// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions. */

//#define MK_NETTEST_TRACE 1 // force nettest.hpp to emit diagnostics

#include <measurement_kit/nettest/nettest.hpp>

#include <stdlib.h>

#include <iostream>

class MyRunner : public mk::nettest::Runner {
 public:
  using mk::nettest::Runner::Runner;

  void on_log(const mk::nettest::event::Log &e) override {
    std::clog << "LOG: <" << e.log_level << "> " << e.message << std::endl;
  }

  void on_status_progress(
      const mk::nettest::event::StatusProgress &e) override {
    std::clog << "PROGRESS: " << e.percentage << " " << e.message << std::endl;
  }

  void on_status_queued(const mk::nettest::event::StatusQueued &) override {
    std::clog << "QUEUED" << std::endl;
  }
};

int main(int argc, char **argv) {
  mk::nettest::settings::WebConnectivity settings;
  settings.inputs.push_back("www.kernel.org");
  --argc, ++argv;
  while (argc > 0) {
    settings.input_filepaths.push_back(*argv);
    --argc, ++argv;
  }
  MyRunner my_runner;
  my_runner.run(my_runner.prepare_web_connectivity(settings));
}
