/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.ooni.mk.nettest.swig;

public class Measurement {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Measurement(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Measurement obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MkNettestJNI.delete_Measurement(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setIdx(long value) {
    MkNettestJNI.Measurement_idx_set(swigCPtr, this, value);
  }

  public long getIdx() {
    return MkNettestJNI.Measurement_idx_get(swigCPtr, this);
  }

  public void setJson_str(String value) {
    MkNettestJNI.Measurement_json_str_set(swigCPtr, this, value);
  }

  public String getJson_str() {
    return MkNettestJNI.Measurement_json_str_get(swigCPtr, this);
  }

  public Measurement() {
    this(MkNettestJNI.new_Measurement(), true);
  }

  public final static String key = MkNettestJNI.Measurement_key_get();
}
