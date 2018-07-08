# Measurement Kit FFI API

Measurement Kit exposes a simple C like API suitable to be used via
[FFI](https://en.wikipedia.org/wiki/Foreign_function_interface).

As of MK v0.9.0, this API is still experimental. You should probably not
use this API directly, rather you should use the high level wrappers that
we have implemented for several languages. Specifically:

- for Android and Java you should use our [Java API](
  https://github.com/measurement-kit/android-libs);

- for Golang you should use our [Golang API](
  https://github.com/measurement-kit/go-measurement-kit);

- for C++11 and better, and Objective C, you should use our
  [C++11 API](../nettest/nettest.hpp).

## Introduction and synopsis

Measurement Kit is a network measurement engine. By default, as mentioned,
it exposes a FFI friendly C like API. To use this API, include
`<measurement_kit/ffi/ffi.h>`. See also the API documentation available
at [codedocs.xyz/measurement-kit/measurement-kit](
https://codedocs.xyz/measurement-kit/measurement-kit).

The FFI API allows you to run network tests (nettests). In the context of this
API, network tests are called _tasks_ (but the name is probably poised to
change before v1.0.0). Example tasks are [OONI's Web Connectivity](
https://github.com/ooni/spec/blob/master/test-specs/ts-017-web-connectivity.md
) or the [Network Diagnostic Test](
https://github.com/ooni/spec/blob/master/test-specs/ts-022-ndt.md).

To _start_ a task you call `mk_task_start` by passing it specific
_settings_ as a serialized JSON string.  All settings are optional,
except for the `name` of the task.  Ideally, you should have high
level code where the settings are a class that gets serialized to
a JSON string. This is, for example, what we do in the higher-level
APIs mentioned above.

Once started, a task will emit _events_. There are several kind of
events, the most common of which is `"log"` that identifies a log
line emitted by the task. Another event is `"status.update.performance"`,
which provides network performance information while a task for
measuring network performance is being run. See below for more
information on the specific events.

The task runs in a separate thread and posts events on a queue. You extract
events from such queue using `mk_task_wait_for_next_event`. This is a _blocking_
function that returns when a new event is posted into the queue. To
process an event, use `mk_event_serialize` to obtain its JSON serialization,
then parse the JSON into some high level data structure, and process it. See
the [C++14](../nettest/nettest.hpp) events processing code to have an idea of
how this could be implemented. (Or, if we have already written an API that
does that works for your use case, perhaps just use such API.)

You should loop processing events until `mk_task_is_done` returns nonzero. At
that point, the task is done, and attempting to extract further events from
the queue with `mk_task_wait_for_next_event` will immediately return the dummy
`status.terminated` event (equivalent to `EOF` for the task queue).

Since the FFI API is basically a C API, you need to manually manage memory
by freeing events and the task, once you are done with them. To this end, use
respectively, `mk_event_destroy` and `mk_task_destroy`.

## Examples

You can find working examples of usage of the FFI API inside the
[example/ffi](../../example/ffi) directory. Another usage example of
the FFI API is [nettest.hpp](../nettest/nettest.hpp), where we wrap the
FFI API into a more-user-friendly C++11 interface.

## Tasks

The following tasks are defined (case matters):

- `"CaptivePortal"`: [OONI's captive portal test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-010-captive-portal.md)

- `"Dash"`: [Neubot's DASH test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-021-dash.md)

- `"DnsInjection"`: [OONI's DNS injection test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-012-dns-injection.md)

- `"FacebookMessenger"`: [OONI's Facebook Messenger test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-019-facebook-messenger.md)

- `"HttpHeaderFieldManipulation"`: [OONI's HTTP header field manipulation test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-006-header-field-manipulation.md)

- `"HttpInvalidRequestLine"`: [OONI's HTTP invalid request line test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-007-http-invalid-request-line.md)

- `"MeekFrontedRequests"`: [OONI's meek fronted requests test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-014-meek-fronted-requests.md)

- `"MultiNdt"`: [the multi NDT network performance test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-022-ndt.md)

- `"Ndt"`: [the NDT network performance test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-022-ndt.md)

- `"TcpConnect"`: [OONI's TCP connect test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-008-tcp-connect.md)

- `"Telegram"`: [OONI's Telegram test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-020-telegram.md)

- `"WebConnectivity"`: [OONI's Web Connectivity test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-017-web-connectivity.md)

- `"Whatsapp"`: [OONI's WhatsApp test](
  https://github.com/ooni/spec/blob/master/test-specs/ts-018-whatsapp.md)

By following the links provided above, you can read detailed documentation on
the purpose of each task. The documentation also describes the JSON schema used
by each task to represent its results. As mentioned below, tasks results are
emitted as a serialized JSON under the `"measurement"` event.

## Settings

The task settings is a JSON like:

```JSON
{
  "annotations": {"campaign": "example", "city": "Rome"},
  "disabled_events": ["log", "measurement"],
  "inputs": ["www.google.com", "www.kernel.org"],
  "input_filepaths": ["./list-1.txt", "./list-7.txt", "./list-4.txt"],
  "log_filepath": "logfile.txt",
  "log_level": "INFO",
  "name": "WebConnectivity",
  "options": {},
  "output_filepath": "results.njson",
}
```

The only mandatory key is `name`, which identifies the task. The possible
task names have already been described above.

All the other keys are optional. We have omitted the context of the `options`
field, which is described in great detail below. The following keys are
available:

- `"annotations"`: (object)
Optional annotations (i.e. key, value string pairs) that will be included into
the JSON report sent to the OONI collector.

- `"disabled_events"`: (array)
List of events that will not be emitted.

- `"inputs"`: (array)
List of URLs or domains required by the test.

- `"input_filepaths"`: (array)
List of files from which to read inputs.

- `"log_filepath"`: (string)
File where to write log messages.

- `"log_level"`: (string)
Type of log messages you are interested into.

- `"name"`: (string; mandatory)
Name of the network test to run.

- `"options"`: (object)
Optional variables influencing the nettest behavior.

- `"output_filepath"`: (string)
File where to write the nettest results.

In the following sections, we will describe in greater detail the available
log levels, options, and events.

## Log levels

The available log levels are:

- `"ERR"`: Only emit error messages.

- `"WARNING"`: Also emit warning messages.

- `"INFO"`: Also emit informational messages.

- `"DEBUG"`: Also emit debug messages.

- `"DEBUG2"`: Emit all log messages.

When you specify a log level in the settings, only messages with a log level
equal or greater than the specified one are emitted. For example, if you
specify `"INFO"`, you will only see `"ERR"`, `"WARNING"`, and `"INFO"` logs.

## Options

Options are actually settings. They are distinct in this specification for
implementation reasons. However, higher level APIs SHOULD present options and
settings as a single class containing all the values that can be set.

Options can be `string`, `float`, or `int`. There is no boolean type: we use
`int`s with boolean semantics in some cases, with the usual convention that `0`
means false and non-`0` (typically `1`) means true.

These are the available options that affect all nettests:

- `"bouncer_base_url"`: (string)
Base URL of the OONI bouncer. This base URL is used to construct the full URL
required to contact the OONI bouncer and get test specific info like test
helpers and test collectors.

- `"collector_base_url"`: (string)
Base URL of the OONI collector. This base URL is used to construct the full URL
required to contact manage the report submission with the collector. By default
this option is not set because we use the bouncer to retrieve the collector
base URL.

- `"dns/nameserver"`: (string)
DNS resolver IP address. By setting this option you will force MK to use that
DNS resolver for resolving domain names to IP addresses. For this setting to
work you should use a DNS engine different from the "system" engine. By default
this option is not set, as we use the system engine as our default DNS engine.

- `"dns/engine"`: (string)
What DNS engine to use. The "system" engine implies that `getaddrinfo()` is
used. If you set this setting to "libevent" and you also configure the
"dns/nameserver" option, MK will use libevent and the specified nameserver to
resolve domain names.

- `"geoip_asn_path"`: (string)
Path to the GeoIP ASN (Autonomous System Number) database file. By default this
option is empty. If you do not change this option to contain the path to a
suitable database file, MK will not be able to map the user's IP address to an
ASN.

- `"geoip_country_path"`: (string)
Path to the GeoIP country database file. By default this option is empty. If
you do not change it to contain the path to a suitable database file, MK will
not be able to map the user's IP to a country code.

- `"ignore_bouncer_error"`: (int)
Whether to ignore bouncer errors. If this option is true, then MK will not stop
after failing to contact the OONI bouncer. Without the information provided by
the bouncer, OONI tests that require a test helper will certainly fail, while
other tests will just fail to submit their results to a collector, unless you
manually configure a collector base URL.

- `"ignore_open_report_error"`: (int)
Whether to ignore errors opening the report with the OONI collector.

- `"max_runtime"`: (float)
Max run time for nettests taking input. When you are running a nettest taking
input, the test will stop after the number of seconds specified by this option
has passed (plus some extra time required to interrupt the testing engine).
Setting this option to a negative value lets the test run as long as necessary
to exhaust its input list.

- `"net/ca_bundle_path"`: (string)
Path to the CA used to validate SSL certificates. This is not necessary where
we use LibreSSL, because in such cases we include a CA bundle directly inside
of the MK binary. This happens for Android, iOS, and Windows systems. If this
option is not set and we're not using LibreSSL, then attempting to connect to
any website using HTTPS will fail.

- `"net/timeout"`: (float)
Number of seconds after which network I/O operations (i.e. connect, recv, send)
will timeout and return an error.

- `"no_bouncer"`: (int)
Whether to avoid using a bouncer. Not using a bouncer means we will not
discover the base URL of a suitable collector and of test helpers. OONI tests
that require test helpers will fail if you disable the bouncer. Other tests
will just not be able to submit results to a collector, unless you manually
configure a collector base URL.

- `"no_collector"`: (int)
Whether to avoid using a collector. If true, it means that the test results are
not submitted to a collector (by default the OONI collector) for archival or
publishing purposes. All measurements submitted to the OONI collector are
published within a few business days.

- `"no_asn_lookup"`: (int)
Whether to avoid the the user's ASN (Autonomous System Number) lookup.

- `"no_cc_lookup"`: (int)
Whether to avoid the user's country code lookup.

- `"no_ip_lookup"`: (int)
Whether to avoid looking up the user's IP. Not knowing it prevents us from
looking up the ASN (Autonomous System Number) and the country code. Most
importantly, this also prevents us from attempting to scrub the IP address from
measurements results, which may be a concern for censorship tests.

- `"no_file_report"`: (int)
Whether to avoid writing a report file to disk.

- `"no_resolver_lookup"`: (int)
Whether to avoid looking up the resolver IP address.

- `"probe_asn"`: (string)
The ASN (Autonomous System Number) in which we are. If you set this, we will of
course skip the user's ASN lookup.

- `"probe_cc"`: (string)
The country code in which we are. If you set this, we will of course skip the
user's country code lookup.

- `"probe_ip"`: (string)
The user's IP. If you set this, we will of course skip the user's IP lookup.

- `"randomize_input"`: (int)
Whether to randomize the provided input.

- `"save_real_probe_asn"`: (int)
Whether to save the user's ASN (Autonomous System Number) in the report.

- `"save_real_probe_cc"`: (int)
Whether to save the user's country code in the report.

- `"save_real_probe_ip"`: (int)
Whether to save the user's IP in the report.

- `"save_real_resolver_ip"`: (int)
Whether to save the user's resolver IP in the report.

- `"software_name"`: (string)
Name of the application.

- `"software_version"`: (string)
Version of the application. By default this is an empty string. If you do not
set this variable, the current MK version will be used.

The following is an example JSON where all the common options that affect
all nettests have been listed along with their default value:

```JSON
{
  "bouncer_base_url": "https://bouncer.ooni.io",
  "collector_base_url": "",
  "dns/nameserver": "",
  "dns/engine": "system",
  "geoip_asn_path": "",
  "geoip_country_path": "",
  "ignore_bouncer_error": 1,
  "ignore_open_report_error": 1,
  "max_runtime": -1.0,
  "net/ca_bundle_path": "",
  "net/timeout": 10.0,
  "no_bouncer": 0,
  "no_collector": 0,
  "no_asn_lookup": 0,
  "no_cc_lookup": 0,
  "no_ip_lookup": 0,
  "no_file_report": 0,
  "no_resolver_lookup": 0,
  "probe_asn": "",
  "probe_cc": "",
  "probe_ip": "",
  "randomize_input": 1,
  "save_real_probe_asn": 1,
  "save_real_probe_cc": 1,
  "save_real_probe_ip": 0,
  "save_real_resolver_ip": 1,
  "software_name": "measurement_kit",
  "software_version": "",
}
```

We will now proceed to describe the options specific to each test.

### Whatsapp options

- `"all_endpoints"`: (int)
Whether to check all WhatsApp endpoints. Default value: 0.

## Events

An event is a JSON object like:

```JSON
{
  "key": "<key>",
  "value": {}
}
```

Where `"value"` is a JSON object with an event-specific structure, and `"key"`
is a string. Below we describe all the possible event keys, along with the
"value" JSON structure. Unless otherwise specified, an event key can be emitted
an arbitrary number of times during the lifecycle of a task. Unless otherwise
specified, all the keys introduced below where added in MK v0.9.0.

The following events are defined:

- `"failure.asn_lookup"`: (object) [documentation](#failureasn_lookup)

- `"failure.cc_lookup"`: (object) [documentation](#failurecc_lookup)

- `"failure.ip_lookup"`: (object) [documentation](#failureip_lookup)

- `"failure.measurement"`: (object) [documentation](#failuremeasurement)

- `"failure.measurement_submission"`: (object) [documentation](#failuremeasurement_submission)

- `"failure.report_create"`: (object) [documentation](#failurereport_create)

- `"failure.report_close"`: (object) [documentation](#failurereport_close)

- `"failure.resolver_lookup"`: (object) [documentation](#failureresolver_lookup)

- `"failure.startup"`: (object) [documentation](#failurestartup)

- `"log"`: (object) [documentation](#log)

- `"measurement"`: (object) [documentation](#measurement)

- `"status.end"`: (object) [documentation](#statusend)

- `"status.geoip_lookup"`: (object) [documentation](#statusgeoip_lookup)

- `"status.progress"`: (object) [documentation](#statusprogress)

- `"status.queued"`: (object) [documentation](#statusqueued)

- `"status.measurement_start"`: (object) [documentation](#statusmeasurement_start)

- `"status.measurement_submission"`: (object) [documentation](#statusmeasurement_submission)

- `"status.measurement_done"`: (object) [documentation](#statusmeasurement_done)

- `"status.report_close"`: (object) [documentation](#statusreport_close)

- `"status.report_create"`: (object) [documentation](#statusreport_create)

- `"status.resolver_lookup"`: (object) [documentation](#statusresolver_lookup)

- `"status.started"`: (object) [documentation](#statusstarted)

- `"status.update_performance"`: (object) [documentation](#statusupdate_performance)

- `"status.update.websites"`: (object) [documentation](#statusupdatewebsites)

- `"task_terminated"`: (object) [documentation](#task_terminated)

Below we provide a detailed description of each event.

### failure.asn_lookup

We could not lookup the ASN (Autonomous System Number) from the user's IP.

This event includes the following attributes:

1. `"failure"`: (string)
The specific error that occurred.

The JSON returned by this event is like:

```JSON
{
  "key": "failure.asn_lookup",
  "value": {  
    "failure": ""
  }
}
```

### failure.cc_lookup

We could not lookup the country code from the user's IP.

This event includes the following attributes:

1. `"failure"`: (string)
The specific error that occurred.

The JSON returned by this event is like:

```JSON
{
  "key": "failure.cc_lookup",
  "value": {  
    "failure": ""
  }
}
```

### failure.ip_lookup

We could not lookup the user IP address.

This event includes the following attributes:

1. `"failure"`: (string)
The specific error that occurred.

The JSON returned by this event is like:

```JSON
{
  "key": "failure.ip_lookup",
  "value": {  
    "failure": ""
  }
}
```

### failure.measurement

There was a failure running the measurement.

This event includes the following attributes:

1. `"failure"`: (string)
The specific error that occurred.

The JSON returned by this event is like:

```JSON
{
  "key": "failure.measurement",
  "value": {  
    "failure": ""
  }
}
```

### failure.measurement_submission

There was a failure in submitting the measurement result to the configured
collector.

This event includes the following attributes:

1. `"failure"`: (string)
The specific error that occurred.

1. `"idx"`: (int)
Index of the measurement that failed

1. `"json_str"`: (string)
Measurement that we could not submit as a serialized JSON.

The JSON returned by this event is like:

```JSON
{
  "key": "failure.measurement_submission",
  "value": {  
    "failure": "",
    "idx": 0,
    "json_str": ""
  }
}
```

### failure.report_create

There was a failure in getting an ID for submitting results from the configured
collector.

This event includes the following attributes:

1. `"failure"`: (string)
The specific error that occurred.

The JSON returned by this event is like:

```JSON
{
  "key": "failure.report_create",
  "value": {  
    "failure": ""
  }
}
```

### failure.report_close

There was a failure in telling the configured collector that all the
measurements related to a specific ID have now been performed.

This event includes the following attributes:

1. `"failure"`: (string)
The specific error that occurred.

The JSON returned by this event is like:

```JSON
{
  "key": "failure.report_close",
  "value": {  
    "failure": ""
  }
}
```

### failure.resolver_lookup

There was a failure attempting to lookup the user DNS resolver IP address.

This event includes the following attributes:

1. `"failure"`: (string)
The specific error that occurred.

The JSON returned by this event is like:

```JSON
{
  "key": "failure.resolver_lookup",
  "value": {  
    "failure": ""
  }
}
```

### failure.startup

There was a failure in starting the nettest, most likely because you passed
incorrect options. See the logs for more information of what went wrong.

This event includes the following attributes:

1. `"failure"`: (string)
The specific error that occurred.

The JSON returned by this event is like:

```JSON
{
  "key": "failure.startup",
  "value": {  
    "failure": ""
  }
}
```

### log

A log line that was emitted.

This event includes the following attributes:

1. `"log_level"`: (string)
The log level as a string (e.g. "INFO").

1. `"message"`: (string)
The log message.

The JSON returned by this event is like:

```JSON
{
  "key": "log",
  "value": {  
    "log_level": "",
    "message": ""
  }
}
```

### measurement

The result of a measurement.

This event includes the following attributes:

1. `"idx"`: (int)
Index of the current measurement

1. `"json_str"`: (string)
The measurement result as a serialized JSON.

The JSON returned by this event is like:

```JSON
{
  "key": "measurement",
  "value": {  
    "idx": 0,
    "json_str": ""
  }
}
```

### status.end

Event emitted once at the end of the nettest. This event is always emitted,
regardless of whether the nettest naturally reaches its end or is interrupted.
As such, you can rely on this event as a "once" suitable for releasing all the
extra resources you may have allocated as part of the nettest lifecyle.

This event includes the following attributes:

1. `"downloaded_kb"`: (float)
The number of KB downloaded during the test.

1. `"uploaded_kb"`: (float)
The number of KB uploaded during the test.

1. `"failure"`: (string)
The error that occurred. If no error occurred, then this variable will hold an
empty string.

The JSON returned by this event is like:

```JSON
{
  "key": "status.end",
  "value": {  
    "downloaded_kb": 0.0,
    "uploaded_kb": 0.0,
    "failure": ""
  }
}
```

### status.geoip_lookup

Event emitted once, when we discover the geolocation of the user based on their
IP address.

This event includes the following attributes:

1. `"probe_ip"`: (string)
The user IP address

1. `"probe_asn"`: (string)
The user ASN (Autonomous System Number)

1. `"probe_cc"`: (string)
The user country code (CC).

1. `"probe_network_name"`: (string)
The descriptive name associated to the ASN

The JSON returned by this event is like:

```JSON
{
  "key": "status.geoip_lookup",
  "value": {  
    "probe_ip": "",
    "probe_asn": "",
    "probe_cc": "",
    "probe_network_name": ""
  }
}
```

### status.progress

Emitted during the task lifecycle to indicate progress.

This event includes the following attributes:

1. `"percentage"`: (float)
Percentage of completion of the task.

1. `"message"`: (string)
Optional message indicating what step is now complete.

The JSON returned by this event is like:

```JSON
{
  "key": "status.progress",
  "value": {  
    "percentage": 0.0,
    "message": ""
  }
}
```

### status.queued

Emitted once to indicate that the tast has been submitted for running. Unless
you run multiple test at the same time (which is discouraged), this event also
implies that the test will be started immediately.


The JSON returned by this event is like:

```JSON
{
  "key": "status.queued",
  "value": { 
  }
}
```

### status.measurement_start

Emitted when we start a new measurement within a nettest. For nettests that do
not require input, there is just a single measurement within a nettest.
Otherwise, there is a measurement for each input provided to the nettest.

This event includes the following attributes:

1. `"idx"`: (int)
Index of the current measurement.

1. `"input"`: (string)
Input of the current measurement. For nettests that do not take input, this
will be the empty string.

The JSON returned by this event is like:

```JSON
{
  "key": "status.measurement_start",
  "value": {  
    "idx": 0,
    "input": ""
  }
}
```

### status.measurement_submission

Emitted when the result of a measurement has been successfully submitted to the
configured collector.

This event includes the following attributes:

1. `"idx"`: (int)
Index of the current measurement.

The JSON returned by this event is like:

```JSON
{
  "key": "status.measurement_submission",
  "value": {  
    "idx": 0
  }
}
```

### status.measurement_done

Emitted when a measurement is done. This is emitted regardless of whether there
were any failures during the measurement.

This event includes the following attributes:

1. `"idx"`: (int)
Index of the current measurement.

The JSON returned by this event is like:

```JSON
{
  "key": "status.measurement_done",
  "value": {  
    "idx": 0
  }
}
```

### status.report_close

Emitted when we have notified the collector that we are done with running
measurements with a specific report ID.

This event includes the following attributes:

1. `"report_id"`: (string)
Unique identifier of the nettest with the collector.

The JSON returned by this event is like:

```JSON
{
  "key": "status.report_close",
  "value": {  
    "report_id": ""
  }
}
```

### status.report_create

Emitted when we have notified the collector the intention to start submitting
measurements. As part of this API call, we receive back a "report ID" to be
used to submit subsequent measurements that we perform.

This event includes the following attributes:

1. `"report_id"`: (string)
Unique identifier of the nettest with the collector.

The JSON returned by this event is like:

```JSON
{
  "key": "status.report_create",
  "value": {  
    "report_id": ""
  }
}
```

### status.resolver_lookup

Emitted once when we discover the user DNS resolver IP.

This event includes the following attributes:

1. `"ip_address"`: (string)
IP address of the user resolver.

The JSON returned by this event is like:

```JSON
{
  "key": "status.resolver_lookup",
  "value": {  
    "ip_address": ""
  }
}
```

### status.started

Emitted once when the nettest has started running.


The JSON returned by this event is like:

```JSON
{
  "key": "status.started",
  "value": { 
  }
}
```

### status.update_performance

Status update regarding the currently ongoing network performance measurement.
This event is, of course, only emitted by network tests that measure the
network performance.

This event includes the following attributes:

1. `"direction"`: (string)
The direction of the performance measurement. Either 'download', for download
measurements, or 'upload' for upload measurements.

1. `"elapsed"`: (float)
Seconds elapsed since the performance measurement was started.

1. `"num_streams"`: (int)
Number of parallel TCP streams being used.

1. `"speed_kbps"`: (float)
Speed measured in kbit/s.

The JSON returned by this event is like:

```JSON
{
  "key": "status.update_performance",
  "value": {  
    "direction": "",
    "elapsed": 0.0,
    "num_streams": 0,
    "speed_kbps": 0.0
  }
}
```

### status.update.websites

Status update regarding the currently ongoing website censorship measurement.

This event includes the following attributes:

1. `"url"`: (string)
URL that we are measuring.

1. `"status"`: (string)
Result of the measurement. Either "accessible" or "blocking".

The JSON returned by this event is like:

```JSON
{
  "key": "status.update.websites",
  "value": {  
    "url": "",
    "status": ""
  }
}
```

### task_terminated

Emitted when a nettest is done and you attempt using the FFI API to extract
more tasks from its queue.


The JSON returned by this event is like:

```JSON
{
  "key": "task_terminated",
  "value": { 
  }
}
```


## Task pseudocode

The following illustrates in pseudocode the operations performed by a task
once you call `mk_task_start`. It not 100% accurate; in particular, we have
omitted the code that generates most log messages. This pseudocode is meant to
help you understand how Measurement Kit works internally, and specifically how all
the settings described above interact together when you specify them for
running Measurement Kit tasks. We are using pseudo JavaScript because that
is the easiest language to show manipulation of JSON objects such as the
`settings` object.

As mentioned, a task run in its own thread. It first validate settings, then
it opens the logfile (if needed), and finally it waits in queue until other
possibly running tasks terminate. The `finish` function will be called when the
task is done, and will emit all the events emitted at the end of a task.

```JavaScript
function taskThread(settings) {
  emitEvent("status.queued", {})
  semaphore.Acquire()                 // blocked until my turn

  let finish = function(error) {
    semaphore.Release()               // allow another test to run
    emitEvent("status.end", {
      downloaded_kb: countDownloadedKb(),
      uploaded_kb: countUploadedKb(),
      failure: (error) ? error.AsString() : null
    })
  }

  if (!settingsAreValid(settings)) {
    emitEvent("failure.startup", {
      failure: "value_error",
    })
    finish("value_error")
    return
  }

  if (settings.log_filepath != "") {
    // TODO(bassosimone): we should decide whether we want to deal with the
    // case where we cannot write into the log file. Currently we don't.
    openLogFile(settings.log_filepath)
  }

  let task = makeTask(settings.name)

  emitEvent("status.started", {})


```

After all this setup, a task contacts the OONI bouncer, lookups the IP address,
the country code, the autonomous system number, and the resolver lookup. All
these information end up in the JSON measurement. Also, all these operations can
be explicitly disabled by setting the appropriate settings.

```JavaScript
  let test_helpers = test.defaultTestHelpers()
  if (!settings.options.no_bouncer) {
    if (settings.options.bouncer_base_url == "") {
      settings.options.bouncer_base_url = defaultBouncerBaseURL()
    }
    let error
    [test_helpers, error] = queryOONIBouncer(settings)
    if (error) {
      emitWarning(settings, "cannot query OONI bouncer")
      if (!settings.options.ignore_bouncer_error) {
        finish(error)
        return
      }
    }
  }

  // TODO(bassosimone): we should make sure the progress described here
  // is consistent with the one emitted by the real code.
  emitProgress(0.1, "contacted bouncer")

  let probe_ip = "127.0.0.1"
  if (settings.options.probe_ip != "") {
    probe_ip = settings.options.probe_ip
  } else if (!settings.options.no_ip_lookup) {
    let error
    [probe_ip, error] = lookupIP(settings)
    if (error) {
      emitEvent("failure.ip_lookup", {
        failure: error.AsString()
      })
      emitWarning(settings, "cannot lookup probe IP")
    }
  }

  let probe_asn = "AS0",
      probe_network_name = "Unknown"
  if (settings.options.probe_asn != "") {
    probe_asn = settings.options.probe_asn
  } else if (!settings.options.no_asn_lookup &&
             settings.options.geoip_asn_path != "") {
    let error
    [probe_asn, probe_network_name, error] = lookupASN(settings)
    if (error) {
      emitEvent("failure.asn_lookup", {
        failure: error.AsString()
      })
      emitWarning(settings, "cannot lookup probe ASN")
    }
  }

  let probe_cc = "ZZ"
  if (settings.options.probe_cc != "") {
    probe_cc = settings.options.probe_cc
  } else if (!settings.options.no_cc_lookup &&
             settings.options.geoip_country_path != "") {
    let error
    [probe_cc, error] = lookupCC(settings)
    if (error) {
      emitEvent("failure.cc_lookup", {
        failure: error.AsString()
      })
      emitWarning(settings, "cannot lookup probe CC")
    }
  }

  emitEvent("status.geoip_lookup", {
    probe_ip: probe_ip,
    probe_asn: probe_asn,
    probe_network_name: probe_network_name,
    probe_cc: probe_cc
  })

  emitProgress(0.2, "geoip lookup")

  // TODO(bassosimone): take decision wrt null vs. ""
  let resolver_ip = null
  if (!settings.options.no_resolver_lookup) {
    let error
    [resolver_ip, error] = lookupResolver(settings)
    if (error) {
      emitEvent("failure.resolver_lookup", {
        failure: error.AsString()
      })
      emitWarning(settings, "cannot lookup resolver IP")
    }
  }

  emitEvent("status.resolver_lookup", {
    resolver_ip: resolver_ip
  })
  emitProgress(0.3, "resolver lookup")
```

Then, Measurement Kit opens the report file on disk, which will contain
the measurements, each serialized on a JSON on its own line. It will also
contact the OONI bouncer and obtain a report-ID for the report.

```JavaScript
  if (!settings.options.no_file_report) {
    if (settings.output_filepath == "") {
      settings.output_filepath = makeDefaultOutputFilepath(settings);
    }
    let error = openFileReport(settings.output_filepath)
    if (error) {
      emitWarning(settings, "cannot open file report")
      finish(error)
      return
    }
  }

  let report_id
  if (!settings.options.no_collector) {
    if (settings.options.collector_base_url == "") {
      settings.options.collector_base_url = defaultCollectorBaseURL();
    }
    let error
    [report_id, error] = collectorOpenReport(settings)
    if (error) {
      emitWarning("cannot open report with OONI collector")
      emitEvent("failure.report_create", {
        failure: error.AsString()
      })
      if (!settings.options.ignore_open_report_error) {
        finish(error)
        return
      }
    } else {
      emitEvent("status.report_create", {
        report_id: report_id
      })
    }
  }

  emitProgress(0.4, "open report")
```

Then comes input processing. Measurement Kit assembles a list of inputs to
process. If the test do not take any input, we fake a single input entry
consisting of the empty string, implying that this test needs to perform just
a single iteration. (This is a somewhat internal detail, but it explains
some events with `idx` equal to `0` and `input` equal to an empty string.)

```JavaScript
  for (let i = 0; i < settings.input_filepaths.length; ++i) {
    let [inputs, error] = readInputFile(settings.input_filepaths[i])
    if (error) {
      emitWarning("cannot read input file")
      finish(error)
      return
    }
    settings.inputs = settings.inputs.concat(inputs)
  }
  if (settings.inputs.length <= 0) {
    if (task.needs_input) {
      emitWarning(settings, "no input provided")
      finish(Error("value_error"))
      return
    }
    settings.inputs.push("") // empty input for input-less tests
  }
  if (settings.options.randomize_input) {
    shuffle(settings.input)
  }
```

Then, Measurement Kit iterates over all the input and runs the function
implementing the specified task on each input.

```JavaScript
  let begin = timeNow()
  for (let i = 0; i < settings.inputs; ++i) {
    let currentTime = timeNow()
    if (settings.options.max_runtime >= 0 &&
        currentTime - begin > settings.options.max_runtime) {
      emitWarning("exceeded maximum runtime")
      break
    }
    emitEvent("status.measurement_start", {
      idx: i,
      input: settings.inputs[i]
    })
    let measurement = Measurement()
    measurement.annotations = settings.annotations
    measurement.annotations.engine_name = "libmeasurement_kit"
    measurement.annotations.engine_version = mkVersion()
    measurement.annotations.engine_version_full = mkVersionFull()
    measurement.annotations.platform = platformName()
    measurement.annotations.probe_network_name = settings.options.save_real_probe_asn
                                                  ? probe_network_name : "Unknown"
    measurement.id = UUID4()
    measurement.input = settings.inputs[i]
    measurement.input_hashes = []
    measurement.measurement_start_time = currentTime
    measurement.options = []
    measurement.probe_asn = settings.options.save_real_probe_asn ? probe_asn : "AS0"
    measurement.probe_cc = settings.options.save_real_probe_cc ? probe_cc : "ZZ"
    measurement.probe_ip = settings.options.save_real_probe_ip
                              ? probe_ip : "127.0.0.1"
    measurement.report_id = report_id
    measurement.sotfware_name = settings.options.software_name
    measurement.sotfware_version = settings.options.software_version
    measurement.test_helpers = test_helpers
    measurement.test_name = test.AsOONITestName()
    measurement.test_start_time = begin
    measurement.test_verson = test.Version()
    let [test_keys, error] = task.Run(
          settings.inputs[i], settings, test_helpers)
    measurement.test_runtime = timeNow() - currentTime
    measurement.test_keys = test_keys
    measurement.test_keys.resolver_ip = settings.options.save_resolver_ip
                                          ? resolve_ip : "127.0.0.1"
    if (error) {
      emitEvent("failure.measurement", {
        failure: error.AsString(),
        idx: i,
        input: settings.inputs[i]
      })
    }
    emitEvent("measurement", {
      json_str: measurement.asJSON(),
      idx: i,
      input: settings.inputs[i]
    })
    if (!settings.options.no_file_report) {
      let error = writeReportToFile(measurement)
      if (error) {
        emitWarning("cannot write report to file")
        finish(error)
        return
      }
    }
    if (!settings.options.no_collector) {
      let error = submitMeasurementToOONICollector(measurement)
      if (error) {
        emitEvent("failure.measurement_submission", {
          idx: i,
          input: settings.inputs[i],
          json_str: measurement.asJSON(),
          failure: error.AsString()
        })
      } else {
        emitEvent("status.measurement_submission", {
          idx: i,
          input: settings.inputs[i],
        })
      }
    }
    emitEvent("status.measurement_done", {
      idx: i
    })
  }
```

Finally, Measurement Kit ends the test by closing the local results file
and the remote report managed by the OONI collector.

```JavaScript
  emitProgress(0.9, "ending the test")

  if (!settings.options.no_file_report) {
    error = closeFileReport()
    if (error) {
      emitWarning("cannot close file report")
      finish(error)
      return
    }
  }
  if (!settings.options.no_collector) {
    let error = closeRemoteReport()
    if (error) {
      emitEvent("failure.report_close", {
        failure: error.AsString()
      })
      emitWarning("cannot close remote report with OONI collector")
    } else {
      emitEvent("status.report_close", {
        report_id: report_id
      })
    }
  }

  finish()
}
```
