/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.ooni.mk.nettest.swig;

public class StatusStarted {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected StatusStarted(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(StatusStarted obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MkNettestJNI.delete_StatusStarted(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public StatusStarted() {
    this(MkNettestJNI.new_StatusStarted(), true);
  }

  public final static String key = MkNettestJNI.StatusStarted_key_get();
}