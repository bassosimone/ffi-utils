/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.ooni.mk.nettest.swig;

public class StatusMeasurementStart {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected StatusMeasurementStart(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(StatusMeasurementStart obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MkNettestJNI.delete_StatusMeasurementStart(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setIdx(long value) {
    MkNettestJNI.StatusMeasurementStart_idx_set(swigCPtr, this, value);
  }

  public long getIdx() {
    return MkNettestJNI.StatusMeasurementStart_idx_get(swigCPtr, this);
  }

  public void setInput(String value) {
    MkNettestJNI.StatusMeasurementStart_input_set(swigCPtr, this, value);
  }

  public String getInput() {
    return MkNettestJNI.StatusMeasurementStart_input_get(swigCPtr, this);
  }

  public StatusMeasurementStart() {
    this(MkNettestJNI.new_StatusMeasurementStart(), true);
  }

  public final static String key = MkNettestJNI.StatusMeasurementStart_key_get();
}