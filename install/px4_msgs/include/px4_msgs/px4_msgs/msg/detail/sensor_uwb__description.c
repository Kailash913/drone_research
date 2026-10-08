// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/SensorUwb.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/sensor_uwb__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__SensorUwb__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x78, 0xbe, 0xd4, 0xf1, 0x2b, 0xef, 0x99, 0x60,
      0x62, 0xf7, 0x44, 0xca, 0xbe, 0x11, 0x7a, 0x4b,
      0xb9, 0x85, 0xbb, 0x40, 0x33, 0xc3, 0xcc, 0xa4,
      0x89, 0x38, 0x03, 0x7f, 0xb1, 0x00, 0xcb, 0xf5,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__SensorUwb__TYPE_NAME[] = "px4_msgs/msg/SensorUwb";

// Define type names, field names, and default values
static char px4_msgs__msg__SensorUwb__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__sessionid[] = "sessionid";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__time_offset[] = "time_offset";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__counter[] = "counter";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__mac[] = "mac";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__mac_dest[] = "mac_dest";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__status[] = "status";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__nlos[] = "nlos";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__distance[] = "distance";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_azimuth_dev[] = "aoa_azimuth_dev";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_elevation_dev[] = "aoa_elevation_dev";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_azimuth_resp[] = "aoa_azimuth_resp";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_elevation_resp[] = "aoa_elevation_resp";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_azimuth_fom[] = "aoa_azimuth_fom";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_elevation_fom[] = "aoa_elevation_fom";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_dest_azimuth_fom[] = "aoa_dest_azimuth_fom";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_dest_elevation_fom[] = "aoa_dest_elevation_fom";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__orientation[] = "orientation";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__offset_x[] = "offset_x";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__offset_y[] = "offset_y";
static char px4_msgs__msg__SensorUwb__FIELD_NAME__offset_z[] = "offset_z";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__SensorUwb__FIELDS[] = {
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__sessionid, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__time_offset, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__counter, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__mac, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__mac_dest, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__status, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__nlos, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__distance, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_azimuth_dev, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_elevation_dev, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_azimuth_resp, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_elevation_resp, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_azimuth_fom, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_elevation_fom, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_dest_azimuth_fom, 20, 20},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__aoa_dest_elevation_fom, 22, 22},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__orientation, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__offset_x, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__offset_y, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__SensorUwb__FIELD_NAME__offset_z, 8, 8},
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
px4_msgs__msg__SensorUwb__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__SensorUwb__TYPE_NAME, 22, 22},
      {px4_msgs__msg__SensorUwb__FIELDS, 21, 21},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Ultra-wideband (UWB) distance sensor\n"
  "#\n"
  "# Distance and angle-of-arrival ranging data from an ultra-wideband (UWB) positioning\n"
  "# system, such as Pozyx or NXP Rddrone. Published and consumed internally by the UWB\n"
  "# ranging driver (src/drivers/uwb/uwb_sr150), which parses serial ranging results from\n"
  "# the sensor module and publishes them on this topic; no other module in the codebase\n"
  "# currently subscribes to it.\n"
  "\n"
  "uint64 timestamp # [us] Time since system start\n"
  "\n"
  "uint32 sessionid # UWB SessionID\n"
  "uint32 time_offset # Time between Ranging Rounds in ms\n"
  "uint32 counter # Number of Ranges since last Start of Ranging\n"
  "uint16 mac # [-] MAC address of Initiator (controller)\n"
  "\n"
  "uint16 mac_dest # [-] MAC address of Responder (Controlee)\n"
  "uint16 status # [-] Ranging status code passed through from the UWB module's measurement result\n"
  "uint8 nlos # [-] Non-line-of-sight condition (y/n)\n"
  "float32 distance # [m] Distance to the UWB receiver\n"
  "\n"
  "#Angle of arrival, Angle in Degree -60..+60; FOV in both axis is 120 degrees\n"
  "float32 aoa_azimuth_dev # [deg] Angle of arrival of first incoming RX msg\n"
  "float32 aoa_elevation_dev # [deg] Angle of arrival of first incoming RX msg\n"
  "float32 aoa_azimuth_resp # [deg] Angle of arrival of first incoming RX msg at the responder\n"
  "float32 aoa_elevation_resp # [deg] Angle of arrival of first incoming RX msg at the responder\n"
  "\n"
  "# Figure of merit for the angle measurements\n"
  "uint8 aoa_azimuth_fom # AOA Azimuth Figure of Merit (FOM)\n"
  "uint8 aoa_elevation_fom # AOA Elevation FOM\n"
  "uint8 aoa_dest_azimuth_fom # AOA Azimuth FOM\n"
  "uint8 aoa_dest_elevation_fom # AOA Elevation FOM\n"
  "\n"
  "# Initiator physical configuration\n"
  "uint8 orientation # Direction the sensor faces from MAV_SENSOR_ORIENTATION enum. Standard configuration has antennas facing down and azimuth aligned in the forward direction.\n"
  "float32 offset_x # UWB initiator offset in X axis (NED drone frame)\n"
  "float32 offset_y # UWB initiator offset in Y axis (NED drone frame)\n"
  "float32 offset_z # UWB initiator offset in Z axis (NED drone frame)";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__SensorUwb__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__SensorUwb__TYPE_NAME, 22, 22},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 2000, 2000},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__SensorUwb__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__SensorUwb__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
