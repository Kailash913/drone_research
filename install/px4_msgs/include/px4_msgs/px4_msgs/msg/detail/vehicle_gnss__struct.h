// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/VehicleGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/vehicle_gnss.h"


#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'CHECK_NSATS'.
/**
  * Too few satellites
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_NSATS = 1
};

/// Constant 'CHECK_PDOP'.
/**
  * Position dilution of precision too high
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_PDOP = 2
};

/// Constant 'CHECK_EPH'.
/**
  * Horizontal position accuracy too low
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_EPH = 4
};

/// Constant 'CHECK_EPV'.
/**
  * Vertical position accuracy too low
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_EPV = 8
};

/// Constant 'CHECK_SACC'.
/**
  * Speed accuracy too low
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_SACC = 16
};

/// Constant 'CHECK_HDRIFT'.
/**
  * Horizontal position drift at rest too high
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_HDRIFT = 32
};

/// Constant 'CHECK_VDRIFT'.
/**
  * Vertical position drift at rest too high
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_VDRIFT = 64
};

/// Constant 'CHECK_HSPEED'.
/**
  * Horizontal speed at rest too high
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_HSPEED = 128
};

/// Constant 'CHECK_VSPEED'.
/**
  * Vertical speed at rest too high
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_VSPEED = 256
};

/// Constant 'CHECK_SPOOFED'.
/**
  * Receiver reports spoofing
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_SPOOFED = 512
};

/// Constant 'CHECK_FIX'.
/**
  * Fix type too low
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_FIX = 1024
};

/// Constant 'CHECK_JAMMED'.
/**
  * Receiver reports jamming
 */
enum
{
  px4_msgs__msg__VehicleGnss__CHECK_JAMMED = 2048
};

// Include directives for member types
// Member 'receiver'
#include "px4_msgs/msg/detail/sensor_gnss__struct.h"

/// Struct defined in msg/VehicleGnss in the package px4_msgs.
/**
  * Selected GNSS solution
  *
  * Published by the sensors module for every sample of the selected receiver, usable or not, with the selection state and the check result for that sample.
  * Heading is on vehicle_gnss_heading.
 */
typedef struct px4_msgs__msg__VehicleGnss
{
  /// Time since system start
  uint64_t timestamp;
  /// Measurement time, delay corrected. Use this rather than receiver.timestamp_sample, which holds the same value
  uint64_t timestamp_sample;
  /// The selected receiver's sensor_gnss sample with the corrected timestamp_sample
  px4_msgs__msg__SensorGnss receiver;
  /// [m] [@frame FRD] Antenna position of the selected receiver
  float antenna_offset[3];
  /// Selection state
  /// [-] sensor_gnss instance of the selected receiver
  uint8_t selected_instance;
  /// Increments when the selected receiver changes
  uint8_t selection_count;
  /// Check result for this sample
  /// Sample may be used: the receiver has passed its checks for long enough
  bool usable;
  /// Bitmask of the enabled checks that failed
  uint16_t failed_checks;
} px4_msgs__msg__VehicleGnss;

// Struct for a sequence of px4_msgs__msg__VehicleGnss.
typedef struct px4_msgs__msg__VehicleGnss__Sequence
{
  px4_msgs__msg__VehicleGnss * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__VehicleGnss__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__STRUCT_H_
