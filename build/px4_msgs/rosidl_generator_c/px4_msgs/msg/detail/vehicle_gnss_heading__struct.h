// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/VehicleGnssHeading.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/vehicle_gnss_heading.h"


#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS_HEADING__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS_HEADING__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/VehicleGnssHeading in the package px4_msgs.
/**
  * GNSS heading from a dual-antenna or moving-baseline receiver
  *
  * Published by the sensors module from sensor_gnss_relative. Consumed by EKF2 independently from position and velocity.
 */
typedef struct px4_msgs__msg__VehicleGnssHeading
{
  /// time since system start (microseconds)
  uint64_t timestamp;
  /// time since system start (microseconds) - actual measurement time
  uint64_t timestamp_sample;
  /// unique device ID for the sensor that does not change between power cycles
  uint32_t device_id;
  /// body-frame heading rel to NED from dual antenna array (rad, [-PI, PI])
  float heading;
  /// 1-sigma heading accuracy (rad)
  float heading_accuracy;
  /// yaw of the configured antenna baseline in the body frame; heading + heading_offset is the measured baseline heading (rad, [-PI, PI])
  float heading_offset;
  /// antenna baseline length reported by the receiver, NaN if it doesn't report one (m)
  float baseline_length;
  /// jamming_state of the receiver providing the heading, values as in SensorGnss (0: Unknown, 1: OK, 2: Mitigated, 3: Detected)
  uint8_t jamming_state;
  /// spoofing_state of the receiver providing the heading, values as in SensorGnss (0: Unknown, 1: OK, 2: Mitigated, 3: Detected)
  uint8_t spoofing_state;
  /// heading may be used: its receiver reports no spoofing or jamming that the enabled checks reject
  bool usable;
} px4_msgs__msg__VehicleGnssHeading;

// Struct for a sequence of px4_msgs__msg__VehicleGnssHeading.
typedef struct px4_msgs__msg__VehicleGnssHeading__Sequence
{
  px4_msgs__msg__VehicleGnssHeading * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__VehicleGnssHeading__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS_HEADING__STRUCT_H_
