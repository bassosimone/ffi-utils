// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.

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
 */

package io.ooni.mk.nettest;

class RunnerWrapper extends io.ooni.mk.nettest.swig.Runner {
  public RunnerWrapper(Runner parent) {
    this.parent = parent;
  }

  @Override
  public void on_failure_asn_lookup(io.ooni.mk.nettest.swig.FailureAsnLookup swigEvent) {
    io.ooni.mk.nettest.event.FailureAsnLookup event = new io.ooni.mk.nettest.event.FailureAsnLookup();
    event.failure = swigEvent.getFailure();
    parent.onFailureAsnLookup(event);
  }

  @Override
  public void on_failure_cc_lookup(io.ooni.mk.nettest.swig.FailureCcLookup swigEvent) {
    io.ooni.mk.nettest.event.FailureCcLookup event = new io.ooni.mk.nettest.event.FailureCcLookup();
    event.failure = swigEvent.getFailure();
    parent.onFailureCcLookup(event);
  }

  @Override
  public void on_failure_ip_lookup(io.ooni.mk.nettest.swig.FailureIpLookup swigEvent) {
    io.ooni.mk.nettest.event.FailureIpLookup event = new io.ooni.mk.nettest.event.FailureIpLookup();
    event.failure = swigEvent.getFailure();
    parent.onFailureIpLookup(event);
  }

  @Override
  public void on_failure_measurement(io.ooni.mk.nettest.swig.FailureMeasurement swigEvent) {
    io.ooni.mk.nettest.event.FailureMeasurement event = new io.ooni.mk.nettest.event.FailureMeasurement();
    event.failure = swigEvent.getFailure();
    parent.onFailureMeasurement(event);
  }

  @Override
  public void on_failure_measurement_submission(io.ooni.mk.nettest.swig.FailureMeasurementSubmission swigEvent) {
    io.ooni.mk.nettest.event.FailureMeasurementSubmission event = new io.ooni.mk.nettest.event.FailureMeasurementSubmission();
    event.failure = swigEvent.getFailure();
    event.idx = swigEvent.getIdx();
    event.jsonStr = swigEvent.getJson_str();
    parent.onFailureMeasurementSubmission(event);
  }

  @Override
  public void on_failure_report_create(io.ooni.mk.nettest.swig.FailureReportCreate swigEvent) {
    io.ooni.mk.nettest.event.FailureReportCreate event = new io.ooni.mk.nettest.event.FailureReportCreate();
    event.failure = swigEvent.getFailure();
    parent.onFailureReportCreate(event);
  }

  @Override
  public void on_failure_report_close(io.ooni.mk.nettest.swig.FailureReportClose swigEvent) {
    io.ooni.mk.nettest.event.FailureReportClose event = new io.ooni.mk.nettest.event.FailureReportClose();
    event.failure = swigEvent.getFailure();
    parent.onFailureReportClose(event);
  }

  @Override
  public void on_failure_resolver_lookup(io.ooni.mk.nettest.swig.FailureResolverLookup swigEvent) {
    io.ooni.mk.nettest.event.FailureResolverLookup event = new io.ooni.mk.nettest.event.FailureResolverLookup();
    event.failure = swigEvent.getFailure();
    parent.onFailureResolverLookup(event);
  }

  @Override
  public void on_failure_startup(io.ooni.mk.nettest.swig.FailureStartup swigEvent) {
    io.ooni.mk.nettest.event.FailureStartup event = new io.ooni.mk.nettest.event.FailureStartup();
    event.failure = swigEvent.getFailure();
    parent.onFailureStartup(event);
  }

  @Override
  public void on_log(io.ooni.mk.nettest.swig.Log swigEvent) {
    io.ooni.mk.nettest.event.Log event = new io.ooni.mk.nettest.event.Log();
    event.logLevel = swigEvent.getLog_level();
    event.message = swigEvent.getMessage();
    parent.onLog(event);
  }

