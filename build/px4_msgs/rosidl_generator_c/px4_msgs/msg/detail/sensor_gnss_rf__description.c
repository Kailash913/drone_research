// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/SensorGnssRf.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/sensor_gnss_rf__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__SensorGnssRf__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x9b, 0xfe, 0xcd, 0x06, 0xbc, 0xad, 0x23, 0x47,
      0x43, 0x22, 0x78, 0x77, 0xa8, 0xa0, 0x80, 0x3d,
      0x3e, 0xea, 0x10, 0x29, 0xce, 0x96, 0xeb, 0x24,
      0x5c, 0x01, 0xf0, 0xf2, 0xa8, 0xa2, 0x1e, 0x96,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__SensorGnssRf__TYPE_NAME[] = "px4_msgs/msg/SensorGnssRf";

// Define type names, field names, and default values
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__timestamp_sample[] = "timestamp_sample";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__device_id[] = "device_id";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__block_id[] = "block_id";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__antenna_status[] = "antenna_status";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__antenna_power[] = "antenna_power";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__post_status[] = "post_status";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__noise_per_ms[] = "noise_per_ms";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__automatic_gain_control[] = "automatic_gain_control";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__jamming_indicator[] = "jamming_indicator";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__jamming_state[] = "jamming_state";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__i_offset[] = "i_offset";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__i_magnitude[] = "i_magnitude";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__q_offset[] = "q_offset";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__q_magnitude[] = "q_magnitude";
static char px4_msgs__msg__SensorGnssRf__FIELD_NAME__center_frequency[] = "center_frequency";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__SensorGnssRf__FIELDS[] = {
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__timestamp_sample, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__device_id, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__block_id, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__antenna_status, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__antenna_power, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__post_status, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__noise_per_ms, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__automatic_gain_control, 22, 22},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__jamming_indicator, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__jamming_state, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__i_offset, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__i_magnitude, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__q_offset, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__q_magnitude, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnssRf__FIELD_NAME__center_frequency, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
px4_msgs__msg__SensorGnssRf__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__SensorGnssRf__TYPE_NAME, 25, 25},
      {px4_msgs__msg__SensorGnssRf__FIELDS, 16, 16},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# GNSS RF status\n"
  "#\n"
  "# Reports RF block status for a GNSS receiver, decoded from the u-blox UBX-MON-RF message.\n"
  "# Includes antenna status/power, jamming/interference indicators, automatic gain control (AGC),\n"
  "# noise level, and I/Q demodulation metrics. Published by the `gps` driver (UBX protocol only), once\n"
  "# per RF block, via the block-specific topics below.\n"
  "\n"
  "uint64 timestamp # [us] Time since system start\n"
  "uint64 timestamp_sample # [us] Timestamp of the raw data\n"
  "\n"
  "uint32 device_id # Unique device ID for the sensor that does not change between power cycles\n"
  "\n"
  "uint8 block_id  # [-] Only used for multi-topic publishing\n"
  "\n"
  "uint8 antenna_status # [@enum ANTENNA_STATUS] Status of the antenna supervisor state machine\n"
  "uint8 ANTENNA_STATUS_INIT = 0 # Initializing\n"
  "uint8 ANTENNA_STATUS_UNKNOWN = 1 # Status unknown\n"
  "uint8 ANTENNA_STATUS_OK = 2 # Antenna OK\n"
  "uint8 ANTENNA_STATUS_SHORT = 3 # Short circuit detected\n"
  "uint8 ANTENNA_STATUS_OPEN = 4 # Open circuit detected\n"
  "\n"
  "uint8 antenna_power # [@enum ANTENNA_POWER] Antenna power state\n"
  "uint8 ANTENNA_POWER_OFF = 0 # Power off\n"
  "uint8 ANTENNA_POWER_ON = 1 # Power on\n"
  "uint8 ANTENNA_POWER_UNKNOWN = 2 # Power state unknown\n"
  "\n"
  "uint32 post_status # [-] Power-on self-test (POST) status word (vendor-specific bitmask)\n"
  "\n"
  "uint16 noise_per_ms # [-] Noise level as measured by the GNSS receiver core\n"
  "uint16 automatic_gain_control # [-] [@range 0, 8191] Automatic Gain Control (AGC) monitor value (8191 = 100% of max gain)\n"
  "uint8 jamming_indicator # [-] [@range 0, 255] Continuous wave (CW) jamming indicator (0 = no CW jamming, 255 = strong CW jamming)\n"
  "\n"
  "uint8 jamming_state # [@enum JAMMING_STATE] Jamming state\n"
  "uint8 JAMMING_STATE_UNKNOWN = 0 # Unknown\n"
  "uint8 JAMMING_STATE_OK = 1 # No jamming detected\n"
  "uint8 JAMMING_STATE_WARNING = 2 # Interference visible but fix OK\n"
  "uint8 JAMMING_STATE_CRITICAL = 3 # Interference visible and no fix\n"
  "\n"
  "int8 i_offset # [-] [@range -128, 127] Imbalance of the I-part of the complex signal (0 = no imbalance)\n"
  "uint8 i_magnitude # [-] [@range 0, 255] Magnitude of the I-part of the complex signal (0 = no signal, 255 = max magnitude)\n"
  "int8 q_offset # [-] [@range -128, 127] Imbalance of the Q-part of the complex signal (0 = no imbalance)\n"
  "uint8 q_magnitude # [-] [@range 0, 255] Magnitude of the Q-part of the complex signal (0 = no signal, 255 = max magnitude)\n"
  "\n"
  "uint32 center_frequency # [Hz] Nominal center frequency of the RF block. 0 = unknown.\n"
  "\n"
  "# One topic per RF block ID\n"
  "# TOPICS sensor_gnss_rf_block0 sensor_gnss_rf_block1 sensor_gnss_rf_block2";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__SensorGnssRf__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__SensorGnssRf__TYPE_NAME, 25, 25},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 2505, 2505},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__SensorGnssRf__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__SensorGnssRf__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
