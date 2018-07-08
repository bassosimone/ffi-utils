// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.
#ifndef MEASUREMENT_KIT_FFI_NETTEST_HPP
#define MEASUREMENT_KIT_FFI_NETTEST_HPP

/*-
 *  __      __  _____ __________  _______  .___ _______    ________
 * /  \    /  \/  _  \\______   \ \      \ |   |\      \  /  _____/
 * \   \/\/   /  /_\  \|       _/ /   |   \|   |/   |   \/   \  ___
 *  \        /    |    \    |   \/    |    \   /    |    \    \_\  \
 *   \__/\  /\____|__  /____|_  /\____|__  /___\____|__  /\______  /
 *        \/         \/       \/         \/            \/        \/
 *
 * Autogenerated by measurement-kit/ffi-tools; DO NOT EDIT!
 *
 * See https://github.com/measurement-kit/ffi-tools for more information.
 *
 * Code in this file is not Doxygen-documented because it's meant for
 * internal Measurement Kit consumption only.
 */

#include <measurement_kit/ffi/task.hpp>

#include <assert.h>
#include <stdint.h>

namespace mk {
namespace ffi {

// Helper class useful to implement a real network test. It adds to the parent
// ffi::Task class knowledge about the structure of settings and events. It
// does not override the methods that actually start and stop a test, as this
// is dependent upon MK internals. It just adds support for events.
class NettestHelper : public Task {
 public:
  // Using the same constructor of the parent class.
  using Task::Task;

  // Necessary because the parent class has virtual destructor.
  ~NettestHelper() noexcept override;

 protected:
  // Method that in debug mode aborts if passed an invalid event.
  nlohmann::json possibly_validate_event(nlohmann::json &&ev) override;

  // Make sure that settings are okay.
  bool check_settings(const nlohmann::json &settings) override;

  // Helper method to emit the failure.asn_lookup event
  void emit_failure_asn_lookup(std::string failure);

  // Helper method to emit the failure.cc_lookup event
  void emit_failure_cc_lookup(std::string failure);

  // Helper method to emit the failure.ip_lookup event
  void emit_failure_ip_lookup(std::string failure);

  // Helper method to emit the failure.measurement event
  void emit_failure_measurement(std::string failure);

  // Helper method to emit the failure.measurement_submission event
  void emit_failure_measurement_submission(std::string failure, int64_t idx,
                                           std::string json_str);

  // Helper method to emit the failure.report_create event
  void emit_failure_report_create(std::string failure);

  // Helper method to emit the failure.report_close event
  void emit_failure_report_close(std::string failure);

  // Helper method to emit the failure.resolver_lookup event
  void emit_failure_resolver_lookup(std::string failure);

  // Helper method to emit the failure.startup event
  void emit_failure_startup(std::string failure);

  // Helper method to emit the log event
  void emit_log(std::string log_level, std::string message);

  // Helper method to emit the measurement event
  void emit_measurement(int64_t idx, std::string json_str);

  // Helper method to emit the status.end event
  void emit_status_end(double downloaded_kb, double uploaded_kb,
                       std::string failure);

  // Helper method to emit the status.geoip_lookup event
  void emit_status_geoip_lookup(std::string probe_ip, std::string probe_asn,
                                std::string probe_cc,
                                std::string probe_network_name);

  // Helper method to emit the status.progress event
  void emit_status_progress(double percentage, std::string message);

  // Helper method to emit the status.queued event
  void emit_status_queued();

  // Helper method to emit the status.measurement_start event
  void emit_status_measurement_start(int64_t idx, std::string input);

  // Helper method to emit the status.measurement_submission event
  void emit_status_measurement_submission(int64_t idx);

  // Helper method to emit the status.measurement_done event
  void emit_status_measurement_done(int64_t idx);

  // Helper method to emit the status.report_close event
  void emit_status_report_close(std::string report_id);

  // Helper method to emit the status.report_create event
  void emit_status_report_create(std::string report_id);

  // Helper method to emit the status.resolver_lookup event
  void emit_status_resolver_lookup(std::string ip_address);

  // Helper method to emit the status.started event
  void emit_status_started();

  // Helper method to emit the status.update_performance event
  void emit_status_update_performance(std::string direction, double elapsed,
                                      int64_t num_streams, double speed_kbps);

