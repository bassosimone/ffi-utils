/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.ooni.mk.nettest.swig;

public class StatusReportCreate {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected StatusReportCreate(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(StatusReportCreate obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MkNettestJNI.delete_StatusReportCreate(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setReport_id(String value) {
    MkNettestJNI.StatusReportCreate_report_id_set(swigCPtr, this, value);
  }

  public String getReport_id() {
    return MkNettestJNI.StatusReportCreate_report_id_get(swigCPtr, this);
  }

  public StatusReportCreate() {
    this(MkNettestJNI.new_StatusReportCreate(), true);
  }

  public final static String key = MkNettestJNI.StatusReportCreate_key_get();
}
