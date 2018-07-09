// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions. */

#include <measurement_kit/ffi/ffi.h>

#include <stdlib.h>

#include <iostream>

int main(int argc, char **argv) {
  auto settings = R"({
    "inputs":["www.kernel.org"],
    "name":"WebConnectivity"
  })";
  auto taskp = mk_task_start(settings);
  while (!mk_task_is_done(taskp)) {
    auto eventp = mk_task_wait_for_next_event(taskp);
    if (!eventp) {
      break;
    }
    auto str = mk_event_serialize(eventp);
    if (!str) {
      mk_event_destroy(eventp);
      break;
    }
    std::clog << str << std::endl;
    mk_event_destroy(eventp);
  }
  mk_task_destroy(taskp);
}
