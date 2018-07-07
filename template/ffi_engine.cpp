// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.

#include "mk-ffi.h"

#include <assert.h>

#define LIBFFI_NAMESPACE mk_libffi

#include "json.hpp"
#include "libffi/libffi.hpp"
#include "mk.hpp"

struct mk_nettest_ : public mk_libffi::Helper {
 public:
  // Constructor and destructor
  // --------------------------

  using mk_libffi::Helper::Helper;

  ~mk_nettest_() noexcept override;

  // Override Client methods
  // -----------------------

  class MyClient : public mk::Client {
   public:
    MyClient(mk_nettest_ *parent, mk::Settings settings) noexcept
        : mk::Client{std::move(settings)}, parent_{parent} {}

    void on_warning(const std::string &s) noexcept override {
      parent_->emit_log("warning", s.c_str());
    }

    void on_info(const std::string &s) noexcept override {
      parent_->emit_log("info", s.c_str());
    }

    void on_debug(const std::string &s) noexcept override {
      parent_->emit_log("debug", s.c_str());
    }

    void on_performance(uint8_t tid, uint8_t nflows, double measured_bytes,
                        double measurement_interval, double elapsed,
                        double max_runtime) noexcept override {
      {
        double speed_kbits = 0.0;
        if (measurement_interval > 0.0) {
          speed_kbits = (8.0 * measured_bytes) / measurement_interval / 1000.0;
        }
        std::string direction;
        switch (tid) {
          case mk::nettest_flag_download:
          case mk::nettest_flag_download_ext:
            direction = "download";
            parent_->downloaded_kb_ += measured_bytes / 1024.0;
            break;
          case mk::nettest_flag_upload:
            direction = "upload";
            parent_->uploaded_kb_ += measured_bytes / 1024.0;
            break;
          default:
            assert(false);
            return;
        }
        parent_->emit_status_update_performance(direction.c_str(), elapsed,
                                                nflows, speed_kbits);
        parent_->emit_status_progress(elapsed / max_runtime, direction.c_str());
      }
    }

    void on_result(std::string scope, std::string name,
                   std::string value) noexcept override {
      nlohmann::json doc;
      doc["key"] = "status.update.result";
      doc["value"]["scope"] = scope;
      doc["value"]["name"] = name;
      doc["value"]["value"] = value;
      parent_->emit(std::move(doc));
    }

    void on_server_busy(std::string /*msg*/) noexcept override {
      parent_->emit_failure_measurement("server_busy");
    }

   private:
    mk_nettest_ *parent_ = nullptr;
  };

  // Override mk_libffi::Helper methods
  // --------------------------------------

  void run(std::string ss) noexcept override {
    mk::Settings settings;

    if (ss.empty() == false) {
      nlohmann::json doc;
      auto okay =
          (parse_json(ss, &doc) &&
           parse_string(doc, "mlabns_url", &settings.mlabns_url, true) &&
           parse_uint16(doc, "timeout", &settings.timeout, true) &&
           parse_string(doc, "hostname", &settings.hostname, true) &&
           parse_string(doc, "port", &settings.port, true) &&
           parse_uint8(doc, "nettest_flags", &settings.nettest_flags, true) &&
           parse_uint32(doc, "verbosity", &settings.verbosity, true) &&
           parse_map_string_string(doc, "metadata", &settings.metadata, true) &&
           parse_uint32(doc, "protocol_flags", &settings.protocol_flags,
                        true) &&
           parse_uint16(doc, "max_runtime", &settings.max_runtime, true) &&
           parse_string(doc, "socks5h_port", &settings.socks5h_port, true));
      if (!okay) {
        return;
      }
    }

    MyClient client{this, std::move(settings)};
    auto rv = client.run();
    // TODO(bassosimone): should have better error than just boolean
    emit_status_end((rv) ? "" : "generic_error", downloaded_kb_, uploaded_kb_);
  }

 private:
  double downloaded_kb_ = 0.0;
  double uploaded_kb_ = 0.0;
};

mk_nettest_::~mk_nettest_() noexcept {}

unsigned int mk_version_major() noexcept { return mk::version_major; }
unsigned int mk_version_minor() noexcept { return mk::version_minor; }
unsigned int mk_version_patch() noexcept { return mk::version_patch; }

unsigned char mk_nettest_flag_upload() noexcept {
  return mk::nettest_flag_upload;
}
unsigned char mk_nettest_flag_download() noexcept {
  return mk::nettest_flag_download;
}
unsigned char mk_nettest_flag_download_ext() noexcept {
  return mk::nettest_flag_download_ext;
}

unsigned int mk_verbosity_quiet() noexcept {
  return mk::verbosity_quiet;
}
unsigned int mk_verbosity_warning() noexcept {
  return mk::verbosity_warning;
}
unsigned int mk_verbosity_info() noexcept { return mk::verbosity_info; }
unsigned int mk_verbosity_debug() noexcept {
  return mk::verbosity_debug;
}

