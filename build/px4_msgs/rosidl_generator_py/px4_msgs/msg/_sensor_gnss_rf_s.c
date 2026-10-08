// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from px4_msgs:msg/SensorGnssRf.idl
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
#include "px4_msgs/msg/detail/sensor_gnss_rf__struct.h"
#include "px4_msgs/msg/detail/sensor_gnss_rf__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool px4_msgs__msg__sensor_gnss_rf__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[42];
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
    assert(strncmp("px4_msgs.msg._sensor_gnss_rf.SensorGnssRf", full_classname_dest, 41) == 0);
  }
  px4_msgs__msg__SensorGnssRf * ros_message = _ros_message;
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
  {  // block_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "block_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->block_id = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // antenna_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "antenna_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->antenna_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // antenna_power
    PyObject * field = PyObject_GetAttrString(_pymsg, "antenna_power");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->antenna_power = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // post_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "post_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->post_status = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // noise_per_ms
    PyObject * field = PyObject_GetAttrString(_pymsg, "noise_per_ms");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->noise_per_ms = (uint16_t)PyLong_AsUnsignedLong(field);
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
  {  // jamming_indicator
    PyObject * field = PyObject_GetAttrString(_pymsg, "jamming_indicator");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->jamming_indicator = (uint8_t)PyLong_AsUnsignedLong(field);
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
  {  // i_offset
    PyObject * field = PyObject_GetAttrString(_pymsg, "i_offset");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->i_offset = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // i_magnitude
    PyObject * field = PyObject_GetAttrString(_pymsg, "i_magnitude");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->i_magnitude = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // q_offset
    PyObject * field = PyObject_GetAttrString(_pymsg, "q_offset");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->q_offset = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // q_magnitude
    PyObject * field = PyObject_GetAttrString(_pymsg, "q_magnitude");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->q_magnitude = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // center_frequency
    PyObject * field = PyObject_GetAttrString(_pymsg, "center_frequency");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->center_frequency = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * px4_msgs__msg__sensor_gnss_rf__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SensorGnssRf */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("px4_msgs.msg._sensor_gnss_rf");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SensorGnssRf");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  px4_msgs__msg__SensorGnssRf * ros_message = (px4_msgs__msg__SensorGnssRf *)raw_ros_message;
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
  {  // block_id
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->block_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "block_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // antenna_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->antenna_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "antenna_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // antenna_power
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->antenna_power);
    {
      int rc = PyObject_SetAttrString(_pymessage, "antenna_power", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // post_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->post_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "post_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // noise_per_ms
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->noise_per_ms);
    {
      int rc = PyObject_SetAttrString(_pymessage, "noise_per_ms", field);
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
  {  // jamming_indicator
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->jamming_indicator);
    {
      int rc = PyObject_SetAttrString(_pymessage, "jamming_indicator", field);
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
  {  // i_offset
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->i_offset);
    {
      int rc = PyObject_SetAttrString(_pymessage, "i_offset", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // i_magnitude
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->i_magnitude);
    {
      int rc = PyObject_SetAttrString(_pymessage, "i_magnitude", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // q_offset
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->q_offset);
    {
      int rc = PyObject_SetAttrString(_pymessage, "q_offset", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // q_magnitude
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->q_magnitude);
    {
      int rc = PyObject_SetAttrString(_pymessage, "q_magnitude", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // center_frequency
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->center_frequency);
    {
      int rc = PyObject_SetAttrString(_pymessage, "center_frequency", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
