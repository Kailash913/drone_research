// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/SensorsStatusGnss.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/sensors_status_gnss__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__SensorsStatusGnss__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6f, 0x78, 0x94, 0xb5, 0x96, 0x43, 0x58, 0x08,
      0xd6, 0xb3, 0x80, 0xab, 0x29, 0xca, 0xd0, 0x63,
      0x7e, 0xf7, 0x30, 0x26, 0xdb, 0xdc, 0x90, 0x73,
      0x6f, 0xf5, 0x82, 0xfc, 0x9b, 0xfb, 0xdd, 0x13,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__SensorsStatusGnss__TYPE_NAME[] = "px4_msgs/msg/SensorsStatusGnss";

// Define type names, field names, and default values
static char px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__device_id_selected[] = "device_id_selected";
static char px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__device_ids[] = "device_ids";
static char px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__order[] = "order";
static char px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__healthy[] = "healthy";
static char px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__failed_checks[] = "failed_checks";
static char px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__strict[] = "strict";
static char px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__drift_rate_horizontal[] = "drift_rate_horizontal";
static char px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__drift_rate_vertical[] = "drift_rate_vertical";
static char px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__speed_horizontal_filtered[] = "speed_horizontal_filtered";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__SensorsStatusGnss__FIELDS[] = {
  {
    {px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__device_id_selected, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__device_ids, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32_ARRAY,
      4,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__order, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT8_ARRAY,
      4,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__healthy, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN_ARRAY,
      4,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__failed_checks, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16_ARRAY,
      4,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__strict, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN_ARRAY,
      4,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__drift_rate_horizontal, 21, 21},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      4,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__drift_rate_vertical, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      4,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorsStatusGnss__FIELD_NAME__speed_horizontal_filtered, 25, 25},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      4,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
px4_msgs__msg__SensorsStatusGnss__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__SensorsStatusGnss__TYPE_NAME, 30, 30},
      {px4_msgs__msg__SensorsStatusGnss__FIELDS, 10, 10},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Per-receiver GNSS health and check diagnostics\n"
  "#\n"
  "# Published by the sensors module. Describes the latest sample of each receiver: to gate on a sample, use vehicle_gnss.usable.\n"
  "\n"
  "uint64 timestamp # [us] Time since system start\n"
  "\n"
  "uint32 device_id_selected # [-] Receiver that vehicle_gnss carries\n"
  "\n"
  "uint8 MAX_RECEIVERS = 4 # Length of the per-receiver arrays\n"
  "\n"
  "uint32[4] device_ids                 # [-] One entry per receiver, 0 where unused\n"
  "int8[4] order                        # [-] Fixed position of the receiver: 0 for the preferred one, otherwise for the first to publish, then in order of first publication. Changes only with the preference, -1 until the receiver publishes\n"
  "bool[4] healthy                      # Publishing, and has passed its checks for long enough\n"
  "uint16[4] failed_checks              # [-] Bitmask of the enabled checks that failed, VehicleGnss CHECK_* bits\n"
  "bool[4] strict                       # The pre-flight thresholds apply rather than the relaxed in-flight ones\n"
  "float32[4] drift_rate_horizontal     # [m/s] Horizontal position drift rate at rest\n"
  "float32[4] drift_rate_vertical       # [m/s] Vertical position drift rate at rest\n"
  "float32[4] speed_horizontal_filtered # [m/s] Filtered horizontal speed at rest\n"
  "\n"
  "# TOPICS sensors_status_gnss";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__SensorsStatusGnss__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__SensorsStatusGnss__TYPE_NAME, 30, 30},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 1266, 1266},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__SensorsStatusGnss__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__SensorsStatusGnss__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
