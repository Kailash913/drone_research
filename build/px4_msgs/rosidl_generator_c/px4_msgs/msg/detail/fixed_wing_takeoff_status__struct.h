// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/FixedWingTakeoffStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/fixed_wing_takeoff_status.h"


#ifndef PX4_MSGS__MSG__DETAIL__FIXED_WING_TAKEOFF_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__FIXED_WING_TAKEOFF_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/FixedWingTakeoffStatus in the package px4_msgs.
/**
  * Status of a fixed-wing takeoff
  * Passes information from the FixedWingModeManager to the Navigator.
 */
typedef struct px4_msgs__msg__FixedWingTakeoffStatus
{
  /// time since system start
  uint64_t timestamp;
  /// Whether the takeoff climbout is finished (altitude, or time if FW_TKO_CLMB_T is set)
  bool climbout_completed;
} px4_msgs__msg__FixedWingTakeoffStatus;

// Struct for a sequence of px4_msgs__msg__FixedWingTakeoffStatus.
typedef struct px4_msgs__msg__FixedWingTakeoffStatus__Sequence
{
  px4_msgs__msg__FixedWingTakeoffStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__FixedWingTakeoffStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__FIXED_WING_TAKEOFF_STATUS__STRUCT_H_
