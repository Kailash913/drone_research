// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/ExternalGimbalManagerStatus.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/external_gimbal_manager_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__ExternalGimbalManagerStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xf4, 0xa9, 0xb0, 0x50, 0xaa, 0xf8, 0xaf, 0xed,
      0x51, 0x18, 0x1d, 0xe2, 0x45, 0x29, 0xf6, 0x30,
      0x19, 0x5d, 0xa4, 0x1f, 0x90, 0xdc, 0xc5, 0x91,
      0xe5, 0x8e, 0x97, 0x6b, 0xed, 0x35, 0x13, 0xf8,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__ExternalGimbalManagerStatus__TYPE_NAME[] = "px4_msgs/msg/ExternalGimbalManagerStatus";

// Define type names, field names, and default values
static char px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__manager_sysid[] = "manager_sysid";
static char px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__manager_compid[] = "manager_compid";
static char px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__flags[] = "flags";
static char px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__gimbal_device_id[] = "gimbal_device_id";
static char px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__primary_control_sysid[] = "primary_control_sysid";
static char px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__primary_control_compid[] = "primary_control_compid";
static char px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__secondary_control_sysid[] = "secondary_control_sysid";
static char px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__secondary_control_compid[] = "secondary_control_compid";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__ExternalGimbalManagerStatus__FIELDS[] = {
  {
    {px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__manager_sysid, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__manager_compid, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__flags, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__gimbal_device_id, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__primary_control_sysid, 21, 21},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__primary_control_compid, 22, 22},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__secondary_control_sysid, 23, 23},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__ExternalGimbalManagerStatus__FIELD_NAME__secondary_control_compid, 24, 24},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
px4_msgs__msg__ExternalGimbalManagerStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__ExternalGimbalManagerStatus__TYPE_NAME, 40, 40},
      {px4_msgs__msg__ExternalGimbalManagerStatus__FIELDS, 9, 9},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# External gimbal manager status\n"
  "#\n"
  "# Status of a gimbal manager running on another component (not us), decoded from\n"
  "# an incoming GIMBAL_MANAGER_STATUS message. Used to track which component\n"
  "# currently controls an external gimbal manager.\n"
  "\n"
  "uint64 timestamp # [us] Time since system start\n"
  "\n"
  "uint8 manager_sysid # [-] System id of the external gimbal manager\n"
  "uint8 manager_compid # [-] Component id of the external gimbal manager\n"
  "\n"
  "uint32 flags # [-]\n"
  "uint8 gimbal_device_id\n"
  "uint8 primary_control_sysid\n"
  "uint8 primary_control_compid\n"
  "uint8 secondary_control_sysid\n"
  "uint8 secondary_control_compid";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__ExternalGimbalManagerStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__ExternalGimbalManagerStatus__TYPE_NAME, 40, 40},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 589, 589},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__ExternalGimbalManagerStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__ExternalGimbalManagerStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
