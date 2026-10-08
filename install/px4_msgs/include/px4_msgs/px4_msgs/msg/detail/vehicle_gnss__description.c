// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/VehicleGnss.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/vehicle_gnss__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__VehicleGnss__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xb7, 0x04, 0xe0, 0xfd, 0x53, 0xa2, 0xe6, 0xf5,
      0xb6, 0xae, 0x16, 0xdd, 0x00, 0x0c, 0xfd, 0x48,
      0x52, 0x97, 0x82, 0x8f, 0x35, 0x5d, 0xf5, 0x02,
      0x51, 0xc9, 0x44, 0x36, 0x59, 0xa5, 0x17, 0xf6,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "px4_msgs/msg/detail/sensor_gnss__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t px4_msgs__msg__SensorGnss__EXPECTED_HASH = {1, {
    0x67, 0x02, 0xf9, 0xcb, 0x39, 0xf2, 0x0c, 0xbb,
    0x5c, 0xc7, 0x13, 0x0d, 0x1a, 0x07, 0x3b, 0xf7,
    0x97, 0xad, 0xf2, 0xe5, 0x18, 0x14, 0x4b, 0xc9,
    0x68, 0x8a, 0x35, 0xe7, 0x1a, 0x78, 0xa6, 0x8e,
  }};
#endif

static char px4_msgs__msg__VehicleGnss__TYPE_NAME[] = "px4_msgs/msg/VehicleGnss";
static char px4_msgs__msg__SensorGnss__TYPE_NAME[] = "px4_msgs/msg/SensorGnss";

// Define type names, field names, and default values
static char px4_msgs__msg__VehicleGnss__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__VehicleGnss__FIELD_NAME__timestamp_sample[] = "timestamp_sample";
static char px4_msgs__msg__VehicleGnss__FIELD_NAME__receiver[] = "receiver";
static char px4_msgs__msg__VehicleGnss__FIELD_NAME__antenna_offset[] = "antenna_offset";
static char px4_msgs__msg__VehicleGnss__FIELD_NAME__selected_instance[] = "selected_instance";
static char px4_msgs__msg__VehicleGnss__FIELD_NAME__selection_count[] = "selection_count";
static char px4_msgs__msg__VehicleGnss__FIELD_NAME__usable[] = "usable";
static char px4_msgs__msg__VehicleGnss__FIELD_NAME__failed_checks[] = "failed_checks";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__VehicleGnss__FIELDS[] = {
  {
    {px4_msgs__msg__VehicleGnss__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnss__FIELD_NAME__timestamp_sample, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnss__FIELD_NAME__receiver, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {px4_msgs__msg__SensorGnss__TYPE_NAME, 23, 23},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnss__FIELD_NAME__antenna_offset, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      3,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnss__FIELD_NAME__selected_instance, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnss__FIELD_NAME__selection_count, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnss__FIELD_NAME__usable, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__VehicleGnss__FIELD_NAME__failed_checks, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription px4_msgs__msg__VehicleGnss__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {px4_msgs__msg__SensorGnss__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
px4_msgs__msg__VehicleGnss__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__VehicleGnss__TYPE_NAME, 24, 24},
      {px4_msgs__msg__VehicleGnss__FIELDS, 8, 8},
    },
    {px4_msgs__msg__VehicleGnss__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&px4_msgs__msg__SensorGnss__EXPECTED_HASH, px4_msgs__msg__SensorGnss__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = px4_msgs__msg__SensorGnss__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Selected GNSS solution\n"
  "#\n"
  "# Published by the sensors module for every sample of the selected receiver, usable or not, with the selection state and the check result for that sample.\n"
  "# Heading is on vehicle_gnss_heading.\n"
  "\n"
  "uint64 timestamp        # [us] Time since system start\n"
  "uint64 timestamp_sample # [us] Measurement time, delay corrected. Use this rather than receiver.timestamp_sample, which holds the same value\n"
  "\n"
  "SensorGnss receiver # The selected receiver's sensor_gnss sample with the corrected timestamp_sample\n"
  "\n"
  "float32[3] antenna_offset # [m] [@frame FRD] Antenna position of the selected receiver\n"
  "\n"
  "# Selection state\n"
  "uint8 selected_instance # [-] sensor_gnss instance of the selected receiver\n"
  "uint8 selection_count   # [-] Increments when the selected receiver changes\n"
  "\n"
  "# Check result for this sample\n"
  "bool usable                 # Sample may be used: the receiver has passed its checks for long enough\n"
  "uint16 failed_checks        # [@enum CHECK] Bitmask of the enabled checks that failed\n"
  "uint16 CHECK_NSATS   = 1    # Too few satellites\n"
  "uint16 CHECK_PDOP    = 2    # Position dilution of precision too high\n"
  "uint16 CHECK_EPH     = 4    # Horizontal position accuracy too low\n"
  "uint16 CHECK_EPV     = 8    # Vertical position accuracy too low\n"
  "uint16 CHECK_SACC    = 16   # Speed accuracy too low\n"
  "uint16 CHECK_HDRIFT  = 32   # Horizontal position drift at rest too high\n"
  "uint16 CHECK_VDRIFT  = 64   # Vertical position drift at rest too high\n"
  "uint16 CHECK_HSPEED  = 128  # Horizontal speed at rest too high\n"
  "uint16 CHECK_VSPEED  = 256  # Vertical speed at rest too high\n"
  "uint16 CHECK_SPOOFED = 512  # Receiver reports spoofing\n"
  "uint16 CHECK_FIX     = 1024 # Fix type too low\n"
  "uint16 CHECK_JAMMED  = 2048 # Receiver reports jamming";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__VehicleGnss__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__VehicleGnss__TYPE_NAME, 24, 24},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 1729, 1729},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__VehicleGnss__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__VehicleGnss__get_individual_type_description_source(NULL),
    sources[1] = *px4_msgs__msg__SensorGnss__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
