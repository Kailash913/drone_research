// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/NfsUp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/nfs_up.h"


#ifndef PX4_MSGS__MSG__DETAIL__NFS_UP__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__NFS_UP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/NfsUp in the package px4_msgs.
typedef struct px4_msgs__msg__NfsUp
{
  /// time since system start (microseconds)
  uint64_t timestamp;
} px4_msgs__msg__NfsUp;

// Struct for a sequence of px4_msgs__msg__NfsUp.
typedef struct px4_msgs__msg__NfsUp__Sequence
{
  px4_msgs__msg__NfsUp * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__NfsUp__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__NFS_UP__STRUCT_H_
