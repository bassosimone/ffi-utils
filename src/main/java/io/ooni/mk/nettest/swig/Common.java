/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.ooni.mk.nettest.swig;

public class Common {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Common(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Common obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MkNettestJNI.delete_Common(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setAnnotations(MapStringString value) {
    MkNettestJNI.Common_annotations_set(swigCPtr, this, MapStringString.getCPtr(value), value);
  }

  public MapStringString getAnnotations() {
    long cPtr = MkNettestJNI.Common_annotations_get(swigCPtr, this);
    return (cPtr == 0) ? null : new MapStringString(cPtr, false);
  }

  public void setDisabled_events(VectorString value) {
    MkNettestJNI.Common_disabled_events_set(swigCPtr, this, VectorString.getCPtr(value), value);
  }

  public VectorString getDisabled_events() {
    long cPtr = MkNettestJNI.Common_disabled_events_get(swigCPtr, this);
    return (cPtr == 0) ? null : new VectorString(cPtr, false);
  }

  public void setInputs(VectorString value) {
    MkNettestJNI.Common_inputs_set(swigCPtr, this, VectorString.getCPtr(value), value);
  }

  public VectorString getInputs() {
    long cPtr = MkNettestJNI.Common_inputs_get(swigCPtr, this);
    return (cPtr == 0) ? null : new VectorString(cPtr, false);
  }

  public void setInput_filepaths(VectorString value) {
    MkNettestJNI.Common_input_filepaths_set(swigCPtr, this, VectorString.getCPtr(value), value);
  }

  public VectorString getInput_filepaths() {
    long cPtr = MkNettestJNI.Common_input_filepaths_get(swigCPtr, this);
    return (cPtr == 0) ? null : new VectorString(cPtr, false);
  }

  public void setLog_filepath(String value) {
    MkNettestJNI.Common_log_filepath_set(swigCPtr, this, value);
  }

  public String getLog_filepath() {
    return MkNettestJNI.Common_log_filepath_get(swigCPtr, this);
  }

  public void setLog_level(String value) {
    MkNettestJNI.Common_log_level_set(swigCPtr, this, value);
  }

  public String getLog_level() {
    return MkNettestJNI.Common_log_level_get(swigCPtr, this);
  }

  public void setOutput_filepath(String value) {
    MkNettestJNI.Common_output_filepath_set(swigCPtr, this, value);
  }

  public String getOutput_filepath() {
    return MkNettestJNI.Common_output_filepath_get(swigCPtr, this);
  }

  public void setBouncer_base_url(String value) {
    MkNettestJNI.Common_bouncer_base_url_set(swigCPtr, this, value);
  }

  public String getBouncer_base_url() {
    return MkNettestJNI.Common_bouncer_base_url_get(swigCPtr, this);
  }

  public void setCollector_base_url(String value) {
    MkNettestJNI.Common_collector_base_url_set(swigCPtr, this, value);
  }

  public String getCollector_base_url() {
    return MkNettestJNI.Common_collector_base_url_get(swigCPtr, this);
  }

  public void setDns_nameserver(String value) {
    MkNettestJNI.Common_dns_nameserver_set(swigCPtr, this, value);
  }

  public String getDns_nameserver() {
    return MkNettestJNI.Common_dns_nameserver_get(swigCPtr, this);
  }

  public void setDns_engine(String value) {
    MkNettestJNI.Common_dns_engine_set(swigCPtr, this, value);
  }

  public String getDns_engine() {
    return MkNettestJNI.Common_dns_engine_get(swigCPtr, this);
  }

  public void setGeoip_asn_path(String value) {
    MkNettestJNI.Common_geoip_asn_path_set(swigCPtr, this, value);
  }

  public String getGeoip_asn_path() {
    return MkNettestJNI.Common_geoip_asn_path_get(swigCPtr, this);
  }

  public void setGeoip_country_path(String value) {
    MkNettestJNI.Common_geoip_country_path_set(swigCPtr, this, value);
  }

  public String getGeoip_country_path() {
    return MkNettestJNI.Common_geoip_country_path_get(swigCPtr, this);
  }

  public void setIgnore_bouncer_error(boolean value) {
    MkNettestJNI.Common_ignore_bouncer_error_set(swigCPtr, this, value);
  }

  public boolean getIgnore_bouncer_error() {
    return MkNettestJNI.Common_ignore_bouncer_error_get(swigCPtr, this);
  }

  public void setIgnore_open_report_error(boolean value) {
    MkNettestJNI.Common_ignore_open_report_error_set(swigCPtr, this, value);
  }

  public boolean getIgnore_open_report_error() {
    return MkNettestJNI.Common_ignore_open_report_error_get(swigCPtr, this);
  }

  public void setMax_runtime(double value) {
    MkNettestJNI.Common_max_runtime_set(swigCPtr, this, value);
  }

  public double getMax_runtime() {
    return MkNettestJNI.Common_max_runtime_get(swigCPtr, this);
  }

  public void setNet_ca_bundle_path(String value) {
    MkNettestJNI.Common_net_ca_bundle_path_set(swigCPtr, this, value);
  }

  public String getNet_ca_bundle_path() {
    return MkNettestJNI.Common_net_ca_bundle_path_get(swigCPtr, this);
  }

  public void setNet_timeout(double value) {
    MkNettestJNI.Common_net_timeout_set(swigCPtr, this, value);
  }

  public double getNet_timeout() {
    return MkNettestJNI.Common_net_timeout_get(swigCPtr, this);
  }

  public void setNo_bouncer(boolean value) {
    MkNettestJNI.Common_no_bouncer_set(swigCPtr, this, value);
  }

  public boolean getNo_bouncer() {
    return MkNettestJNI.Common_no_bouncer_get(swigCPtr, this);
  }

  public void setNo_collector(boolean value) {
    MkNettestJNI.Common_no_collector_set(swigCPtr, this, value);
  }

  public boolean getNo_collector() {
    return MkNettestJNI.Common_no_collector_get(swigCPtr, this);
  }

  public void setNo_asn_lookup(boolean value) {
    MkNettestJNI.Common_no_asn_lookup_set(swigCPtr, this, value);
  }

  public boolean getNo_asn_lookup() {
    return MkNettestJNI.Common_no_asn_lookup_get(swigCPtr, this);
  }

  public void setNo_cc_lookup(boolean value) {
    MkNettestJNI.Common_no_cc_lookup_set(swigCPtr, this, value);
  }

  public boolean getNo_cc_lookup() {
    return MkNettestJNI.Common_no_cc_lookup_get(swigCPtr, this);
  }

  public void setNo_ip_lookup(boolean value) {
    MkNettestJNI.Common_no_ip_lookup_set(swigCPtr, this, value);
  }

  public boolean getNo_ip_lookup() {
    return MkNettestJNI.Common_no_ip_lookup_get(swigCPtr, this);
  }

  public void setNo_file_report(boolean value) {
    MkNettestJNI.Common_no_file_report_set(swigCPtr, this, value);
  }

  public boolean getNo_file_report() {
    return MkNettestJNI.Common_no_file_report_get(swigCPtr, this);
  }

  public void setNo_resolver_lookup(boolean value) {
    MkNettestJNI.Common_no_resolver_lookup_set(swigCPtr, this, value);
  }

  public boolean getNo_resolver_lookup() {
    return MkNettestJNI.Common_no_resolver_lookup_get(swigCPtr, this);
  }

  public void setProbe_asn(String value) {
    MkNettestJNI.Common_probe_asn_set(swigCPtr, this, value);
  }

  public String getProbe_asn() {
    return MkNettestJNI.Common_probe_asn_get(swigCPtr, this);
  }

  public void setProbe_cc(String value) {
    MkNettestJNI.Common_probe_cc_set(swigCPtr, this, value);
  }

  public String getProbe_cc() {
    return MkNettestJNI.Common_probe_cc_get(swigCPtr, this);
  }

  public void setProbe_ip(String value) {
    MkNettestJNI.Common_probe_ip_set(swigCPtr, this, value);
  }

  public String getProbe_ip() {
    return MkNettestJNI.Common_probe_ip_get(swigCPtr, this);
  }

  public void setRandomize_input(boolean value) {
    MkNettestJNI.Common_randomize_input_set(swigCPtr, this, value);
  }

  public boolean getRandomize_input() {
    return MkNettestJNI.Common_randomize_input_get(swigCPtr, this);
  }

  public void setSave_real_probe_asn(boolean value) {
    MkNettestJNI.Common_save_real_probe_asn_set(swigCPtr, this, value);
  }

  public boolean getSave_real_probe_asn() {
    return MkNettestJNI.Common_save_real_probe_asn_get(swigCPtr, this);
  }

  public void setSave_real_probe_cc(boolean value) {
    MkNettestJNI.Common_save_real_probe_cc_set(swigCPtr, this, value);
  }

  public boolean getSave_real_probe_cc() {
    return MkNettestJNI.Common_save_real_probe_cc_get(swigCPtr, this);
  }

  public void setSave_real_probe_ip(boolean value) {
    MkNettestJNI.Common_save_real_probe_ip_set(swigCPtr, this, value);
  }

  public boolean getSave_real_probe_ip() {
    return MkNettestJNI.Common_save_real_probe_ip_get(swigCPtr, this);
  }

  public void setSave_real_resolver_ip(boolean value) {
    MkNettestJNI.Common_save_real_resolver_ip_set(swigCPtr, this, value);
  }

  public boolean getSave_real_resolver_ip() {
    return MkNettestJNI.Common_save_real_resolver_ip_get(swigCPtr, this);
  }

  public void setSoftware_name(String value) {
    MkNettestJNI.Common_software_name_set(swigCPtr, this, value);
  }

  public String getSoftware_name() {
    return MkNettestJNI.Common_software_name_get(swigCPtr, this);
  }

  public void setSoftware_version(String value) {
    MkNettestJNI.Common_software_version_set(swigCPtr, this, value);
  }

  public String getSoftware_version() {
    return MkNettestJNI.Common_software_version_get(swigCPtr, this);
  }

  public Common() {
    this(MkNettestJNI.new_Common(), true);
  }

  public final static String log_level_err = MkNettestJNI.Common_log_level_err_get();
  public final static String log_level_warning = MkNettestJNI.Common_log_level_warning_get();
  public final static String log_level_info = MkNettestJNI.Common_log_level_info_get();
  public final static String log_level_debug = MkNettestJNI.Common_log_level_debug_get();
  public final static String log_level_debug2 = MkNettestJNI.Common_log_level_debug2_get();
}