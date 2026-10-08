// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/VehicleGnssHeading.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/vehicle_gnss_heading__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__VehicleGnssHeading__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6e, 0x82, 0x62, 0x95, 0xa1, 0x40, 0x07, 0x92,
      0x33, 0x7e, 0x58, 0x26, 0xfe, 0x29, 0xe2, 0x83,
      0x32, 0x39, 0x5c, 0x2b, 0x6f, 0x8a, 0x75, 0x4c,
      0x3e, 0xb9, 0x56, 0xd0, 0xf2, 0x0d, 0x9f, 0x53,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__VehicleGnssHeading__TYPE_NAME[] = "px4_msgs/msg/VehicleGnssHeading";

// Define type names, field names, and default values
static char px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__timestamp_sample[] = "timestamp_sample";
static char px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__device_id[] = "device_id";
static char px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__heading[] = "heading";
static char px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__heading_accuracy[] = "heading_accuracy";
static char px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__heading_offset[] = "heading_offset";
static char px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__baseline_length[] = "baseline_length";
static char px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__jamming_state[] = "jamming_state";
static char px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__spoofing_state[] = "spoofing_state";
static char px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__usable[] = "usable";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__VehicleGnssHeading__FIELDS[] = {
  {
    {px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__timestamp_sample, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__device_id, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__heading, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__heading_accuracy, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__heading_offset, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__baseline_length, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__jamming_state, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__spoofing_state, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnssHeading__FIELD_NAME__usable, 6, 6},
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
px4_msgs__msg__VehicleGnssHeading__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__VehicleGnssHeading__TYPE_NAME, 31, 31},
      {px4_msgs__msg__VehicleGnssHeading__FIELDS, 10, 10},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# GNSS heading from a dual-antenna or moving-baseline receiver\n"
  "#\n"
  "# Published by the sensors module from sensor_gnss_relative. Consumed by EKF2 independently from position and velocity.\n"
  "\n"
  "uint64 timestamp              # time since system start (microseconds)\n"
  "uint64 timestamp_sample       # time since system start (microseconds) - actual measurement time\n"
  "\n"
  "uint32 device_id              # unique device ID for the sensor that does not change between power cycles\n"
  "\n"
  "float32 heading               # body-frame heading rel to NED from dual antenna array (rad, [-PI, PI])\n"
  "float32 heading_accuracy      # 1-sigma heading accuracy (rad)\n"
  "float32 heading_offset        # yaw of the configured antenna baseline in the body frame; heading + heading_offset is the measured baseline heading (rad, [-PI, PI])\n"
  "float32 baseline_length       # antenna baseline length reported by the receiver, NaN if it doesn't report one (m)\n"
  "\n"
  "uint8 jamming_state           # jamming_state of the receiver providing the heading, values as in SensorGnss (0: Unknown, 1: OK, 2: Mitigated, 3: Detected)\n"
  "uint8 spoofing_state          # spoofing_state of the receiver providing the heading, values as in SensorGnss (0: Unknown, 1: OK, 2: Mitigated, 3: Detected)\n"
  "bool usable                   # heading may be used: its receiver reports no spoofing or jamming that the enabled checks reject";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__VehicleGnssHeading__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__VehicleGnssHeading__TYPE_NAME, 31, 31},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 1350, 1350},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__VehicleGnssHeading__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__VehicleGnssHeading__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
