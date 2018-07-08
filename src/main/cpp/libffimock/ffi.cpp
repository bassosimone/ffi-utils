// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions. */

#include <measurement_kit/ffi/ffi.h>

#include <nlohmann/json.hpp>

#include <measurement_kit/ffi/nettest.hpp>

// Fake implementation of a network test.
struct mk_task_ : public mk::ffi::NettestHelper {
 public:
  using mk::ffi::NettestHelper::NettestHelper;

 protected:
  void run(nlohmann::json &&settings) override;
};

void mk_task_t::run(nlohmann::json &&settings) {
  // TODO(bassosimone): implement.
}

struct mk_event_ : public nlohmann::json {
  using nlohmann::json::json;
};

const char *mk_event_serialize(mk_event_t *event) noexcept {
  return (event) ? event->dump().c_str() : nullptr;
}

void mk_event_destroy(mk_event_t *event) noexcept {
  delete event;
}

mk_task_t *mk_task_start(const char *settings) noexcept {
  if (settings == nullptr) {
    return nullptr;
  }
  nlohmann::json doc;
  try {
    doc = nlohmann::json::parse(settings);
  } catch (const std::exception &) {
    return nullptr;
  }
  return new mk_task_t{std::move(doc)};
}

mk_event_t *mk_task_wait_for_next_event(mk_task_t *task) noexcept {
  return (task) ? new mk_event_t{task->wait_for_next_event()} : nullptr;
}

int mk_task_is_done(mk_task_t *task) noexcept {
  return (task) ? (int)task->is_done() : 1;
}

void mk_task_interrupt(mk_task_t *task) noexcept {
  if (task) {
    task->interrupt();
  }
}

void mk_task_destroy(mk_task_t *task) noexcept {
  delete task;
}
