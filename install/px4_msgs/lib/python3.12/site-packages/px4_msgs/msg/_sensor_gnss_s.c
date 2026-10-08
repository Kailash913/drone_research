// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from px4_msgs:msg/SensorGnss.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "px4_msgs/msg/detail/sensor_gnss__struct.h"
#include "px4_msgs/msg/detail/sensor_gnss__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool px4_msgs__msg__sensor_gnss__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[37];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("px4_msgs.msg._sensor_gnss.SensorGnss", full_classname_dest, 36) == 0);
  }
  px4_msgs__msg__SensorGnss * ros_message = _ros_message;
  {  // timestamp
    PyObject * field = PyObject_GetAttrString(_pymsg, "timestamp");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timestamp = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // timestamp_sample
    PyObject * field = PyObject_GetAttrString(_pymsg, "timestamp_sample");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timestamp_sample = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // device_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "device_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->device_id = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // latitude
    PyObject * field = PyObject_GetAttrString(_pymsg, "latitude");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->latitude = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // longitude
    PyObject * field = PyObject_GetAttrString(_pymsg, "longitude");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->longitude = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // altitude_msl
    PyObject * field = PyObject_GetAttrString(_pymsg, "altitude_msl");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->altitude_msl = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // altitude_ellipsoid
    PyObject * field = PyObject_GetAttrString(_pymsg, "altitude_ellipsoid");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->altitude_ellipsoid = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // speed_accuracy
    PyObject * field = PyObject_GetAttrString(_pymsg, "speed_accuracy");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->speed_accuracy = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // course_accuracy
    PyObject * field = PyObject_GetAttrString(_pymsg, "course_accuracy");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->course_accuracy = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // fix_type
    PyObject * field = PyObject_GetAttrString(_pymsg, "fix_type");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->fix_type = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // eph
    PyObject * field = PyObject_GetAttrString(_pymsg, "eph");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->eph = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // epv
    PyObject * field = PyObject_GetAttrString(_pymsg, "epv");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->epv = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // hdop
    PyObject * field = PyObject_GetAttrString(_pymsg, "hdop");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->hdop = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // vdop
    PyObject * field = PyObject_GetAttrString(_pymsg, "vdop");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->vdop = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // noise
    PyObject * field = PyObject_GetAttrString(_pymsg, "noise");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->noise = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // automatic_gain_control
    PyObject * field = PyObject_GetAttrString(_pymsg, "automatic_gain_control");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->automatic_gain_control = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // jamming_state
    PyObject * field = PyObject_GetAttrString(_pymsg, "jamming_state");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->jamming_state = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // jamming_indicator
    PyObject * field = PyObject_GetAttrString(_pymsg, "jamming_indicator");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->jamming_indicator = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // spoofing_state
    PyObject * field = PyObject_GetAttrString(_pymsg, "spoofing_state");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->spoofing_state = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // authentication_state
    PyObject * field = PyObject_GetAttrString(_pymsg, "authentication_state");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->authentication_state = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // ground_speed
    PyObject * field = PyObject_GetAttrString(_pymsg, "ground_speed");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ground_speed = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // vel_north
    PyObject * field = PyObject_GetAttrString(_pymsg, "vel_north");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->vel_north = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // vel_east
    PyObject * field = PyObject_GetAttrString(_pymsg, "vel_east");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->vel_east = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // vel_down
    PyObject * field = PyObject_GetAttrString(_pymsg, "vel_down");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->vel_down = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // course
    PyObject * field = PyObject_GetAttrString(_pymsg, "course");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->course = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // vel_ned_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "vel_ned_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->vel_ned_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // timestamp_time_relative
    PyObject * field = PyObject_GetAttrString(_pymsg, "timestamp_time_relative");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timestamp_time_relative = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // time_utc_usec
    PyObject * field = PyObject_GetAttrString(_pymsg, "time_utc_usec");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->time_utc_usec = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // satellites_used
    PyObject * field = PyObject_GetAttrString(_pymsg, "satellites_used");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->satellites_used = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // system_error
    PyObject * field = PyObject_GetAttrString(_pymsg, "system_error");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->system_error = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // rtcm_injection_rate
    PyObject * field = PyObject_GetAttrString(_pymsg, "rtcm_injection_rate");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->rtcm_injection_rate = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // selected_rtcm_instance
    PyObject * field = PyObject_GetAttrString(_pymsg, "selected_rtcm_instance");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->selected_rtcm_instance = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // corrections_protocol
    PyObject * field = PyObject_GetAttrString(_pymsg, "corrections_protocol");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->corrections_protocol = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // corrections_crc_failed
    PyObject * field = PyObject_GetAttrString(_pymsg, "corrections_crc_failed");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->corrections_crc_failed = (Py_True == field);
    Py_DECREF(field);
  }
  {  // corrections_msg_used
    PyObject * field = PyObject_GetAttrString(_pymsg, "corrections_msg_used");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->corrections_msg_used = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * px4_msgs__msg__sensor_gnss__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SensorGnss */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("px4_msgs.msg._sensor_gnss");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SensorGnss");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  px4_msgs__msg__SensorGnss * ros_message = (px4_msgs__msg__SensorGnss *)raw_ros_message;
  {  // timestamp
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->timestamp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timestamp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timestamp_sample
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->timestamp_sample);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timestamp_sample", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // device_id
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->device_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "device_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // latitude
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->latitude);
    {
      int rc = PyObject_SetAttrString(_pymessage, "latitude", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // longitude
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->longitude);
    {
      int rc = PyObject_SetAttrString(_pymessage, "longitude", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // altitude_msl
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->altitude_msl);
    {
      int rc = PyObject_SetAttrString(_pymessage, "altitude_msl", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // altitude_ellipsoid
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->altitude_ellipsoid);
    {
      int rc = PyObject_SetAttrString(_pymessage, "altitude_ellipsoid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // speed_accuracy
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->speed_accuracy);
    {
      int rc = PyObject_SetAttrString(_pymessage, "speed_accuracy", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // course_accuracy
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->course_accuracy);
    {
      int rc = PyObject_SetAttrString(_pymessage, "course_accuracy", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fix_type
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->fix_type);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fix_type", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // eph
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->eph);
    {
      int rc = PyObject_SetAttrString(_pymessage, "eph", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // epv
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->epv);
    {
      int rc = PyObject_SetAttrString(_pymessage, "epv", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // hdop
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->hdop);
    {
      int rc = PyObject_SetAttrString(_pymessage, "hdop", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // vdop
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->vdop);
    {
      int rc = PyObject_SetAttrString(_pymessage, "vdop", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // noise
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->noise);
    {
      int rc = PyObject_SetAttrString(_pymessage, "noise", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // automatic_gain_control
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->automatic_gain_control);
    {
      int rc = PyObject_SetAttrString(_pymessage, "automatic_gain_control", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // jamming_state
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->jamming_state);
    {
      int rc = PyObject_SetAttrString(_pymessage, "jamming_state", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // jamming_indicator
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->jamming_indicator);
    {
      int rc = PyObject_SetAttrString(_pymessage, "jamming_indicator", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // spoofing_state
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->spoofing_state);
    {
      int rc = PyObject_SetAttrString(_pymessage, "spoofing_state", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // authentication_state
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->authentication_state);
    {
      int rc = PyObject_SetAttrString(_pymessage, "authentication_state", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ground_speed
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ground_speed);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ground_speed", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // vel_north
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->vel_north);
    {
      int rc = PyObject_SetAttrString(_pymessage, "vel_north", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // vel_east
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->vel_east);
    {
      int rc = PyObject_SetAttrString(_pymessage, "vel_east", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // vel_down
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->vel_down);
    {
      int rc = PyObject_SetAttrString(_pymessage, "vel_down", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // course
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->course);
    {
      int rc = PyObject_SetAttrString(_pymessage, "course", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // vel_ned_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->vel_ned_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "vel_ned_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timestamp_time_relative
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->timestamp_time_relative);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timestamp_time_relative", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // time_utc_usec
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->time_utc_usec);
    {
      int rc = PyObject_SetAttrString(_pymessage, "time_utc_usec", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // satellites_used
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->satellites_used);
    {
      int rc = PyObject_SetAttrString(_pymessage, "satellites_used", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // system_error
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->system_error);
    {
      int rc = PyObject_SetAttrString(_pymessage, "system_error", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rtcm_injection_rate
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->rtcm_injection_rate);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rtcm_injection_rate", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // selected_rtcm_instance
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->selected_rtcm_instance);
    {
      int rc = PyObject_SetAttrString(_pymessage, "selected_rtcm_instance", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // corrections_protocol
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->corrections_protocol);
    {
      int rc = PyObject_SetAttrString(_pymessage, "corrections_protocol", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // corrections_crc_failed
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->corrections_crc_failed ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "corrections_crc_failed", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // corrections_msg_used
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->corrections_msg_used);
    {
      int rc = PyObject_SetAttrString(_pymessage, "corrections_msg_used", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
