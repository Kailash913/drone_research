// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/SensorGnss.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/sensor_gnss__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__SensorGnss__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x67, 0x02, 0xf9, 0xcb, 0x39, 0xf2, 0x0c, 0xbb,
      0x5c, 0xc7, 0x13, 0x0d, 0x1a, 0x07, 0x3b, 0xf7,
      0x97, 0xad, 0xf2, 0xe5, 0x18, 0x14, 0x4b, 0xc9,
      0x68, 0x8a, 0x35, 0xe7, 0x1a, 0x78, 0xa6, 0x8e,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__SensorGnss__TYPE_NAME[] = "px4_msgs/msg/SensorGnss";

// Define type names, field names, and default values
static char px4_msgs__msg__SensorGnss__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__timestamp_sample[] = "timestamp_sample";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__device_id[] = "device_id";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__latitude[] = "latitude";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__longitude[] = "longitude";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__altitude_msl[] = "altitude_msl";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__altitude_ellipsoid[] = "altitude_ellipsoid";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__speed_accuracy[] = "speed_accuracy";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__course_accuracy[] = "course_accuracy";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__fix_type[] = "fix_type";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__eph[] = "eph";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__epv[] = "epv";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__hdop[] = "hdop";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__vdop[] = "vdop";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__noise[] = "noise";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__automatic_gain_control[] = "automatic_gain_control";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__jamming_state[] = "jamming_state";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__jamming_indicator[] = "jamming_indicator";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__spoofing_state[] = "spoofing_state";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__authentication_state[] = "authentication_state";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__ground_speed[] = "ground_speed";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__vel_north[] = "vel_north";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__vel_east[] = "vel_east";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__vel_down[] = "vel_down";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__course[] = "course";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__vel_ned_valid[] = "vel_ned_valid";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__timestamp_time_relative[] = "timestamp_time_relative";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__time_utc_usec[] = "time_utc_usec";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__satellites_used[] = "satellites_used";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__system_error[] = "system_error";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__rtcm_injection_rate[] = "rtcm_injection_rate";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__selected_rtcm_instance[] = "selected_rtcm_instance";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__corrections_protocol[] = "corrections_protocol";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__corrections_crc_failed[] = "corrections_crc_failed";
static char px4_msgs__msg__SensorGnss__FIELD_NAME__corrections_msg_used[] = "corrections_msg_used";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__SensorGnss__FIELDS[] = {
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__timestamp_sample, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__device_id, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__latitude, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__longitude, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__altitude_msl, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__altitude_ellipsoid, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__speed_accuracy, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__course_accuracy, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__fix_type, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__eph, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__epv, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__hdop, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__vdop, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__noise, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__automatic_gain_control, 22, 22},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__jamming_state, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__jamming_indicator, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__spoofing_state, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__authentication_state, 20, 20},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__ground_speed, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__vel_north, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__vel_east, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__vel_down, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__course, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__vel_ned_valid, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__timestamp_time_relative, 23, 23},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__time_utc_usec, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__satellites_used, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__system_error, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__rtcm_injection_rate, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__selected_rtcm_instance, 22, 22},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__corrections_protocol, 20, 20},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__corrections_crc_failed, 22, 22},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorGnss__FIELD_NAME__corrections_msg_used, 20, 20},
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
px4_msgs__msg__SensorGnss__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__SensorGnss__TYPE_NAME, 23, 23},
      {px4_msgs__msg__SensorGnss__FIELDS, 35, 35},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# GNSS receiver report, position in WGS84\n"
  "#\n"
  "# One instance per receiver, published by its driver: the receiver's own solution, unmodified.\n"
  "# The sensors module publishes the selected receiver on vehicle_gnss.\n"
  "\n"
  "uint64 timestamp        # [us] Time since system start\n"
  "uint64 timestamp_sample # [us] Measurement time if the driver knows it, else 0 or equal to timestamp. vehicle_gnss carries the corrected value\n"
  "\n"
  "uint32 device_id # [-] Unique device ID for the sensor that does not change between power cycles\n"
  "\n"
  "float64 latitude           # [deg] Latitude, allows centimeter level RTK precision\n"
  "float64 longitude          # [deg] Longitude, allows centimeter level RTK precision\n"
  "float64 altitude_msl       # [m] Altitude above MSL, from the receiver's own geoid model\n"
  "float64 altitude_ellipsoid # [m] Altitude above the WGS84 ellipsoid\n"
  "\n"
  "float32 speed_accuracy  # [m/s] Speed accuracy estimate\n"
  "float32 course_accuracy # [rad] Course accuracy estimate\n"
  "\n"
  "uint8 fix_type                             # [@enum FIX_TYPE] Value 0 is also valid to represent no fix\n"
  "uint8 FIX_TYPE_NONE                   = 1\n"
  "uint8 FIX_TYPE_2D                     = 2\n"
  "uint8 FIX_TYPE_3D                     = 3\n"
  "uint8 FIX_TYPE_RTCM_CODE_DIFFERENTIAL = 4\n"
  "uint8 FIX_TYPE_RTK_FLOAT              = 5\n"
  "uint8 FIX_TYPE_RTK_FIXED              = 6\n"
  "uint8 FIX_TYPE_EXTRAPOLATED           = 8\n"
  "\n"
  "float32 eph  # [m] Horizontal position accuracy\n"
  "float32 epv  # [m] Vertical position accuracy\n"
  "float32 hdop # [-] Horizontal dilution of precision\n"
  "float32 vdop # [-] Vertical dilution of precision\n"
  "\n"
  "int32 noise                   # [-] Noise level per millisecond\n"
  "uint16 automatic_gain_control # [-] Automatic gain control monitor\n"
  "\n"
  "uint8 jamming_state           # [@enum JAMMING_STATE]\n"
  "uint8 JAMMING_STATE_UNKNOWN   = 0\n"
  "uint8 JAMMING_STATE_OK        = 1\n"
  "uint8 JAMMING_STATE_MITIGATED = 2\n"
  "uint8 JAMMING_STATE_DETECTED  = 3\n"
  "int32 jamming_indicator       # [-] Jamming indicator\n"
  "\n"
  "uint8 spoofing_state           # [@enum SPOOFING_STATE]\n"
  "uint8 SPOOFING_STATE_UNKNOWN   = 0\n"
  "uint8 SPOOFING_STATE_OK        = 1\n"
  "uint8 SPOOFING_STATE_MITIGATED = 2\n"
  "uint8 SPOOFING_STATE_DETECTED  = 3\n"
  "\n"
  "uint8 authentication_state              # [@enum AUTHENTICATION_STATE] Combined signal authentication state (e.g. Galileo OSNMA)\n"
  "uint8 AUTHENTICATION_STATE_UNKNOWN      = 0\n"
  "uint8 AUTHENTICATION_STATE_INITIALIZING = 1\n"
  "uint8 AUTHENTICATION_STATE_ERROR        = 2\n"
  "uint8 AUTHENTICATION_STATE_OK           = 3\n"
  "uint8 AUTHENTICATION_STATE_DISABLED     = 4\n"
  "\n"
  "float32 ground_speed # [m/s] Ground speed\n"
  "float32 vel_north    # [m/s] North velocity\n"
  "float32 vel_east     # [m/s] East velocity\n"
  "float32 vel_down     # [m/s] Down velocity\n"
  "float32 course       # [rad] [@range -PI, PI] Course over ground, not heading\n"
  "bool vel_ned_valid   # NED velocity is valid\n"
  "\n"
  "int32 timestamp_time_relative # [us] timestamp + timestamp_time_relative = time of the UTC timestamp since system start\n"
  "uint64 time_utc_usec          # [us] UTC time from the receiver, 0 until known\n"
  "\n"
  "uint8 satellites_used # [-] Satellites used in the solution\n"
  "\n"
  "uint32 system_error                      # [@enum SYSTEM_ERROR] Bitmask of receiver errors\n"
  "uint32 SYSTEM_ERROR_OK                   = 0\n"
  "uint32 SYSTEM_ERROR_INCOMING_CORRECTIONS = 1\n"
  "uint32 SYSTEM_ERROR_CONFIGURATION        = 2\n"
  "uint32 SYSTEM_ERROR_SOFTWARE             = 4\n"
  "uint32 SYSTEM_ERROR_ANTENNA              = 8\n"
  "uint32 SYSTEM_ERROR_EVENT_CONGESTION     = 16\n"
  "uint32 SYSTEM_ERROR_CPU_OVERLOAD         = 32\n"
  "uint32 SYSTEM_ERROR_OUTPUT_CONGESTION    = 64\n"
  "\n"
  "float32 rtcm_injection_rate  # [Hz] Correction injection rate\n"
  "uint8 selected_rtcm_instance # [-] uORB instance used for corrections\n"
  "\n"
  "uint8 corrections_protocol         # [@enum CORRECTIONS_PROTOCOL] Protocol of the last correction message the receiver parsed\n"
  "uint8 CORRECTIONS_PROTOCOL_UNKNOWN = 0\n"
  "uint8 CORRECTIONS_PROTOCOL_RTCM3   = 1\n"
  "uint8 CORRECTIONS_PROTOCOL_SPARTN  = 2\n"
  "uint8 CORRECTIONS_PROTOCOL_HAS     = 3 # Galileo High Accuracy Service, received on E6\n"
  "uint8 CORRECTIONS_PROTOCOL_PMP     = 4 # SPARTN over L-band (u-blox NEO-D9S)\n"
  "uint8 CORRECTIONS_PROTOCOL_QZSS_L6 = 5 # QZSS CLAS\n"
  "bool corrections_crc_failed        # Last correction message failed its CRC or content check\n"
  "\n"
  "uint8 corrections_msg_used          # [@enum CORRECTIONS_MSG_USED] Whether the receiver used the last correction message\n"
  "uint8 CORRECTIONS_MSG_USED_UNKNOWN  = 0\n"
  "uint8 CORRECTIONS_MSG_USED_NOT_USED = 1\n"
  "uint8 CORRECTIONS_MSG_USED_USED     = 2\n"
  "\n"
  "# TOPICS sensor_gnss";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__SensorGnss__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__SensorGnss__TYPE_NAME, 23, 23},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 4426, 4426},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__SensorGnss__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__SensorGnss__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
