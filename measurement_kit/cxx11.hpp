// Autogenerated by measurement-kit/ffi tools; DO NOT EDIT!
#ifndef MEASUREMENT_KIT_CXX11_HPP

#include <stdint.h>

#include <map>
#include <string>
#include <vector>

#include <measurement_kit/ffi.h>
#include <nlohmann/json.hpp>

namespace mk {
namespace cxx11 {

/// @brief We could not lookup the ASN from the probe IP.
class FailureASNLookupEvent {
public:
  /// @brief The actual failure that occurred.
  std::string failure = "";
};

/// @brief Status update regarding measuring performance.
class StatusUpdatePerformanceEvent {
public:
  /// @brief Either 'download' or 'upload'.
  std::string direction = "";
  /// @brief Seconds elapsed since we started measuring.
  double elapsed = 0.0;
  /// @brief Number of streams being used.
  int64_t num_streams = 0;
  /// @brief Speed measured in kbit/s.
  double speed_kbps = 0.0;
};

/// @brief Scalar options controlling the behavior of a nettest.
class Options {
public:
  /// @brief Base URL of the OONI bouncer
  std::string bouncer_base_url = "";
  /// @brief Use this specific nameserver to resolve DNS names rather than using
  /// the default system resolver.
  std::string dns_name_server = "";
  /// @brief Ignore errors when contacting the OONI bouncer.
  bool ignore_bouncer_error = true;
  /// @brief Maximum number of seconds for which nettests containing multiple
  /// inputs are allowed to run.
  double max_runtime = -1.0;
};

/// @brief Contains all the settings of a network test. The most important, and
/// the only mandatory field, is the network test `name`, that identifies what
/// test to run.
class Settings {
public:
  /// @brief Optional annotations that will be included into the report sent to
  /// the OONI collector.
  std::map<std::string, std::string> annotations;
  /// @brief List of events that will not be delivered becasue you do not care
  /// about them.
  std::vector<std::string> disabled_events;
  /// @brief Name of the test. This is a mandatory setting.
  std::string name = "";
  /// @brief Scalar options controlling the behavior of a nettest.
  Options options;
};

/// @brief A network test.
class Nettest {
public:
  /// @brief Callback called by run when FailureASNLookupEvent occurs.
  virtual void on_failure_asn_lookup(const FailureASNLookupEvent &) {
    // TODO: override
  }

  /// @brief Callback called by run when StatusUpdatePerformanceEvent occurs.
  virtual void
  on_status_update_performance(const StatusUpdatePerformanceEvent &) {
    // TODO: override
  }

  /// @brief Create a nettest using the specified settings.
  explicit Nettest(Settings s) noexcept { std::swap(s, settings_); }

  /// @brief Runs the nettest until completion.
  void run();

  /// @brief Releases allocated resources.
  virtual ~Nettest() noexcept;

private:
  Settings settings_;
};

Nettest::~Nettest() noexcept {}

namespace internal {

class TaskDeleter {
public:
  void operator()(mk_task_t *task) noexcept { mk_task_destroy(task); }
};
using UniqueTask = std::unique_ptr<mk_task_t, TaskDeleter>;

class EventDeleter {
public:
  void operator()(mk_event_t *event) noexcept { mk_event_destroy(event); }
};
using UniqueEvent = std::unique_ptr<mk_event_t, EventDeleter>;

} // namespace internal

void Nettest::run() {
  nlohmann::json cxx_settings;
  {
    cxx_settings["annotations"] = settings_.annotations;
    cxx_settings["disabled_events"] = settings_.disabled_events;
    cxx_settings["name"] = settings_.name;
  }
  {
    cxx_settings["options"]["bouncer_base_url"] =
        settings_.options.bouncer_base_url;
    cxx_settings["options"]["dns/nameserver"] =
        settings_.options.dns_name_server;
    cxx_settings["options"]["ignore_bouncer_error"] =
        (settings_.options.ignore_bouncer_error) ? 1 : 0;
    cxx_settings["options"]["max_runtime"] = settings_.options.max_runtime;
  }
  internal::UniqueTask task{mk_task_start(cxx_settings.dump().c_str())};
  while (task) {
    nlohmann::json ev;
    {
      internal::UniqueEvent event{mk_task_wait_for_next_event(task.get())};
      if (!event) {
        break;
      }
      auto str = mk_event_serialize(event.get());
      if (!str) {
        break;
      }
      ev = nlohmann::json::parse(str);
    }
    if (ev.at("key") == "failure.asn_lookup") {
      FailureASNLookupEvent event;
      event.failure = ev.at("value").at("failure");
      on_failure_asn_lookup(event);
      continue;
    }
    if (ev.at("key") == "status.update_performance") {
      StatusUpdatePerformanceEvent event;
      event.direction = ev.at("value").at("direction");
      event.elapsed = ev.at("value").at("elapsed");
      event.num_streams = ev.at("value").at("num_streams");
      event.speed_kbps = ev.at("value").at("speed_kbps");
      on_status_update_performance(event);
      continue;
    }
  }
}

} // namespace cxx11
} // namespace mk
#endif // MEASUREMENT_KIT_CXX11_HPP
