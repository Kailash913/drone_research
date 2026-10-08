// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/SensorGnssSpectrum.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/sensor_gnss_spectrum__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__SensorGnssSpectrum__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x7c, 0x03, 0xe8, 0x5b, 0x65, 0x06, 0x61, 0xcc,
      0x58, 0xae, 0x85, 0xbf, 0xae, 0x5c, 0x6c, 0x4e,
      0xc5, 0x53, 0x3d, 0x09, 0x03, 0x6b, 0x78, 0x98,
      0xa9, 0x38, 0x75, 0xaa, 0xbf, 0x83, 0x70, 0x72,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__SensorGnssSpectrum__TYPE_NAME[] = "px4_msgs/msg/SensorGnssSpectrum";

// Define type names, field names, and default values
static char px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__timestamp_sample[] = "timestamp_sample";
static char px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__device_id[] = "device_id";
static char px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__block_id[] = "block_id";
static char px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__spectrum[] = "spectrum";
static char px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__spectrum_span[] = "spectrum_span";
static char px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__resolution[] = "resolution";
static char px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__center_frequency[] = "center_frequency";
static char px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__programmable_gain_amplifier[] = "programmable_gain_amplifier";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__SensorGnssSpectrum__FIELDS[] = {
  {
    {px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__timestamp_sample, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__device_id, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__block_id, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__spectrum, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8_ARRAY,
      256,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__spectrum_span, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__resolution, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__center_frequency, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssSpectrum__FIELD_NAME__programmable_gain_amplifier, 27, 27},
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
px4_msgs__msg__SensorGnssSpectrum__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__SensorGnssSpectrum__TYPE_NAME, 31, 31},
      {px4_msgs__msg__SensorGnssSpectrum__FIELDS, 9, 9},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# GNSS spectrum analysis\n"
  "#\n"
  "# Reports a basic RF spectrum analysis for a GNSS receiver, decoded from the u-blox UBX-MON-SPAN message.\n"
  "# Published by the `gps` driver (UBX protocol only), once per RF block, via the block-specific topics below.\n"
  "# The center frequency of bin i is: f(i) = center_frequency + spectrum_span * (i - 127) / 256\n"
  "\n"
  "uint64 timestamp # [us] Time since system start\n"
  "uint64 timestamp_sample # [us] Timestamp of the raw data\n"
  "\n"
  "uint32 device_id # Unique device ID for the sensor that does not change between power cycles\n"
  "\n"
  "uint8 block_id # [-] Only used for multi-topic publishing. Use center_frequency to determine which RF band it is.\n"
  "\n"
  "uint8[256] spectrum # [(2^-2)dB] Spectrum magnitude per bin (number of points = spectrum_span / resolution)\n"
  "uint32 spectrum_span # [Hz] Frequency span covered by the spectrum\n"
  "uint32 resolution # [Hz] Frequency resolution of the spectrum (bin width)\n"
  "uint32 center_frequency # [Hz] Center frequency of the spectrum span\n"
  "uint8 programmable_gain_amplifier # [dB] Programmable gain amplifier setting\n"
  "\n"
  "# One topic per RF block ID\n"
  "# TOPICS sensor_gnss_spectrum_block0 sensor_gnss_spectrum_block1 sensor_gnss_spectrum_block2";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__SensorGnssSpectrum__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__SensorGnssSpectrum__TYPE_NAME, 31, 31},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 1169, 1169},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__SensorGnssSpectrum__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__SensorGnssSpectrum__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
