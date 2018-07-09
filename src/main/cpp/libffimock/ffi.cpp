// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions. */

#include <measurement_kit/ffi/ffi.h>

#include <chrono>
#include <fstream>
#include <random>

#include <nlohmann/json.hpp>

#include <measurement_kit/ffi/nettest.hpp>

// Fake implementation of a network test.
struct mk_task_ : public mk::ffi::NettestHelper {
 public:
  using mk::ffi::NettestHelper::NettestHelper;

 protected:
  void run(nlohmann::json &&settings) override;

 private:
  std::string really_run(nlohmann::json &&settings, std::mt19937 &&generator);
};

void mk_task_t::run(nlohmann::json &&settings) {
  std::random_device rd;
  std::mt19937 g{rd()};
  std::uniform_int_distribution<int64_t> d{0, UINT32_MAX};
  emit_status_end(d(g), d(g), really_run(std::move(settings), std::move(g)));
}

std::string mk_task_t::really_run(nlohmann::json &&settings,
                                  std::mt19937 &&gen) {
  // Gather interesting settings values
  // ----------------------------------

  std::vector<std::string> inputs;
  std::vector<std::string> input_filepaths;
  std::string log_filepath;
  double max_runtime = -1.0;
  int64_t randomize_input = 1;

  if (settings.count("log_filepath") > 0) {
    log_filepath = settings.at("log_filepath");
  }
  if (settings.count("inputs") > 0) {
    inputs = settings.at("inputs").get<std::vector<std::string>>();
  }
  if (settings.count("input_filepaths") > 0) {
    input_filepaths =
        settings.at("input_filepaths").get<std::vector<std::string>>();
  }
  if (settings.count("options") > 0 &&
      settings.at("options").count("max_runtime") > 0) {
    max_runtime = settings.at("options").at("max_runtime");
  }
  if (settings.count("options") > 0 &&
      settings.at("options").count("randomize_input") > 0) {
    randomize_input = settings.at("options").at("randomize_input");
  }

  // Pre-test operations
  // -------------------

  emit_status_started();
  emit_status_progress(0.1, "contacted bouncer");
  emit_status_geoip_lookup("127.0.0.1", "AS0", "ZZ", "");
  emit_status_progress(0.2, "geoip lookup");
  emit_status_resolver_lookup("127.0.0.1");
  emit_status_progress(0.3, "resolver_lookup");
  emit_status_report_create(
      "20180709T073520Z_AS0_"
      "i1rnCpvJtwpvBmVStDatcajrYiXt7wzW0kV77HqNvUR5bfSa9i");
  emit_status_progress(0.4, "open report");

  // Load and randomize input
  // ------------------------

  for (auto &path : input_filepaths) {
    std::ifstream filep{path};
    std::string line;
    while ((std::getline(filep, line))) {
      inputs.push_back(line);
    }
    if (!filep.eof()) {
      emit_log("WARNING", "cannot read input file");
      return "io_error";
    }
  }
  if (inputs.size() <= 0) {
    emit_log("WARNING", "no input provided");
    return "invalid_argument";
  }
  if (randomize_input != 0) {
    std::shuffle(inputs.begin(), inputs.end(), gen);
  }

  // Run measurements
  // ----------------

  auto start = std::chrono::steady_clock::now();
  int64_t idx = 0;
  for (auto &input : inputs) {
    auto current_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> delta = start - current_time;
    if (max_runtime >= 0 && delta.count() > max_runtime) {
      emit_log("WARNING", "exceeded maximum runtime");
      break;
    }
    emit_status_measurement_start(idx, input);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    emit_measurement(idx, R"({
      "annotations": {
        "engine_name": "libmeasurement_kit",
        "engine_version": "0.8.3",
        "engine_version_full": "v0.8.3",
        "platform": "macos"
      },
      "data_format_version": "0.2.0",
      "id": "1737d0bf-7a31-49f8-9b35-ff8b5817d003",
      "input": null,
      "input_hashes": [],
      "measurement_start_time": "2018-07-09 07:35:20",
      "options": [],
      "probe_asn": "AS0",
      "probe_cc": "ZZ",
      "probe_city": null,
      "probe_ip": "127.0.0.1",
      "report_id": "20180709T073520Z_AS0_i1rnCpvJtwpvBmVStDatcajrYiXt7wzW0kV77HqNvUR5bfSa9i",
      "software_name": "measurement_kit",
      "software_version": "0.8.3",
      "test_helpers": {
        "backend": "http://37.218.247.95:80"
      },
      "test_keys": {
        "client_resolver": "80.78.66.66",
        "failure": null
      },
      "test_name": "mocked_test",
      "test_runtime": 1.0,
      "test_start_time": "2018-07-09 07:35:17",
      "test_version": "0.0.1"
    })");
    emit_status_measurement_done(idx);
    if (idx > INT64_MAX - 1) {
      emit_log("WARNING", "avoiding overflow");
      return "value_too_large";
    }
    idx += 1;
  }

  // Finish nettest
  // --------------

  emit_status_progress(0.9, "ending the test");
  emit_status_report_close(
      "20180709T073520Z_AS0_"
      "i1rnCpvJtwpvBmVStDatcajrYiXt7wzW0kV77HqNvUR5bfSa9i");

  return "";
}

struct mk_event_ : public std::string {
  using std::string::string;
};

const char *mk_event_serialize(mk_event_t *event) noexcept {
  return (event) ? event->c_str() : nullptr;
}

void mk_event_destroy(mk_event_t *event) noexcept { delete event; }

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
  return (task) ? new mk_event_t{task->wait_for_next_event().dump()} : nullptr;
}

int mk_task_is_done(mk_task_t *task) noexcept {
  return (task) ? (int)task->is_done() : 1;
}

void mk_task_interrupt(mk_task_t *task) noexcept {
  if (task) {
    task->interrupt();
  }
}

void mk_task_destroy(mk_task_t *task) noexcept { delete task; }