  @Override
  public void on_measurement(io.ooni.mk.nettest.swig.Measurement swigEvent) {
    io.ooni.mk.nettest.event.Measurement event = new io.ooni.mk.nettest.event.Measurement();
    event.idx = swigEvent.getIdx();
    event.jsonStr = swigEvent.getJson_str();
    parent.onMeasurement(event);
  }

  @Override
  public void on_status_end(io.ooni.mk.nettest.swig.StatusEnd swigEvent) {
    io.ooni.mk.nettest.event.StatusEnd event = new io.ooni.mk.nettest.event.StatusEnd();
    event.downloadedKb = swigEvent.getDownloaded_kb();
    event.uploadedKb = swigEvent.getUploaded_kb();
    event.failure = swigEvent.getFailure();
    parent.onStatusEnd(event);
  }

  @Override
  public void on_status_geoip_lookup(io.ooni.mk.nettest.swig.StatusGeoipLookup swigEvent) {
    io.ooni.mk.nettest.event.StatusGeoipLookup event = new io.ooni.mk.nettest.event.StatusGeoipLookup();
    event.probeIp = swigEvent.getProbe_ip();
    event.probeAsn = swigEvent.getProbe_asn();
    event.probeCc = swigEvent.getProbe_cc();
    event.probeNetworkName = swigEvent.getProbe_network_name();
    parent.onStatusGeoipLookup(event);
  }

  @Override
  public void on_status_progress(io.ooni.mk.nettest.swig.StatusProgress swigEvent) {
    io.ooni.mk.nettest.event.StatusProgress event = new io.ooni.mk.nettest.event.StatusProgress();
    event.percentage = swigEvent.getPercentage();
    event.message = swigEvent.getMessage();
    parent.onStatusProgress(event);
  }

  @Override
  public void on_status_queued(io.ooni.mk.nettest.swig.StatusQueued swigEvent) {
    io.ooni.mk.nettest.event.StatusQueued event = new io.ooni.mk.nettest.event.StatusQueued();
    /* No event specific attributes */
    parent.onStatusQueued(event);
  }

  @Override
  public void on_status_measurement_start(io.ooni.mk.nettest.swig.StatusMeasurementStart swigEvent) {
    io.ooni.mk.nettest.event.StatusMeasurementStart event = new io.ooni.mk.nettest.event.StatusMeasurementStart();
    event.idx = swigEvent.getIdx();
    event.input = swigEvent.getInput();
    parent.onStatusMeasurementStart(event);
  }

  @Override
  public void on_status_measurement_submission(io.ooni.mk.nettest.swig.StatusMeasurementSubmission swigEvent) {
    io.ooni.mk.nettest.event.StatusMeasurementSubmission event = new io.ooni.mk.nettest.event.StatusMeasurementSubmission();
    event.idx = swigEvent.getIdx();
    parent.onStatusMeasurementSubmission(event);
  }

  @Override
  public void on_status_measurement_done(io.ooni.mk.nettest.swig.StatusMeasurementDone swigEvent) {
    io.ooni.mk.nettest.event.StatusMeasurementDone event = new io.ooni.mk.nettest.event.StatusMeasurementDone();
    event.idx = swigEvent.getIdx();
    parent.onStatusMeasurementDone(event);
  }

  @Override
  public void on_status_report_close(io.ooni.mk.nettest.swig.StatusReportClose swigEvent) {
    io.ooni.mk.nettest.event.StatusReportClose event = new io.ooni.mk.nettest.event.StatusReportClose();
    event.reportId = swigEvent.getReport_id();
    parent.onStatusReportClose(event);
  }

  @Override
  public void on_status_report_create(io.ooni.mk.nettest.swig.StatusReportCreate swigEvent) {
    io.ooni.mk.nettest.event.StatusReportCreate event = new io.ooni.mk.nettest.event.StatusReportCreate();
    event.reportId = swigEvent.getReport_id();
    parent.onStatusReportCreate(event);
  }

  @Override
  public void on_status_resolver_lookup(io.ooni.mk.nettest.swig.StatusResolverLookup swigEvent) {
    io.ooni.mk.nettest.event.StatusResolverLookup event = new io.ooni.mk.nettest.event.StatusResolverLookup();
    event.ipAddress = swigEvent.getIp_address();
    parent.onStatusResolverLookup(event);
  }

