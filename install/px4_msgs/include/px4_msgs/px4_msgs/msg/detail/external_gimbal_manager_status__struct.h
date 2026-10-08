// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/ExternalGimbalManagerStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/external_gimbal_manager_status.h"


#ifndef PX4_MSGS__MSG__DETAIL__EXTERNAL_GIMBAL_MANAGER_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__EXTERNAL_GIMBAL_MANAGER_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/ExternalGimbalManagerStatus in the package px4_msgs.
/**
  * External gimbal manager status
  *
  * Status of a gimbal manager running on another component (not us), decoded from
  * an incoming GIMBAL_MANAGER_STATUS message. Used to track which component
  * currently controls an external gimbal manager.
 */
typedef struct px4_msgs__msg__ExternalGimbalManagerStatus
{
  /// Time since system start
  uint64_t timestamp;
  /// System id of the external gimbal manager
  uint8_t manager_sysid;
  /// Component id of the external gimbal manager
  uint8_t manager_compid;
  uint32_t flags;
  uint8_t gimbal_device_id;
  uint8_t primary_control_sysid;
  uint8_t primary_control_compid;
  uint8_t secondary_control_sysid;
  uint8_t secondary_control_compid;
} px4_msgs__msg__ExternalGimbalManagerStatus;

// Struct for a sequence of px4_msgs__msg__ExternalGimbalManagerStatus.
typedef struct px4_msgs__msg__ExternalGimbalManagerStatus__Sequence
{
  px4_msgs__msg__ExternalGimbalManagerStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__ExternalGimbalManagerStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__EXTERNAL_GIMBAL_MANAGER_STATUS__STRUCT_H_
