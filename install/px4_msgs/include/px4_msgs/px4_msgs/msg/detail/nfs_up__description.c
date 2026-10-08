// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/NfsUp.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/nfs_up__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__NfsUp__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xba, 0x53, 0xe0, 0xc1, 0x47, 0xdc, 0x25, 0x95,
      0x7c, 0x1e, 0x03, 0xeb, 0x2b, 0xad, 0xcf, 0xd3,
      0xca, 0x93, 0x9e, 0x7a, 0x1c, 0x49, 0x73, 0x90,
      0x35, 0xe0, 0x46, 0x5e, 0xed, 0x8c, 0x5c, 0x5e,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__NfsUp__TYPE_NAME[] = "px4_msgs/msg/NfsUp";

// Define type names, field names, and default values
static char px4_msgs__msg__NfsUp__FIELD_NAME__timestamp[] = "timestamp";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__NfsUp__FIELDS[] = {
  {
    {px4_msgs__msg__NfsUp__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
px4_msgs__msg__NfsUp__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__NfsUp__TYPE_NAME, 18, 18},
      {px4_msgs__msg__NfsUp__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint64 timestamp        # time since system start (microseconds)";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__NfsUp__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__NfsUp__TYPE_NAME, 18, 18},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 65, 65},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__NfsUp__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__NfsUp__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
