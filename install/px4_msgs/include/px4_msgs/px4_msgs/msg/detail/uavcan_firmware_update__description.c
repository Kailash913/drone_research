// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/UavcanFirmwareUpdate.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/uavcan_firmware_update__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__UavcanFirmwareUpdate__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6b, 0xc0, 0xea, 0x25, 0x95, 0xca, 0x9e, 0xea,
      0x4a, 0x21, 0xc2, 0x32, 0x52, 0x25, 0xe0, 0x63,
      0x9d, 0xde, 0x9d, 0x7b, 0xef, 0x80, 0xef, 0x72,
      0x8a, 0x42, 0xa7, 0x78, 0x07, 0x10, 0x45, 0x6f,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__UavcanFirmwareUpdate__TYPE_NAME[] = "px4_msgs/msg/UavcanFirmwareUpdate";

// Define type names, field names, and default values
static char px4_msgs__msg__UavcanFirmwareUpdate__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__UavcanFirmwareUpdate__FIELD_NAME__pending_updates[] = "pending_updates";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__UavcanFirmwareUpdate__FIELDS[] = {
  {
    {px4_msgs__msg__UavcanFirmwareUpdate__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__UavcanFirmwareUpdate__FIELD_NAME__pending_updates, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
px4_msgs__msg__UavcanFirmwareUpdate__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__UavcanFirmwareUpdate__TYPE_NAME, 33, 33},
      {px4_msgs__msg__UavcanFirmwareUpdate__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint64 timestamp        # time since system start (microseconds)\n"
  "bool pending_updates    # true when one or more nodes requiring a firmware update have been detected and the update is not yet complete";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__UavcanFirmwareUpdate__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__UavcanFirmwareUpdate__TYPE_NAME, 33, 33},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 201, 201},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__UavcanFirmwareUpdate__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__UavcanFirmwareUpdate__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
