/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.ooni.mk.nettest.swig;

public class FailureReportClose {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected FailureReportClose(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(FailureReportClose obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MkNettestJNI.delete_FailureReportClose(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setFailure(String value) {
    MkNettestJNI.FailureReportClose_failure_set(swigCPtr, this, value);
  }

  public String getFailure() {
    return MkNettestJNI.FailureReportClose_failure_get(swigCPtr, this);
  }

  public FailureReportClose() {
    this(MkNettestJNI.new_FailureReportClose(), true);
  }

  public final static String key = MkNettestJNI.FailureReportClose_key_get();
}
