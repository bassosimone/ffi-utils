/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.openobservatory.measurement_kit.nettest.swig;

public class Settings {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Settings(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Settings obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        LibndtJNI.delete_Settings(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setAnnotations(MapStringString value) {
    LibndtJNI.Settings_annotations_set(swigCPtr, this, MapStringString.getCPtr(value), value);
  }

  public MapStringString getAnnotations() {
    long cPtr = LibndtJNI.Settings_annotations_get(swigCPtr, this);
    return (cPtr == 0) ? null : new MapStringString(cPtr, false);
  }

  public void setDisabled_events(VectorString value) {
    LibndtJNI.Settings_disabled_events_set(swigCPtr, this, VectorString.getCPtr(value), value);
  }

  public VectorString getDisabled_events() {
    long cPtr = LibndtJNI.Settings_disabled_events_get(swigCPtr, this);
    return (cPtr == 0) ? null : new VectorString(cPtr, false);
  }

  public void setName(String value) {
    LibndtJNI.Settings_name_set(swigCPtr, this, value);
  }

  public String getName() {
    return LibndtJNI.Settings_name_get(swigCPtr, this);
  }

  public void setOptions(Options value) {
    LibndtJNI.Settings_options_set(swigCPtr, this, Options.getCPtr(value), value);
  }

  public Options getOptions() {
    long cPtr = LibndtJNI.Settings_options_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Options(cPtr, false);
  }

  public Settings() {
    this(LibndtJNI.new_Settings(), true);
  }

}