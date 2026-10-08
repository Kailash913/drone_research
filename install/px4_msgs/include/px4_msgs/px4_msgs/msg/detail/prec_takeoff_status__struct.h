// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/PrecTakeoffStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/prec_takeoff_status.h"


#ifndef PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'PREC_TAKEOFF_STATE_STOPPED'.
/**
  * Not active
 */
enum
{
  px4_msgs__msg__PrecTakeoffStatus__PREC_TAKEOFF_STATE_STOPPED = 0
};

/// Constant 'PREC_TAKEOFF_STATE_ONGOING'.
/**
  * Takeoff active; the estimator may still be acquiring the target
 */
enum
{
  px4_msgs__msg__PrecTakeoffStatus__PREC_TAKEOFF_STATE_ONGOING = 1
};

/// Constant 'PREC_TAKEOFF_STATE_DONE'.
/**
  * Takeoff altitude reached
 */
enum
{
  px4_msgs__msg__PrecTakeoffStatus__PREC_TAKEOFF_STATE_DONE = 2
};

/// Struct defined in msg/PrecTakeoffStatus in the package px4_msgs.
/**
  * Precision takeoff status.
  *
  * Published by: navigator (prec_takeoff.cpp).
  * Subscribed by: vision_target_estimator, flight_mode_manager (FlightTaskAuto).
  *
  * ONGOING while a vertical takeoff setpoint is active and MIS_TKO_PREC is set. DONE is published when the
  * takeoff altitude is reached, then STOPPED once the takeoff is no longer active. Published every Navigator cycle.
 */
typedef struct px4_msgs__msg__PrecTakeoffStatus
{
  /// Time since system start
  uint64_t timestamp;
  /// Current precision-takeoff state
  uint8_t state;
  /// True after a valid target adjusted the horizontal setpoint
  bool setpoint_adjusted;
} px4_msgs__msg__PrecTakeoffStatus;

// Struct for a sequence of px4_msgs__msg__PrecTakeoffStatus.
typedef struct px4_msgs__msg__PrecTakeoffStatus__Sequence
{
  px4_msgs__msg__PrecTakeoffStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__PrecTakeoffStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__STRUCT_H_
