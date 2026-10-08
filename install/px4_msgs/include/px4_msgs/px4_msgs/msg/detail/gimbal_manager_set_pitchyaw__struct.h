// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/GimbalManagerSetPitchyaw.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/gimbal_manager_set_pitchyaw.h"


#ifndef PX4_MSGS__MSG__DETAIL__GIMBAL_MANAGER_SET_PITCHYAW__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__GIMBAL_MANAGER_SET_PITCHYAW__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'GIMBAL_MANAGER_FLAGS_PITCH_LOCK'.
enum
{
  px4_msgs__msg__GimbalManagerSetPitchyaw__GIMBAL_MANAGER_FLAGS_PITCH_LOCK = 8ul
};

/// Constant 'GIMBAL_MANAGER_FLAGS_YAW_LOCK'.
enum
{
  px4_msgs__msg__GimbalManagerSetPitchyaw__GIMBAL_MANAGER_FLAGS_YAW_LOCK = 16ul
};

/// Constant 'GIMBAL_MANAGER_FLAGS_YAW_IN_EARTH_FRAME'.
enum
{
  px4_msgs__msg__GimbalManagerSetPitchyaw__GIMBAL_MANAGER_FLAGS_YAW_IN_EARTH_FRAME = 64ul
};

/// Struct defined in msg/GimbalManagerSetPitchyaw in the package px4_msgs.
/**
  * Gimbal manager pitch/yaw setpoint 
  *
  * This is sent by PX4 (acting as a gimbal manager client) to an
  * external gimbal manager). Streamed out as GIMBAL_MANAGER_SET_PITCHYAW.
 */
typedef struct px4_msgs__msg__GimbalManagerSetPitchyaw
{
  /// Time since system start
  uint64_t timestamp;
  /// System id of the external gimbal manager
  uint8_t target_system;
  /// Component id of the external gimbal manager
  uint8_t target_component;
  /// Gimbal device to address (0 for all)
  uint8_t gimbal_device_id;
  /// GIMBAL_MANAGER_FLAGS bitmask
  uint32_t flags;
  /// [rad] [@invalid NaN to ignore] pitch angle
  float pitch;
  /// [rad] [@invalid NaN to ignore] yaw angle
  float yaw;
  /// [rad/s] [@invalid NaN to ignore] Pitch angular rate
  float pitch_rate;
  /// [rad/s] [@invalid NaN to ignore] Yaw angular rate
  float yaw_rate;
} px4_msgs__msg__GimbalManagerSetPitchyaw;

// Struct for a sequence of px4_msgs__msg__GimbalManagerSetPitchyaw.
typedef struct px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence
{
  px4_msgs__msg__GimbalManagerSetPitchyaw * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__GIMBAL_MANAGER_SET_PITCHYAW__STRUCT_H_
