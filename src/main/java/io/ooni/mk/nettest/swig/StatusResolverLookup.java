/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.ooni.mk.nettest.swig;

public class StatusResolverLookup {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected StatusResolverLookup(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(StatusResolverLookup obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MkNettestJNI.delete_StatusResolverLookup(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setIp_address(String value) {
    MkNettestJNI.StatusResolverLookup_ip_address_set(swigCPtr, this, value);
  }

  public String getIp_address() {
    return MkNettestJNI.StatusResolverLookup_ip_address_get(swigCPtr, this);
  }

  public StatusResolverLookup() {
    this(MkNettestJNI.new_StatusResolverLookup(), true);
  }

  public final static String key = MkNettestJNI.StatusResolverLookup_key_get();
}