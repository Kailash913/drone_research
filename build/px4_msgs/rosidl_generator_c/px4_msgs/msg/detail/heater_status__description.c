// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/HeaterStatus.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/heater_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__HeaterStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xb5, 0xb5, 0x60, 0xe0, 0x48, 0x2f, 0x07, 0x1d,
      0x46, 0x73, 0x1b, 0xa3, 0xb7, 0x2d, 0x72, 0x57,
      0xf1, 0x7a, 0x64, 0x3b, 0xe5, 0xc3, 0x8d, 0x27,
      0x4f, 0xc9, 0x88, 0x8e, 0x5b, 0x0d, 0xc6, 0xcd,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__HeaterStatus__TYPE_NAME[] = "px4_msgs/msg/HeaterStatus";

// Define type names, field names, and default values
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__device_id[] = "device_id";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__heater_on[] = "heater_on";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__temperature_target_met[] = "temperature_target_met";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__temperature_activation_threshold_met[] = "temperature_activation_threshold_met";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__temperature_sensor[] = "temperature_sensor";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__temperature_target[] = "temperature_target";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__controller_period_usec[] = "controller_period_usec";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__controller_time_on_usec[] = "controller_time_on_usec";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__proportional_value[] = "proportional_value";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__integrator_value[] = "integrator_value";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__feed_forward_value[] = "feed_forward_value";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__nominal_multiplier[] = "nominal_multiplier";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__mode[] = "mode";
static char px4_msgs__msg__HeaterStatus__FIELD_NAME__temperature_source[] = "temperature_source";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__HeaterStatus__FIELDS[] = {
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__device_id, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__heater_on, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__temperature_target_met, 22, 22},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__temperature_activation_threshold_met, 36, 36},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__temperature_sensor, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__temperature_target, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__controller_period_usec, 22, 22},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__controller_time_on_usec, 23, 23},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__proportional_value, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__integrator_value, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__feed_forward_value, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__nominal_multiplier, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__mode, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__HeaterStatus__FIELD_NAME__temperature_source, 18, 18},
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
px4_msgs__msg__HeaterStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__HeaterStatus__TYPE_NAME, 25, 25},
      {px4_msgs__msg__HeaterStatus__FIELDS, 15, 15},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint64 timestamp\\t# time since system start (microseconds)\n"
  "\n"
  "uint32 device_id\n"
  "\n"
  "bool heater_on\\t\\t\\t# element driven this control period (controller_time_on_usec > 0)\n"
  "bool temperature_target_met\n"
  "bool temperature_activation_threshold_met\n"
  "\n"
  "float32 temperature_sensor\n"
  "float32 temperature_target\n"
  "\n"
  "uint32 controller_period_usec\n"
  "uint32 controller_time_on_usec\n"
  "\n"
  "float32 proportional_value\n"
  "float32 integrator_value\n"
  "float32 feed_forward_value\n"
  "\n"
  "float32 nominal_multiplier\\t# duty scaling from HEATERn_NOM_V: (V_nom/V)^2 above V_nom, 1 without compensation, 0 without battery data\n"
  "\n"
  "uint8 MODE_GPIO  = 1\n"
  "uint8 MODE_PX4IO = 2\n"
  "uint8 mode\n"
  "\n"
  "uint8 TEMPERATURE_SOURCE_IMU   = 0\n"
  "uint8 TEMPERATURE_SOURCE_HYGRO = 1\n"
  "uint8 temperature_source";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__HeaterStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__HeaterStatus__TYPE_NAME, 25, 25},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 713, 713},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__HeaterStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__HeaterStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
