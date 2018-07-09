/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_MkNettest_WRAP_H_
#define SWIG_MkNettest_WRAP_H_

class SwigDirector_Runner : public mk::nettest::Runner, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_Runner(JNIEnv *jenv);
    virtual void on_failure_asn_lookup(mk::nettest::event::FailureAsnLookup const &arg0);
    virtual void on_failure_cc_lookup(mk::nettest::event::FailureCcLookup const &arg0);
    virtual void on_failure_ip_lookup(mk::nettest::event::FailureIpLookup const &arg0);
    virtual void on_failure_measurement(mk::nettest::event::FailureMeasurement const &arg0);
    virtual void on_failure_measurement_submission(mk::nettest::event::FailureMeasurementSubmission const &arg0);
    virtual void on_failure_report_create(mk::nettest::event::FailureReportCreate const &arg0);
    virtual void on_failure_report_close(mk::nettest::event::FailureReportClose const &arg0);
    virtual void on_failure_resolver_lookup(mk::nettest::event::FailureResolverLookup const &arg0);
    virtual void on_failure_startup(mk::nettest::event::FailureStartup const &arg0);
    virtual void on_log(mk::nettest::event::Log const &arg0);
    virtual void on_measurement(mk::nettest::event::Measurement const &arg0);
    virtual void on_status_end(mk::nettest::event::StatusEnd const &arg0);
    virtual void on_status_geoip_lookup(mk::nettest::event::StatusGeoipLookup const &arg0);
    virtual void on_status_progress(mk::nettest::event::StatusProgress const &arg0);
    virtual void on_status_queued(mk::nettest::event::StatusQueued const &arg0);
    virtual void on_status_measurement_start(mk::nettest::event::StatusMeasurementStart const &arg0);
    virtual void on_status_measurement_submission(mk::nettest::event::StatusMeasurementSubmission const &arg0);
    virtual void on_status_measurement_done(mk::nettest::event::StatusMeasurementDone const &arg0);
    virtual void on_status_report_close(mk::nettest::event::StatusReportClose const &arg0);
    virtual void on_status_report_create(mk::nettest::event::StatusReportCreate const &arg0);
    virtual void on_status_resolver_lookup(mk::nettest::event::StatusResolverLookup const &arg0);
    virtual void on_status_started(mk::nettest::event::StatusStarted const &arg0);
    virtual void on_status_update_performance(mk::nettest::event::StatusUpdatePerformance const &arg0);
    virtual void on_status_update_websites(mk::nettest::event::StatusUpdateWebsites const &arg0);
    virtual void on_task_terminated(mk::nettest::event::TaskTerminated const &arg0);
    virtual ~SwigDirector_Runner();
public:
    bool swig_overrides(int n) {
      return (n < 25 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<25> swig_override;
};


#endif
