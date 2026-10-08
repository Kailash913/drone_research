// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from px4_msgs:msg/SensorsStatusGnss.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "px4_msgs/msg/detail/sensors_status_gnss__rosidl_typesupport_introspection_c.h"
#include "px4_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "px4_msgs/msg/detail/sensors_status_gnss__functions.h"
#include "px4_msgs/msg/detail/sensors_status_gnss__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  px4_msgs__msg__SensorsStatusGnss__init(message_memory);
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_fini_function(void * message_memory)
{
  px4_msgs__msg__SensorsStatusGnss__fini(message_memory);
}

size_t px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__device_ids(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__device_ids(
  const void * untyped_member, size_t index)
{
  const uint32_t * member =
    (const uint32_t *)(untyped_member);
  return &member[index];
}

void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__device_ids(
  void * untyped_member, size_t index)
{
  uint32_t * member =
    (uint32_t *)(untyped_member);
  return &member[index];
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__device_ids(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint32_t * item =
    ((const uint32_t *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__device_ids(untyped_member, index));
  uint32_t * value =
    (uint32_t *)(untyped_value);
  *value = *item;
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__device_ids(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint32_t * item =
    ((uint32_t *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__device_ids(untyped_member, index));
  const uint32_t * value =
    (const uint32_t *)(untyped_value);
  *item = *value;
}

size_t px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__order(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__order(
  const void * untyped_member, size_t index)
{
  const int8_t * member =
    (const int8_t *)(untyped_member);
  return &member[index];
}

void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__order(
  void * untyped_member, size_t index)
{
  int8_t * member =
    (int8_t *)(untyped_member);
  return &member[index];
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__order(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int8_t * item =
    ((const int8_t *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__order(untyped_member, index));
  int8_t * value =
    (int8_t *)(untyped_value);
  *value = *item;
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__order(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int8_t * item =
    ((int8_t *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__order(untyped_member, index));
  const int8_t * value =
    (const int8_t *)(untyped_value);
  *item = *value;
}

size_t px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__healthy(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__healthy(
  const void * untyped_member, size_t index)
{
  const bool * member =
    (const bool *)(untyped_member);
  return &member[index];
}

void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__healthy(
  void * untyped_member, size_t index)
{
  bool * member =
    (bool *)(untyped_member);
  return &member[index];
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__healthy(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__healthy(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__healthy(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__healthy(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

size_t px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__failed_checks(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__failed_checks(
  const void * untyped_member, size_t index)
{
  const uint16_t * member =
    (const uint16_t *)(untyped_member);
  return &member[index];
}

void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__failed_checks(
  void * untyped_member, size_t index)
{
  uint16_t * member =
    (uint16_t *)(untyped_member);
  return &member[index];
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__failed_checks(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint16_t * item =
    ((const uint16_t *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__failed_checks(untyped_member, index));
  uint16_t * value =
    (uint16_t *)(untyped_value);
  *value = *item;
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__failed_checks(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint16_t * item =
    ((uint16_t *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__failed_checks(untyped_member, index));
  const uint16_t * value =
    (const uint16_t *)(untyped_value);
  *item = *value;
}

size_t px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__strict(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__strict(
  const void * untyped_member, size_t index)
{
  const bool * member =
    (const bool *)(untyped_member);
  return &member[index];
}

void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__strict(
  void * untyped_member, size_t index)
{
  bool * member =
    (bool *)(untyped_member);
  return &member[index];
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__strict(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__strict(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__strict(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__strict(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

size_t px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__drift_rate_horizontal(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__drift_rate_horizontal(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__drift_rate_horizontal(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__drift_rate_horizontal(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__drift_rate_horizontal(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__drift_rate_horizontal(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__drift_rate_horizontal(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

size_t px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__drift_rate_vertical(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__drift_rate_vertical(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__drift_rate_vertical(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__drift_rate_vertical(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__drift_rate_vertical(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__drift_rate_vertical(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__drift_rate_vertical(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

size_t px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__speed_horizontal_filtered(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__speed_horizontal_filtered(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__speed_horizontal_filtered(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__speed_horizontal_filtered(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__speed_horizontal_filtered(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__speed_horizontal_filtered(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__speed_horizontal_filtered(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_message_member_array[10] = {
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__SensorsStatusGnss, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "device_id_selected",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__SensorsStatusGnss, device_id_selected),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "device_ids",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__SensorsStatusGnss, device_ids),  // bytes offset in struct
    NULL,  // default value
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__device_ids,  // size() function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__device_ids,  // get_const(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__device_ids,  // get(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__device_ids,  // fetch(index, &value) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__device_ids,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "order",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__SensorsStatusGnss, order),  // bytes offset in struct
    NULL,  // default value
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__order,  // size() function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__order,  // get_const(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__order,  // get(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__order,  // fetch(index, &value) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__order,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "healthy",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__SensorsStatusGnss, healthy),  // bytes offset in struct
    NULL,  // default value
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__healthy,  // size() function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__healthy,  // get_const(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__healthy,  // get(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__healthy,  // fetch(index, &value) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__healthy,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "failed_checks",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__SensorsStatusGnss, failed_checks),  // bytes offset in struct
    NULL,  // default value
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__failed_checks,  // size() function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__failed_checks,  // get_const(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__failed_checks,  // get(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__failed_checks,  // fetch(index, &value) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__failed_checks,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "strict",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__SensorsStatusGnss, strict),  // bytes offset in struct
    NULL,  // default value
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__strict,  // size() function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__strict,  // get_const(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__strict,  // get(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__strict,  // fetch(index, &value) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__strict,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drift_rate_horizontal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__SensorsStatusGnss, drift_rate_horizontal),  // bytes offset in struct
    NULL,  // default value
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__drift_rate_horizontal,  // size() function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__drift_rate_horizontal,  // get_const(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__drift_rate_horizontal,  // get(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__drift_rate_horizontal,  // fetch(index, &value) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__drift_rate_horizontal,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drift_rate_vertical",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__SensorsStatusGnss, drift_rate_vertical),  // bytes offset in struct
    NULL,  // default value
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__drift_rate_vertical,  // size() function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__drift_rate_vertical,  // get_const(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__drift_rate_vertical,  // get(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__drift_rate_vertical,  // fetch(index, &value) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__drift_rate_vertical,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed_horizontal_filtered",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__SensorsStatusGnss, speed_horizontal_filtered),  // bytes offset in struct
    NULL,  // default value
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__size_function__SensorsStatusGnss__speed_horizontal_filtered,  // size() function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_const_function__SensorsStatusGnss__speed_horizontal_filtered,  // get_const(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__get_function__SensorsStatusGnss__speed_horizontal_filtered,  // get(index) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__fetch_function__SensorsStatusGnss__speed_horizontal_filtered,  // fetch(index, &value) function pointer
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__assign_function__SensorsStatusGnss__speed_horizontal_filtered,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_message_members = {
  "px4_msgs__msg",  // message namespace
  "SensorsStatusGnss",  // message name
  10,  // number of fields
  sizeof(px4_msgs__msg__SensorsStatusGnss),
  false,  // has_any_key_member_
  px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_message_member_array,  // message members
  px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_init_function,  // function to initialize message memory (memory has to be allocated)
  px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_message_type_support_handle = {
  0,
  &px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_message_members,
  get_message_typesupport_handle_function,
  &px4_msgs__msg__SensorsStatusGnss__get_type_hash,
  &px4_msgs__msg__SensorsStatusGnss__get_type_description,
  &px4_msgs__msg__SensorsStatusGnss__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_px4_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, px4_msgs, msg, SensorsStatusGnss)() {
  if (!px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_message_type_support_handle.typesupport_identifier) {
    px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &px4_msgs__msg__SensorsStatusGnss__rosidl_typesupport_introspection_c__SensorsStatusGnss_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