  // Helper method to emit the status.update.websites event
  void emit_status_update_websites(std::string url, std::string status);

  // Helper method to emit the task_terminated event
  void emit_task_terminated();
};

#ifndef MK_FFI_NETTEST_NO_INLINE_IMPL

NettestHelper::~NettestHelper() noexcept {}

nlohmann::json NettestHelper::possibly_validate_event(nlohmann::json &&ev) {
#ifndef NDEBUG
  {
    bool known_event_key = false;
    do {
      if (ev.at("key") == "failure.asn_lookup") {
        known_event_key = true;
        std::string failure = ev.at("value").at("failure");
        (void)failure;
        break;
      }

      if (ev.at("key") == "failure.cc_lookup") {
        known_event_key = true;
        std::string failure = ev.at("value").at("failure");
        (void)failure;
        break;
      }

      if (ev.at("key") == "failure.ip_lookup") {
        known_event_key = true;
        std::string failure = ev.at("value").at("failure");
        (void)failure;
        break;
      }

      if (ev.at("key") == "failure.measurement") {
        known_event_key = true;
        std::string failure = ev.at("value").at("failure");
        (void)failure;
        break;
      }

      if (ev.at("key") == "failure.measurement_submission") {
        known_event_key = true;
        std::string failure = ev.at("value").at("failure");
        (void)failure;
        int64_t idx = ev.at("value").at("idx");
        (void)idx;
        std::string json_str = ev.at("value").at("json_str");
        (void)json_str;
        break;
      }

      if (ev.at("key") == "failure.report_create") {
        known_event_key = true;
        std::string failure = ev.at("value").at("failure");
        (void)failure;
        break;
      }

      if (ev.at("key") == "failure.report_close") {
        known_event_key = true;
        std::string failure = ev.at("value").at("failure");
        (void)failure;
        break;
      }

      if (ev.at("key") == "failure.resolver_lookup") {
        known_event_key = true;
        std::string failure = ev.at("value").at("failure");
        (void)failure;
        break;
      }

      if (ev.at("key") == "failure.startup") {
        known_event_key = true;
        std::string failure = ev.at("value").at("failure");
        (void)failure;
        break;
      }

      if (ev.at("key") == "log") {
        known_event_key = true;
        std::string log_level = ev.at("value").at("log_level");
        (void)log_level;
        std::string message = ev.at("value").at("message");
        (void)message;
        break;
      }

      if (ev.at("key") == "measurement") {
        known_event_key = true;
        int64_t idx = ev.at("value").at("idx");
        (void)idx;
        std::string json_str = ev.at("value").at("json_str");
        (void)json_str;
        break;
      }

      if (ev.at("key") == "status.end") {
        known_event_key = true;
        double downloaded_kb = ev.at("value").at("downloaded_kb");
        (void)downloaded_kb;
        double uploaded_kb = ev.at("value").at("uploaded_kb");
        (void)uploaded_kb;
        std::string failure = ev.at("value").at("failure");
        (void)failure;
        break;
      }

      if (ev.at("key") == "status.geoip_lookup") {
        known_event_key = true;
        std::string probe_ip = ev.at("value").at("probe_ip");
        (void)probe_ip;
        std::string probe_asn = ev.at("value").at("probe_asn");
        (void)probe_asn;
        std::string probe_cc = ev.at("value").at("probe_cc");
        (void)probe_cc;
        std::string probe_network_name =
            ev.at("value").at("probe_network_name");
        (void)probe_network_name;
        break;
      }

      if (ev.at("key") == "status.progress") {
        known_event_key = true;
        double percentage = ev.at("value").at("percentage");
        (void)percentage;
        std::string message = ev.at("value").at("message");
        (void)message;
        break;
      }

      if (ev.at("key") == "status.queued") {
        known_event_key = true;
        break;
      }

      if (ev.at("key") == "status.measurement_start") {
        known_event_key = true;
        int64_t idx = ev.at("value").at("idx");
        (void)idx;
        std::string input = ev.at("value").at("input");
        (void)input;
        break;
      }

      if (ev.at("key") == "status.measurement_submission") {
        known_event_key = true;
        int64_t idx = ev.at("value").at("idx");
        (void)idx;
        break;
      }

      if (ev.at("key") == "status.measurement_done") {
        known_event_key = true;
        int64_t idx = ev.at("value").at("idx");
        (void)idx;
        break;
      }

      if (ev.at("key") == "status.report_close") {
        known_event_key = true;
        std::string report_id = ev.at("value").at("report_id");
        (void)report_id;
        break;
      }

      if (ev.at("key") == "status.report_create") {
        known_event_key = true;
        std::string report_id = ev.at("value").at("report_id");
        (void)report_id;
        break;
      }

      if (ev.at("key") == "status.resolver_lookup") {
        known_event_key = true;
        std::string ip_address = ev.at("value").at("ip_address");
        (void)ip_address;
        break;
      }

      if (ev.at("key") == "status.started") {
        known_event_key = true;
        break;
      }

      if (ev.at("key") == "status.update_performance") {
        known_event_key = true;
        std::string direction = ev.at("value").at("direction");
        (void)direction;
        double elapsed = ev.at("value").at("elapsed");
        (void)elapsed;
        int64_t num_streams = ev.at("value").at("num_streams");
        (void)num_streams;
        double speed_kbps = ev.at("value").at("speed_kbps");
        (void)speed_kbps;
        break;
      }

      if (ev.at("key") == "status.update.websites") {
        known_event_key = true;
        std::string url = ev.at("value").at("url");
        (void)url;
        std::string status = ev.at("value").at("status");
        (void)status;
        break;
      }

      if (ev.at("key") == "task_terminated") {
        known_event_key = true;
        break;
      }

    } while (0);
    assert(known_event_key);
  }
  if (ev.at("key") == "log") {
    bool known_log_level = false;
    do {
      if (ev.at("key").at("log_level") == "ERR") {
        known_log_level = true;
        break;
      }
      if (ev.at("key").at("log_level") == "WARNING") {
        known_log_level = true;
        break;
      }
      if (ev.at("key").at("log_level") == "INFO") {
        known_log_level = true;
        break;
      }
      if (ev.at("key").at("log_level") == "DEBUG") {
        known_log_level = true;
        break;
      }
      if (ev.at("key").at("log_level") == "DEBUG2") {
        known_log_level = true;
        break;
      }

    } while (0);
    assert(known_log_level);
  }
#endif
  return std::move(ev);
}

bool NettestHelper::check_settings(const nlohmann::json &settings) {
  if (!settings.is_object()) {
    return false;
  }

  // Settings checks
  // ---------------

  // Make sure that all fields in settings have the correct type.
  if (settings.count("annotations") > 0 &&
      !settings.at("annotations").is_object()) {
    return false;
  }
  if (settings.count("disabled_events") > 0 &&
      !settings.at("disabled_events").is_array()) {
    return false;
  }
  if (settings.count("inputs") > 0 && !settings.at("inputs").is_array()) {
    return false;
  }
  if (settings.count("input_filepaths") > 0 &&
      !settings.at("input_filepaths").is_array()) {
    return false;
  }
  if (settings.count("log_filepath") > 0 &&
      !settings.at("log_filepath").is_string()) {
    return false;
  }
  if (settings.count("log_level") > 0 &&
      !settings.at("log_level").is_string()) {
    return false;
  }
  if (settings.count("name") > 0 && !settings.at("name").is_string()) {
    return false;
  }
  if (settings.count("options") > 0 && !settings.at("options").is_object()) {
    return false;
  }
  if (settings.count("output_filepath") > 0 &&
      !settings.at("output_filepath").is_string()) {
    return false;
  }

  // Make sure all annotations are actually strings.
  if (settings.count("annotations") > 0) {
    auto &annotations = settings.at("annotations");
#if NLOHMANN_JSON_VERSION_MAJOR >= 3
    for (auto &it : annotations.items()) {
#else
    for (auto it : nlohmann::json::iterator_wrapper(annotations)) {
#endif
      auto &value = it.value();
      if (!value.is_string()) {
        return false;
      }
    }
  }

  // Make sure all disabled_events are strings and known events.
  if (settings.count("disabled_events") > 0) {
    auto &disabled_events = settings.at("disabled_events");
    for (auto &elem : disabled_events) {
      if (!elem.is_string()) {
        return false;
      }
      if (elem != "failure.asn_lookup" && elem != "failure.cc_lookup" &&
          elem != "failure.ip_lookup" && elem != "failure.measurement" &&
          elem != "failure.measurement_submission" &&
          elem != "failure.report_create" && elem != "failure.report_close" &&
          elem != "failure.resolver_lookup" && elem != "failure.startup" &&
          elem != "log" && elem != "measurement" && elem != "status.end" &&
          elem != "status.geoip_lookup" && elem != "status.progress" &&
          elem != "status.queued" && elem != "status.measurement_start" &&
          elem != "status.measurement_submission" &&
          elem != "status.measurement_done" && elem != "status.report_close" &&
          elem != "status.report_create" && elem != "status.resolver_lookup" &&
          elem != "status.started" && elem != "status.update_performance" &&
          elem != "status.update.websites" && elem != "task_terminated") {
        return false;
      }
    }
  }

  // Make sure all inputs are strings.
  if (settings.count("inputs") > 0) {
    auto &inputs = settings.at("inputs");
    for (auto &elem : inputs) {
      if (!elem.is_string()) {
        return false;
      }
    }
  }

  // Make sure all input_filepaths are strings.
  if (settings.count("input_filepaths") > 0) {
    auto &input_filepaths = settings.at("input_filepaths");
    for (auto &elem : input_filepaths) {
      if (!elem.is_string()) {
        return false;
      }
    }
  }

  // Make sure that log_level is a known value.
  if (settings.count("log_level") > 0) {
    auto &log_level = settings.at("log_level");
    if (log_level != "ERR" && log_level != "WARNING" && log_level != "INFO" &&
        log_level != "DEBUG" && log_level != "DEBUG2") {
      return false;
    }
  }

  // Make sure that name is present and is a known value.
  if (settings.count("name") <= 0) {
    return false;
  }
  {
    auto &name = settings.at("name");
    if (name != "CaptivePortal" && name != "Dash" && name != "DnsInjection" &&
        name != "FacebookMessenger" && name != "HttpHeaderFieldManipulation" &&
        name != "HttpInvalidRequestLine" && name != "MeekFrontedRequests" &&
        name != "MultiNdt" && name != "Ndt" && name != "TcpConnect" &&
        name != "Telegram" && name != "WebConnectivity" && name != "Whatsapp") {
      return false;
    }
  }

  // Options checks
  // --------------

  // Make sure that all fields in settings.options have the correct type.
  if (settings.count("options") > 0) {
    auto &options = settings.at("options");
    if (options.count("bouncer_base_url") > 0 &&
        !options.at("bouncer_base_url").is_string()) {
      return false;
    }
    if (options.count("collector_base_url") > 0 &&
        !options.at("collector_base_url").is_string()) {
      return false;
    }
    if (options.count("dns/nameserver") > 0 &&
        !options.at("dns/nameserver").is_string()) {
      return false;
    }
    if (options.count("dns/engine") > 0 &&
        !options.at("dns/engine").is_string()) {
      return false;
    }
    if (options.count("geoip_asn_path") > 0 &&
        !options.at("geoip_asn_path").is_string()) {
      return false;
    }
    if (options.count("geoip_country_path") > 0 &&
        !options.at("geoip_country_path").is_string()) {
      return false;
    }
    if (options.count("ignore_bouncer_error") > 0 &&
        !options.at("ignore_bouncer_error").is_number_integer()) {
      return false;
    }
    if (options.count("ignore_open_report_error") > 0 &&
        !options.at("ignore_open_report_error").is_number_integer()) {
      return false;
    }
    if (options.count("max_runtime") > 0 &&
        !options.at("max_runtime").is_number_float()) {
      return false;
    }
    if (options.count("net/ca_bundle_path") > 0 &&
        !options.at("net/ca_bundle_path").is_string()) {
      return false;
    }
    if (options.count("net/timeout") > 0 &&
        !options.at("net/timeout").is_number_float()) {
      return false;
    }
    if (options.count("no_bouncer") > 0 &&
        !options.at("no_bouncer").is_number_integer()) {
      return false;
    }
    if (options.count("no_collector") > 0 &&
        !options.at("no_collector").is_number_integer()) {
      return false;
    }
    if (options.count("no_asn_lookup") > 0 &&
        !options.at("no_asn_lookup").is_number_integer()) {
      return false;
    }
    if (options.count("no_cc_lookup") > 0 &&
        !options.at("no_cc_lookup").is_number_integer()) {
      return false;
    }
    if (options.count("no_ip_lookup") > 0 &&
        !options.at("no_ip_lookup").is_number_integer()) {
      return false;
    }
    if (options.count("no_file_report") > 0 &&
        !options.at("no_file_report").is_number_integer()) {
      return false;
    }
    if (options.count("no_resolver_lookup") > 0 &&
        !options.at("no_resolver_lookup").is_number_integer()) {
      return false;
    }
    if (options.count("probe_asn") > 0 &&
        !options.at("probe_asn").is_string()) {
      return false;
    }
    if (options.count("probe_cc") > 0 && !options.at("probe_cc").is_string()) {
      return false;
    }
    if (options.count("probe_ip") > 0 && !options.at("probe_ip").is_string()) {
      return false;
    }
    if (options.count("randomize_input") > 0 &&
        !options.at("randomize_input").is_number_integer()) {
      return false;
    }
    if (options.count("save_real_probe_asn") > 0 &&
        !options.at("save_real_probe_asn").is_number_integer()) {
      return false;
    }
    if (options.count("save_real_probe_cc") > 0 &&
        !options.at("save_real_probe_cc").is_number_integer()) {
      return false;
    }
    if (options.count("save_real_probe_ip") > 0 &&
        !options.at("save_real_probe_ip").is_number_integer()) {
      return false;
    }
    if (options.count("save_real_resolver_ip") > 0 &&
        !options.at("save_real_resolver_ip").is_number_integer()) {
      return false;
    }
    if (options.count("software_name") > 0 &&
        !options.at("software_name").is_string()) {
      return false;
    }
    if (options.count("software_version") > 0 &&
        !options.at("software_version").is_string()) {
      return false;
    }
  }

  return true;
}

void NettestHelper::emit_failure_asn_lookup(std::string failure) {
  nlohmann::json doc;
  doc["value"]["failure"] = failure;
  doc["key"] = "failure.asn_lookup";
  emit(std::move(doc));
}

void NettestHelper::emit_failure_cc_lookup(std::string failure) {
  nlohmann::json doc;
  doc["value"]["failure"] = failure;
  doc["key"] = "failure.cc_lookup";
  emit(std::move(doc));
}

void NettestHelper::emit_failure_ip_lookup(std::string failure) {
  nlohmann::json doc;
  doc["value"]["failure"] = failure;
  doc["key"] = "failure.ip_lookup";
  emit(std::move(doc));
}

void NettestHelper::emit_failure_measurement(std::string failure) {
  nlohmann::json doc;
  doc["value"]["failure"] = failure;
  doc["key"] = "failure.measurement";
  emit(std::move(doc));
}

void NettestHelper::emit_failure_measurement_submission(std::string failure,
                                                        int64_t idx,
                                                        std::string json_str) {
  nlohmann::json doc;
  doc["value"]["failure"] = failure;
  doc["value"]["idx"] = idx;
  doc["value"]["json_str"] = json_str;
  doc["key"] = "failure.measurement_submission";
  emit(std::move(doc));
}

void NettestHelper::emit_failure_report_create(std::string failure) {
  nlohmann::json doc;
  doc["value"]["failure"] = failure;
  doc["key"] = "failure.report_create";
  emit(std::move(doc));
}

void NettestHelper::emit_failure_report_close(std::string failure) {
  nlohmann::json doc;
  doc["value"]["failure"] = failure;
  doc["key"] = "failure.report_close";
  emit(std::move(doc));
}

void NettestHelper::emit_failure_resolver_lookup(std::string failure) {
  nlohmann::json doc;
  doc["value"]["failure"] = failure;
  doc["key"] = "failure.resolver_lookup";
  emit(std::move(doc));
}

void NettestHelper::emit_failure_startup(std::string failure) {
  nlohmann::json doc;
  doc["value"]["failure"] = failure;
  doc["key"] = "failure.startup";
  emit(std::move(doc));
}

void NettestHelper::emit_log(std::string log_level, std::string message) {
  nlohmann::json doc;
  doc["value"]["log_level"] = log_level;
  doc["value"]["message"] = message;
  doc["key"] = "log";
  emit(std::move(doc));
}

void NettestHelper::emit_measurement(int64_t idx, std::string json_str) {
  nlohmann::json doc;
  doc["value"]["idx"] = idx;
  doc["value"]["json_str"] = json_str;
  doc["key"] = "measurement";
  emit(std::move(doc));
}

void NettestHelper::emit_status_end(double downloaded_kb, double uploaded_kb,
                                    std::string failure) {
  nlohmann::json doc;
  doc["value"]["downloaded_kb"] = downloaded_kb;
  doc["value"]["uploaded_kb"] = uploaded_kb;
  doc["value"]["failure"] = failure;
  doc["key"] = "status.end";
  emit(std::move(doc));
}

void NettestHelper::emit_status_geoip_lookup(std::string probe_ip,
                                             std::string probe_asn,
                                             std::string probe_cc,
                                             std::string probe_network_name) {
  nlohmann::json doc;
  doc["value"]["probe_ip"] = probe_ip;
  doc["value"]["probe_asn"] = probe_asn;
  doc["value"]["probe_cc"] = probe_cc;
  doc["value"]["probe_network_name"] = probe_network_name;
  doc["key"] = "status.geoip_lookup";
  emit(std::move(doc));
}

void NettestHelper::emit_status_progress(double percentage,
                                         std::string message) {
  nlohmann::json doc;
  doc["value"]["percentage"] = percentage;
  doc["value"]["message"] = message;
  doc["key"] = "status.progress";
  emit(std::move(doc));
}

void NettestHelper::emit_status_queued() {
  nlohmann::json doc;
  doc["key"] = "status.queued";
  emit(std::move(doc));
}

void NettestHelper::emit_status_measurement_start(int64_t idx,
                                                  std::string input) {
  nlohmann::json doc;
  doc["value"]["idx"] = idx;
  doc["value"]["input"] = input;
  doc["key"] = "status.measurement_start";
  emit(std::move(doc));
}

void NettestHelper::emit_status_measurement_submission(int64_t idx) {
  nlohmann::json doc;
  doc["value"]["idx"] = idx;
  doc["key"] = "status.measurement_submission";
  emit(std::move(doc));
}

void NettestHelper::emit_status_measurement_done(int64_t idx) {
  nlohmann::json doc;
  doc["value"]["idx"] = idx;
  doc["key"] = "status.measurement_done";
  emit(std::move(doc));
}

void NettestHelper::emit_status_report_close(std::string report_id) {
  nlohmann::json doc;
  doc["value"]["report_id"] = report_id;
  doc["key"] = "status.report_close";
  emit(std::move(doc));
}

void NettestHelper::emit_status_report_create(std::string report_id) {
  nlohmann::json doc;
  doc["value"]["report_id"] = report_id;
  doc["key"] = "status.report_create";
  emit(std::move(doc));
}

void NettestHelper::emit_status_resolver_lookup(std::string ip_address) {
  nlohmann::json doc;
  doc["value"]["ip_address"] = ip_address;
  doc["key"] = "status.resolver_lookup";
  emit(std::move(doc));
}

void NettestHelper::emit_status_started() {
  nlohmann::json doc;
  doc["key"] = "status.started";
  emit(std::move(doc));
}

void NettestHelper::emit_status_update_performance(std::string direction,
                                                   double elapsed,
                                                   int64_t num_streams,
                                                   double speed_kbps) {
  nlohmann::json doc;
  doc["value"]["direction"] = direction;
  doc["value"]["elapsed"] = elapsed;
  doc["value"]["num_streams"] = num_streams;
  doc["value"]["speed_kbps"] = speed_kbps;
  doc["key"] = "status.update_performance";
  emit(std::move(doc));
}

void NettestHelper::emit_status_update_websites(std::string url,
                                                std::string status) {
  nlohmann::json doc;
  doc["value"]["url"] = url;
  doc["value"]["status"] = status;
  doc["key"] = "status.update.websites";
  emit(std::move(doc));
}

void NettestHelper::emit_task_terminated() {
  nlohmann::json doc;
  doc["key"] = "task_terminated";
  emit(std::move(doc));
}

#endif  // MK_FFI_NETTEST_NO_INLINE_IMPL
}  // namespace ffi
}  // namespace mk
#endif  // MEASUREMENT_KIT_FFI_NETTEST_HPP
