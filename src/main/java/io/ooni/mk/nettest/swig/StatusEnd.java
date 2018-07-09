/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.ooni.mk.nettest.swig;

public class StatusEnd {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected StatusEnd(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(StatusEnd obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MkNettestJNI.delete_StatusEnd(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setDownloaded_kb(double value) {
    MkNettestJNI.StatusEnd_downloaded_kb_set(swigCPtr, this, value);
  }

  public double getDownloaded_kb() {
    return MkNettestJNI.StatusEnd_downloaded_kb_get(swigCPtr, this);
  }

  public void setUploaded_kb(double value) {
    MkNettestJNI.StatusEnd_uploaded_kb_set(swigCPtr, this, value);
  }

  public double getUploaded_kb() {
    return MkNettestJNI.StatusEnd_uploaded_kb_get(swigCPtr, this);
  }

  public void setFailure(String value) {
    MkNettestJNI.StatusEnd_failure_set(swigCPtr, this, value);
  }

  public String getFailure() {
    return MkNettestJNI.StatusEnd_failure_get(swigCPtr, this);
  }

  public StatusEnd() {
    this(MkNettestJNI.new_StatusEnd(), true);
  }

  public final static String key = MkNettestJNI.StatusEnd_key_get();
}
