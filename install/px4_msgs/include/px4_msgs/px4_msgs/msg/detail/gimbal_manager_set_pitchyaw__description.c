// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/GimbalManagerSetPitchyaw.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/gimbal_manager_set_pitchyaw__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__GimbalManagerSetPitchyaw__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x24, 0x5d, 0xfc, 0xbe, 0x44, 0x67, 0xc4, 0x95,
      0x08, 0x54, 0x23, 0x82, 0x3a, 0xa8, 0xe0, 0x13,
      0xf7, 0x65, 0x16, 0x55, 0x6d, 0xb8, 0x96, 0xfe,
      0x7d, 0x92, 0xb0, 0xc1, 0x45, 0xf6, 0x2b, 0x05,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__GimbalManagerSetPitchyaw__TYPE_NAME[] = "px4_msgs/msg/GimbalManagerSetPitchyaw";

// Define type names, field names, and default values
static char px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__target_system[] = "target_system";
static char px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__target_component[] = "target_component";
static char px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__gimbal_device_id[] = "gimbal_device_id";
static char px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__flags[] = "flags";
static char px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__pitch[] = "pitch";
static char px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__yaw[] = "yaw";
static char px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__pitch_rate[] = "pitch_rate";
static char px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__yaw_rate[] = "yaw_rate";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__GimbalManagerSetPitchyaw__FIELDS[] = {
  {
    {px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__target_system, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__target_component, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__gimbal_device_id, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__flags, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__pitch, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__yaw, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__pitch_rate, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__GimbalManagerSetPitchyaw__FIELD_NAME__yaw_rate, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
px4_msgs__msg__GimbalManagerSetPitchyaw__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__GimbalManagerSetPitchyaw__TYPE_NAME, 37, 37},
      {px4_msgs__msg__GimbalManagerSetPitchyaw__FIELDS, 9, 9},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Gimbal manager pitch/yaw setpoint \n"
  "#\n"
  "# This is sent by PX4 (acting as a gimbal manager client) to an\n"
  "# external gimbal manager). Streamed out as GIMBAL_MANAGER_SET_PITCHYAW.\n"
  "\n"
  "uint64 timestamp # [us] Time since system start\n"
  "\n"
  "uint8 target_system # [-] System id of the external gimbal manager\n"
  "uint8 target_component\\t# [-] Component id of the external gimbal manager\n"
  "uint8 gimbal_device_id # [-] Gimbal device to address (0 for all)\n"
  "\n"
  "uint32 flags # [@enum GIMBAL_MANAGER_FLAGS] GIMBAL_MANAGER_FLAGS bitmask\n"
  "uint32 GIMBAL_MANAGER_FLAGS_PITCH_LOCK = 8\n"
  "uint32 GIMBAL_MANAGER_FLAGS_YAW_LOCK = 16\n"
  "uint32 GIMBAL_MANAGER_FLAGS_YAW_IN_EARTH_FRAME = 64\n"
  "\n"
  "float32 pitch # [rad] [@invalid NaN to ignore] pitch angle\n"
  "float32 yaw # [rad] [@invalid NaN to ignore] yaw angle\n"
  "float32 pitch_rate # [rad/s] [@invalid NaN to ignore] Pitch angular rate\n"
  "float32 yaw_rate # [rad/s] [@invalid NaN to ignore] Yaw angular rate";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__GimbalManagerSetPitchyaw__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__GimbalManagerSetPitchyaw__TYPE_NAME, 37, 37},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 900, 900},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__GimbalManagerSetPitchyaw__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__GimbalManagerSetPitchyaw__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
