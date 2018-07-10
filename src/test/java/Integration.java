// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.

package main;

import io.ooni.mk.nettest.Runner;
import io.ooni.mk.nettest.event.LogEvent;
import io.ooni.mk.nettest.event.StatusProgressEvent;
import io.ooni.mk.nettest.event.StatusQueuedEvent;
import io.ooni.mk.nettest.settings.WebConnectivitySettings;

public class Integration {
  static class MyRunner extends Runner {
    public void onLog(LogEvent e) {
      System.out.println("LOG: <" + e.logLevel + "> " + e.message);
    }

    public void onStatusProgress(StatusProgressEvent e) {
      System.out.println("PROGRESS: " + e.percentage + " " + e.message);
    }

    public void onStatusQueued(StatusQueuedEvent e) {
      System.out.println("QUEUED");
    }
  }

  public static void main(String[] args) {
    System.loadLibrary("measurementkit-jni");
    WebConnectivitySettings settings = new WebConnectivitySettings();
    settings.inputs.add("www.kernel.org");
    for (String v : args) {
      settings.inputs.add(v);
    }
    MyRunner runner = new MyRunner();
    runner.run(runner.prepareWebConnectivity(settings));
  }
}