unsigned int mk_protocol_flag_json() noexcept {
  return mk::protocol_flag_json;
}
unsigned int mk_protocol_flag_tls() noexcept {
  return mk::protocol_flag_tls;
}
unsigned int mk_protocol_flag_websockets() noexcept {
  return mk::protocol_flag_websockets;
}


//


// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.
#ifndef LIBFFI_HPP
#define LIBFFI_HPP

#include <assert.h>
#include <limits.h>
#include <stdint.h>

#include <atomic>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#include <json.hpp>

#ifndef LIBFFI_NAMESPACE
#define LIBFFI_NAMESPACE libffi
#endif

namespace LIBFFI_NAMESPACE {

class Helper {
 public:
  // Methods to override
  // -------------------

  virtual void run(std::string) noexcept {}

  virtual void interrupt() noexcept {}

  // Emitters
  // --------

  void emit(nlohmann::json &&doc) noexcept {
    {
      std::unique_lock<std::mutex> _{mutex_};
      events_.push_back(std::move(doc));
    }
    // We expect to have a _single_ reader. See below.
    ready_.notify_one();
  }

  void emit_smpl(const char *key, const char *value_key, const char *value_value) noexcept {
    nlohmann::json doc;
    doc["value"][value_key] = value_value;
    doc["key"] = key;
    emit(std::move(doc));
  }

  void emit_failure_measurement(const char *failure) noexcept {
    emit_smpl("failure.measurement", "failure", failure);
  }

  void emit_failure_startup(const char *failure) noexcept {
    emit_smpl("failure.startup", "failure", failure);
  }

  void emit_log(const char *log_level, const char *message) noexcept {
    nlohmann::json doc;
    doc["value"]["log_level"] = log_level;
    doc["value"]["message"] = message;
    doc["key"] = "log";
    emit(std::move(doc));
  }

  void emit_status_end(const char *failure, double downloaded_kb, double uploaded_kb) noexcept {
    nlohmann::json doc;
    doc["key"] = "status.end";
    doc["value"]["failure"] = failure;
    doc["value"]["downloaded_kb"] = downloaded_kb;
    doc["value"]["uploaded_kb"] = uploaded_kb;
    emit(std::move(doc));
  }

  void emit_status_update_performance(const char *direction, double elapsed, unsigned long nflows,
                                      double speed_kbits) noexcept {
    nlohmann::json doc;
    doc["key"] = "status.update.performance";
    doc["value"]["direction"] = direction;
    doc["value"]["elapsed"] = elapsed;
    doc["value"]["num_streams"] = nflows;
    doc["value"]["speed_kbits"] = speed_kbits;
    emit(std::move(doc));
  }

  void emit_status_progress(double percentage, const char *message) noexcept {
    nlohmann::json doc;
    doc["key"] = "status.progress";
    doc["value"]["percentage"] = percentage;
    doc["value"]["message"] = message;
    emit(std::move(doc));
  }

  // Parsers
  // -------

  void parser_emit_failure_startup(const std::string &error, const std::string &context) noexcept {
    std::stringstream ss;
    ss << error;
    if (!context.empty()) {
      ss << ": ";
      ss << context;
    }
    emit_failure_startup(ss.str().c_str());
  }

  bool parse_json(const std::string &str, nlohmann::json *doc) noexcept {
    nlohmann::json r;
    try {
      r = nlohmann::json::parse(str);
    } catch (const nlohmann::json::exception &) {
      emit_failure_startup("json_parse_error");
      return false;
    }
    if (!r.is_object()) {
      emit_failure_startup("invalid_json_type");
      return false;
    }
    if (doc != nullptr) {
      std::swap(*doc, r);
    }
    return true;
  }

  bool parse_map_string_string(const nlohmann::json &doc, const std::string &key,
                               std::map<std::string, std::string> *value,
                               bool is_optional) noexcept {
    if (doc.count(key) <= 0) {
      if (!is_optional) {
        parser_emit_failure_startup("missing_mandatory_key", key);
        return false;
      }
      return true;
    }
    auto v = doc.at(key);
    if (!v.is_object()) {
      parser_emit_failure_startup("invalid_entry_type", key);
      return false;
    }
    for (auto it : v.items()) {
      const auto &k = it.key();
      auto &v = it.value();
      if (!v.is_string()) {
        parser_emit_failure_startup("invalid_map_string_string_value", key);
        return false;
      }
      if (value != nullptr) {
        (*value)[k] = v;
      }
    }
    return true;
  }

