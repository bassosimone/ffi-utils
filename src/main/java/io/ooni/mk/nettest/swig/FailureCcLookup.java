/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.ooni.mk.nettest.swig;

public class FailureCcLookup {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected FailureCcLookup(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(FailureCcLookup obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MkNettestJNI.delete_FailureCcLookup(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setFailure(String value) {
    MkNettestJNI.FailureCcLookup_failure_set(swigCPtr, this, value);
  }

  public String getFailure() {
    return MkNettestJNI.FailureCcLookup_failure_get(swigCPtr, this);
  }

  public FailureCcLookup() {
    this(MkNettestJNI.new_FailureCcLookup(), true);
  }

  public final static String key = MkNettestJNI.FailureCcLookup_key_get();
}
