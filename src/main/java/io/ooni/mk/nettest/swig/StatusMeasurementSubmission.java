/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.ooni.mk.nettest.swig;

public class StatusMeasurementSubmission {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected StatusMeasurementSubmission(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(StatusMeasurementSubmission obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MkNettestJNI.delete_StatusMeasurementSubmission(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setIdx(long value) {
    MkNettestJNI.StatusMeasurementSubmission_idx_set(swigCPtr, this, value);
  }

  public long getIdx() {
    return MkNettestJNI.StatusMeasurementSubmission_idx_get(swigCPtr, this);
  }

  public StatusMeasurementSubmission() {
    this(MkNettestJNI.new_StatusMeasurementSubmission(), true);
  }

  public final static String key = MkNettestJNI.StatusMeasurementSubmission_key_get();
}