  bool parse_string(const nlohmann::json &doc, const std::string &key, std::string *value,
                    bool is_optional) noexcept {
    if (doc.count(key) <= 0) {
      if (!is_optional) {
        parser_emit_failure_startup("missing_mandatory_key", key);
        return false;
      }
      return true;
    }
    auto v = doc.at(key);
    if (!v.is_string()) {
      parser_emit_failure_startup("invalid_entry_type", key);
      return false;
    }
    if (value != nullptr) {
      *value = v;
    }
    return true;
  }

  bool parse_uint8(const nlohmann::json &doc, const std::string &key, uint8_t *value,
                   bool is_optional) noexcept {
    if (doc.count(key) <= 0) {
      if (!is_optional) {
        parser_emit_failure_startup("missing_mandatory_key", key);
        return false;
      }
      return true;
    }
    auto v = doc.at(key);
    if (!v.is_number_integer()) {
      parser_emit_failure_startup("invalid_entry_type", key);
      return false;
    }
    if (v < 0 || v > UINT8_MAX) {
      parser_emit_failure_startup("invalid_entry_value", key);
      return false;
    }
    if (value != nullptr) {
      *value = v;
    }
    return true;
  }

  bool parse_uint16(const nlohmann::json &doc, const std::string &key, uint16_t *value,
                    bool is_optional) noexcept {
    if (doc.count(key) <= 0) {
      if (!is_optional) {
        parser_emit_failure_startup("missing_mandatory_key", key);
        return false;
      }
      return true;
    }
    auto v = doc.at(key);
    if (!v.is_number_integer()) {
      parser_emit_failure_startup("invalid_entry_type", key);
      return false;
    }
    if (v < 0 || v > UINT16_MAX) {
      parser_emit_failure_startup("invalid_entry_value", key);
      return false;
    }
    if (value != nullptr) {
      *value = v;
    }
    return true;
  }

  bool parse_uint32(const nlohmann::json &doc, const std::string &key, uint32_t *value,
                    bool is_optional) noexcept {
    if (doc.count(key) <= 0) {
      if (!is_optional) {
        parser_emit_failure_startup("missing_mandatory_key", key);
        return false;
      }
      return true;
    }
    auto v = doc.at(key);
    if (!v.is_number_integer()) {
      parser_emit_failure_startup("invalid_entry_type", key);
      return false;
    }
    if (v < 0 || v > UINT32_MAX) {
      parser_emit_failure_startup("invalid_entry_value", key);
      return false;
    }
    if (value != nullptr) {
      *value = v;
    }
    return true;
  }

  // Lifecycle
  // ---------

  static mk_nettest_t *start(const char *s) noexcept {
    auto nettest = new mk_nettest_t{};
    std::string ss = s;
    auto main = [ nettest, ss ]() mutable noexcept {
      // TODO(bassosimone): emit start/stop?
      nettest->run(std::move(ss));
      nettest->done_ = true;
    };
    nettest->worker_ = std::thread{main};
    return nettest;
  }

  static const char *next(Helper *helper) noexcept {
    if (helper == nullptr) {
      return nullptr;
    }
    std::unique_lock<std::mutex> lock{helper->mutex_};
    helper->ready_.wait(lock, [helper]() {  //
      return helper->done_ || !helper->events_.empty();
    });
    // before returning `nullptr` because of joinable thread, drain the queue
    if (!helper->events_.empty()) {
      auto ev = std::move(helper->events_.front());
      helper->events_.pop_front();
      try {
        helper->current_event_ = ev.dump();
      } catch (const nlohmann::json::exception &) {
        return nullptr;
      }
      // Buffer overwritten by each call. Unless we change this code we cannot
      // have more than a _single_ reader at any given time.
      return helper->current_event_.c_str();
    }
    assert(helper->done_);
    return nullptr;
  }

  static void free(Helper *helper) noexcept {
    if (helper != nullptr && helper->worker_.joinable()) {
      helper->interrupt();
      helper->worker_.join();
    }
    delete helper;  // Handles nullptr gracefully
  }

  // Ctor/dtor
  // ---------

  Helper() noexcept {}

  virtual ~Helper() noexcept;

 private:
  std::string current_event_;
  std::atomic_bool done_{false};
  std::deque<nlohmann::json> events_;
  std::mutex mutex_;
  std::condition_variable ready_;
  std::thread worker_;
};

Helper::~Helper() noexcept {}

}  // LIBFFI_NAMESPACE
#endif



//

mk_nettest_t *mk_nettest_start(const char *s) noexcept {
  return (s) ? mk_nettest_t::start(s) : nullptr;
}

const char *mk_nettest_next(mk_nettest_t *nettest) noexcept {
  return (nettest) ? mk_nettest_t::next(nettest) : nullptr;
}

void mk_nettest_free(mk_nettest_t *nettest) noexcept {
  delete nettest;
}
