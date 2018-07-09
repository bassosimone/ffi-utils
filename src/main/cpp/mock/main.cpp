// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions. */

#include <measurement_kit/nettest/nettest.hpp>

#include <stdlib.h>

#include <iostream>

class MyRunner : public mk::nettest::Runner {
 public:
  using mk::nettest::Runner::Runner;

  void on_log(const mk::nettest::events::Log &e) override {
    std::clog << "LOG: <" << e.log_level << "> " << e.message << std::endl;
  }

  void on_status_progress(
      const mk::nettest::events::StatusProgress &e) override {
    std::clog << "PROGRESS: " << e.percentage << " " << e.message << std::endl;
  }
};

int main(int argc, char **argv) {
  mk::nettest::settings::WebConnectivitySettings my_settings;
  my_settings.inputs.push_back("www.kernel.org");
  --argc, ++argv;
  while (argc > 0) {
    my_settings.input_filepaths.push_back(*argv);
    --argc, ++argv;
  }
  MyRunner my_runner;
  try {
    my_runner.run(my_settings);
  } catch (const std::exception &exc) {
    std::clog << "EXCEPTION: " << exc.what();
    return EXIT_FAILURE;
  }
}
