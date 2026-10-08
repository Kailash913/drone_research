// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/UavcanFirmwareUpdate.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/uavcan_firmware_update.h"


#ifndef PX4_MSGS__MSG__DETAIL__UAVCAN_FIRMWARE_UPDATE__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__UAVCAN_FIRMWARE_UPDATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/UavcanFirmwareUpdate in the package px4_msgs.
typedef struct px4_msgs__msg__UavcanFirmwareUpdate
{
  /// time since system start (microseconds)
  uint64_t timestamp;
  /// true when one or more nodes requiring a firmware update have been detected and the update is not yet complete
  bool pending_updates;
} px4_msgs__msg__UavcanFirmwareUpdate;

// Struct for a sequence of px4_msgs__msg__UavcanFirmwareUpdate.
typedef struct px4_msgs__msg__UavcanFirmwareUpdate__Sequence
{
  px4_msgs__msg__UavcanFirmwareUpdate * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__UavcanFirmwareUpdate__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__UAVCAN_FIRMWARE_UPDATE__STRUCT_H_
