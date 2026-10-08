// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/SensorsStatusGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensors_status_gnss.h"


#ifndef PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'MAX_RECEIVERS'.
/**
  * Length of the per-receiver arrays
 */
enum
{
  px4_msgs__msg__SensorsStatusGnss__MAX_RECEIVERS = 4
};

/// Struct defined in msg/SensorsStatusGnss in the package px4_msgs.
/**
  * Per-receiver GNSS health and check diagnostics
  *
  * Published by the sensors module. Describes the latest sample of each receiver: to gate on a sample, use vehicle_gnss.usable.
 */
typedef struct px4_msgs__msg__SensorsStatusGnss
{
  /// Time since system start
  uint64_t timestamp;
  /// Receiver that vehicle_gnss carries
  uint32_t device_id_selected;
  /// One entry per receiver, 0 where unused
  uint32_t device_ids[4];
  /// Fixed position of the receiver: 0 for the preferred one, otherwise for the first to publish, then in order of first publication. Changes only with the preference, -1 until the receiver publishes
  int8_t order[4];
  /// Publishing, and has passed its checks for long enough
  bool healthy[4];
  /// Bitmask of the enabled checks that failed, VehicleGnss CHECK_* bits
  uint16_t failed_checks[4];
  /// The pre-flight thresholds apply rather than the relaxed in-flight ones
  bool strict[4];
  /// Horizontal position drift rate at rest
  float drift_rate_horizontal[4];
  /// Vertical position drift rate at rest
  float drift_rate_vertical[4];
  /// Filtered horizontal speed at rest
  float speed_horizontal_filtered[4];
} px4_msgs__msg__SensorsStatusGnss;

// Struct for a sequence of px4_msgs__msg__SensorsStatusGnss.
typedef struct px4_msgs__msg__SensorsStatusGnss__Sequence
{
  px4_msgs__msg__SensorsStatusGnss * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__SensorsStatusGnss__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__STRUCT_H_