  @Override
  public void on_status_started(io.ooni.mk.nettest.swig.StatusStarted swigEvent) {
    io.ooni.mk.nettest.event.StatusStarted event = new io.ooni.mk.nettest.event.StatusStarted();
    /* No event specific attributes */
    parent.onStatusStarted(event);
  }

  @Override
  public void on_status_update_performance(io.ooni.mk.nettest.swig.StatusUpdatePerformance swigEvent) {
    io.ooni.mk.nettest.event.StatusUpdatePerformance event = new io.ooni.mk.nettest.event.StatusUpdatePerformance();
    event.direction = swigEvent.getDirection();
    event.elapsed = swigEvent.getElapsed();
    event.numStreams = swigEvent.getNum_streams();
    event.speedKbps = swigEvent.getSpeed_kbps();
    parent.onStatusUpdatePerformance(event);
  }

  @Override
  public void on_status_update_websites(io.ooni.mk.nettest.swig.StatusUpdateWebsites swigEvent) {
    io.ooni.mk.nettest.event.StatusUpdateWebsites event = new io.ooni.mk.nettest.event.StatusUpdateWebsites();
    event.url = swigEvent.getUrl();
    event.status = swigEvent.getStatus();
    parent.onStatusUpdateWebsites(event);
  }

  @Override
  public void on_task_terminated(io.ooni.mk.nettest.swig.TaskTerminated swigEvent) {
    io.ooni.mk.nettest.event.TaskTerminated event = new io.ooni.mk.nettest.event.TaskTerminated();
    /* No event specific attributes */
    parent.onTaskTerminated(event);
  }

  @Override
  public void run_captive_portal(io.ooni.mk.nettest.swig.CaptivePortal swigSettings) {
    super.run_captive_portal(swigSettings);
  }

  @Override
  public void run_dash(io.ooni.mk.nettest.swig.Dash swigSettings) {
    super.run_dash(swigSettings);
  }

  @Override
  public void run_dns_injection(io.ooni.mk.nettest.swig.DnsInjection swigSettings) {
    super.run_dns_injection(swigSettings);
  }

  @Override
  public void run_facebook_messenger(io.ooni.mk.nettest.swig.FacebookMessenger swigSettings) {
    super.run_facebook_messenger(swigSettings);
  }

  @Override
  public void run_http_header_field_manipulation(io.ooni.mk.nettest.swig.HttpHeaderFieldManipulation swigSettings) {
    super.run_http_header_field_manipulation(swigSettings);
  }

  @Override
  public void run_http_invalid_request_line(io.ooni.mk.nettest.swig.HttpInvalidRequestLine swigSettings) {
    super.run_http_invalid_request_line(swigSettings);
  }

  @Override
  public void run_meek_fronted_requests(io.ooni.mk.nettest.swig.MeekFrontedRequests swigSettings) {
    super.run_meek_fronted_requests(swigSettings);
  }

  @Override
  public void run_multi_ndt(io.ooni.mk.nettest.swig.MultiNdt swigSettings) {
    super.run_multi_ndt(swigSettings);
  }

  @Override
  public void run_ndt(io.ooni.mk.nettest.swig.Ndt swigSettings) {
    super.run_ndt(swigSettings);
  }

  @Override
  public void run_tcp_connect(io.ooni.mk.nettest.swig.TcpConnect swigSettings) {
    super.run_tcp_connect(swigSettings);
  }

  @Override
  public void run_telegram(io.ooni.mk.nettest.swig.Telegram swigSettings) {
    super.run_telegram(swigSettings);
  }

  @Override
  public void run_web_connectivity(io.ooni.mk.nettest.swig.WebConnectivity swigSettings) {
    super.run_web_connectivity(swigSettings);
  }

  @Override
  public void run_whatsapp(io.ooni.mk.nettest.swig.Whatsapp swigSettings) {
    super.run_whatsapp(swigSettings);
  }

  private Runner parent;
}
