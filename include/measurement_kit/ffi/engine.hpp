// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.
#ifndef MEASUREMENT_KIT_FFI_ENGINE_HPP
#define MEASUREMENT_KIT_FFI_ENGINE_HPP

/*-
 *  __      __  _____ __________  _______  .___ _______    ________
 * /  \    /  \/  _  \\______   \ \      \ |   |\      \  /  _____/
 * \   \/\/   /  /_\  \|       _/ /   |   \|   |/   |   \/   \  ___
 *  \        /    |    \    |   \/    |    \   /    |    \    \_\  \
 *   \__/\  /\____|__  /____|_  /\____|__  /___\____|__  /\______  /
 *        \/         \/       \/         \/            \/        \/
 *
 * Copied from measurement-kit/ffi-tools; DO NOT EDIT!
 *
 * See https://github.com/measurement-kit/ffi-tools for more information.
 *
 * Code in this file is not Doxygen-documented because it's meant for
 * internal Measurement Kit consumption only.
 */

#include <assert.h>

#include <atomic>
#include <algorithm>
#include <condition_variable>
#include <deque>
#include <future>
#include <mutex>
#include <thread>

#include <nlohmann/json.hpp>

namespace mk {
namespace ffi {
namespace engine {

// Abstraction that behaves like a semaphore. We use it to make sure that
// tests do not run concurrently. Since a semaphore does not provide any
// FIFO guarantee, you SHOULD NOT rely on this mechanism to guarantee that
// nettests are executed in order because you would be disappointed.
class Semaphore {
 public:
  Semaphore() noexcept;

  // Acquire the semaphore. Lock if another thread is active.
  void acquire();

  // Release the semaphore possibly allowing another thread to continue.
  void release();

  // Make the class non copyable and non movable.
  Semaphore(const Semaphore &) = delete;
  Semaphore &operator=(const Semaphore &) = delete;
  Semaphore(Semaphore &&) = delete;
  Semaphore &operator=(Semaphore &&) = delete;

  ~Semaphore() noexcept;

 private:
  std::mutex mutex_;
};

#ifndef MK_FFI_ENGINE_NO_INLINE_IMPL

Semaphore::Semaphore() noexcept {}

void Semaphore::acquire() { mutex_.lock(); }

void Semaphore::release() { mutex_.unlock(); }

Semaphore::~Semaphore() noexcept {}

#endif  // MK_FFI_ENGINE_NO_INLINE_IMPL

// A task that you would like to run. You should override the run() and
// really_interrupt() methods. The class name is Task rather than Nettest
// because it may possibly be useful to run several types of tasks.
class Task {
 public:
  // Create a task with the specified settings. This method starts a
  // background thread where to run the task. Note that the task could
  // be paused if there is already an active task.
  explicit Task(nlohmann::json &&settings);

  // Blocks waiting for the next event to be posted on the queue.
  nlohmann::json wait_for_next_event();

  // Returns true if the task is completed, false otherwise.
  bool is_done();

  // Interrupts the task if it's currently running. This method will call
  // the really_interrupt() method that you should probably override.
  void interrupt();

  // Interrupts the task and then waits for the thread to terminate.
  virtual ~Task() noexcept;

  // Make this class explicitly non copyable and non movable.
  Task(const Task &) noexcept = delete;
  Task &operator=(const Task &) noexcept = delete;
  Task(Task &&) noexcept = delete;
  Task &operator=(Task &&) noexcept = delete;

 protected:
  // This method is called by this class or by base classes to emit an event.
  void emit(nlohmann::json &&event);

  // You should override this method to interrupt the test.
  virtual void really_interrupt();

  // You should override this method to actually run the test. The settings
  // argument will contain the settings passed to the constructor. This
  // method will be called from the background thread, after we are sure
  // that the current nettest can run (i.e. no other running nettests).
  virtual void run(nlohmann::json &&settings);

  // Condition variable used to know when we have pending events.
  std::condition_variable cond_;

  // Queue where pending events are posted.
  std::deque<nlohmann::json> deque_;

  // Atomic flag telling us whether we've been interrupted.
  std::atomic_bool interrupted_{false};

  // Mutex protecting this class from concurrent access.
  std::mutex mutex_;

  // Atomic flag telling us whether the background thread is running.
  std::atomic_bool running_{false};

  // The background thread where the nettest will run.
  std::thread thread_;

 private:
  // Method that in debug mode aborts if passed an invalid event.
  nlohmann::json possibly_validate_event(nlohmann::json &&ev);

  // Make sure that settings are okay and then invoke the run() method.
  void check_settings_and_run(nlohmann::json &&settings);
};

#ifndef MK_FFI_ENGINE_NO_INLINE_IMPL

Task::Task(nlohmann::json &&settings) {
  // The purpose of `barrier` is to wait in the constructor until the
  // thread for running the test is up and running.
  std::promise<void> barrier;
  std::future<void> started = barrier.get_future();
  auto main = [this, &barrier, settings]() mutable {
    running_ = true;
    barrier.set_value();
    static Semaphore semaphore;
    {
      nlohmann::json event;
      event["key"] = "status.queued";
      event["value"] = nlohmann::json::object();
      emit(std::move(event));
    }
    semaphore.acquire();  // prevent concurrent tasks
    check_settings_and_run(std::move(settings));
    running_ = false;
    cond_.notify_all();   // tell the readers we're done
    semaphore.release();  // allow another task to run
  };
  thread_ = std::thread(std::move(main));
  started.wait();  // guarantee Task() completes when the thread is running
}

nlohmann::json Task::wait_for_next_event() {
  std::unique_lock<std::mutex> lock{mutex_};
  // purpose: block here until we stop running or we have events to read
  cond_.wait(lock, [this]() { return !running_ || !deque_.empty(); });
  // must be first so we drain the queue before emitting the final null
  if (!deque_.empty()) {
    auto ev = std::move(deque_.front());
    deque_.pop_front();
    return ev;
  }
  assert(!running_);
  // Rationale: we used to return `null` when done. But then I figured that
  // this could break people code. So, to ease integrator's life, we now
  // return a dummy event structured exactly like other events.
  return possibly_validate_event(nlohmann::json{
      {"key", "task_terminated"},
      {"value", nlohmann::json::object()},
  });
}

bool Task::is_done() {
  std::unique_lock<std::mutex> _{mutex_};
  // Rationale: when the task thread terminates, there may be some
  // unread events in queue. We do not consider the task as done until
  // such events have been read and processed by our controller.
  return running_ == false && deque_.empty();
}

void Task::interrupt() {
  interrupted_ = true;
  really_interrupt();
}

Task::~Task() noexcept {
  if (thread_.joinable()) {
    // Configurable because this was not the default behavior in the
    // MK implementation, so I want to explicitly break compat.
#ifdef MK_FFI_ENGINE_INTERRUPT_ON_DESTROY
    interrupt();
#endif
    thread_.join();
  }
}

void Task::emit(nlohmann::json &&event) {
  event = possibly_validate_event(std::move(event));
  {
    std::unique_lock<std::mutex> _{mutex_};
    deque_.push_back(std::move(event));
  }
  cond_.notify_all();  // more efficient if unlocked
}

void Task::really_interrupt() {}

void Task::run(nlohmann::json &&) {}

nlohmann::json Task::possibly_validate_event(nlohmann::json &&ev) {
  return std::move(ev);
}

void Task::check_settings_and_run(nlohmann::json &&settings) {
  run(std::move(settings));
}

#endif  // MK_FFI_ENGINE_NO_INLINE_IMPL
}  // namespace engine
}  // namespace ffi
}  // namespace mk
#endif
