/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.ooni.mk.nettest.swig;

public class HttpHeaderFieldManipulation extends Common {
  private transient long swigCPtr;

  protected HttpHeaderFieldManipulation(long cPtr, boolean cMemoryOwn) {
    super(MkNettestJNI.HttpHeaderFieldManipulation_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(HttpHeaderFieldManipulation obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MkNettestJNI.delete_HttpHeaderFieldManipulation(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public HttpHeaderFieldManipulation() {
    this(MkNettestJNI.new_HttpHeaderFieldManipulation(), true);
  }

  public final static boolean needs_input = MkNettestJNI.HttpHeaderFieldManipulation_needs_input_get();
}
