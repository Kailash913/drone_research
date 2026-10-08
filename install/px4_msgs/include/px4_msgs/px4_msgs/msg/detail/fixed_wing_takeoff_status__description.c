// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/FixedWingTakeoffStatus.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/fixed_wing_takeoff_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__FixedWingTakeoffStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x06, 0x23, 0x55, 0xe9, 0x66, 0x9d, 0xc1, 0x0b,
      0x34, 0x2c, 0xa3, 0x5d, 0xfa, 0x4b, 0xff, 0xce,
      0xca, 0x8d, 0xcb, 0xc2, 0x3c, 0x98, 0x5a, 0x7d,
      0xd2, 0xc3, 0xb9, 0x65, 0x1e, 0x2a, 0xf5, 0xa5,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__FixedWingTakeoffStatus__TYPE_NAME[] = "px4_msgs/msg/FixedWingTakeoffStatus";

// Define type names, field names, and default values
static char px4_msgs__msg__FixedWingTakeoffStatus__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__FixedWingTakeoffStatus__FIELD_NAME__climbout_completed[] = "climbout_completed";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__FixedWingTakeoffStatus__FIELDS[] = {
  {
    {px4_msgs__msg__FixedWingTakeoffStatus__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__FixedWingTakeoffStatus__FIELD_NAME__climbout_completed, 18, 18},
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
px4_msgs__msg__FixedWingTakeoffStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__FixedWingTakeoffStatus__TYPE_NAME, 35, 35},
      {px4_msgs__msg__FixedWingTakeoffStatus__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Status of a fixed-wing takeoff\n"
  "# Passes information from the FixedWingModeManager to the Navigator.\n"
  "\n"
  "uint64 timestamp # [us] time since system start\n"
  "\n"
  "bool climbout_completed  # Whether the takeoff climbout is finished (altitude, or time if FW_TKO_CLMB_T is set)";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__FixedWingTakeoffStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__FixedWingTakeoffStatus__TYPE_NAME, 35, 35},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 264, 264},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__FixedWingTakeoffStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__FixedWingTakeoffStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
