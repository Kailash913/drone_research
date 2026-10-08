// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/PrecTakeoffStatus.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/prec_takeoff_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__PrecTakeoffStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x8d, 0xb0, 0x83, 0x95, 0x3e, 0x68, 0x9f, 0x01,
      0x90, 0x5e, 0x93, 0x70, 0x6b, 0x8c, 0x5c, 0xd7,
      0xc3, 0xfb, 0xe6, 0x72, 0xd1, 0xcd, 0x43, 0xd9,
      0xd9, 0x63, 0xb7, 0xde, 0x9f, 0x99, 0xaa, 0xa3,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__PrecTakeoffStatus__TYPE_NAME[] = "px4_msgs/msg/PrecTakeoffStatus";

// Define type names, field names, and default values
static char px4_msgs__msg__PrecTakeoffStatus__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__PrecTakeoffStatus__FIELD_NAME__state[] = "state";
static char px4_msgs__msg__PrecTakeoffStatus__FIELD_NAME__setpoint_adjusted[] = "setpoint_adjusted";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__PrecTakeoffStatus__FIELDS[] = {
  {
    {px4_msgs__msg__PrecTakeoffStatus__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__PrecTakeoffStatus__FIELD_NAME__state, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__PrecTakeoffStatus__FIELD_NAME__setpoint_adjusted, 17, 17},
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
px4_msgs__msg__PrecTakeoffStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__PrecTakeoffStatus__TYPE_NAME, 30, 30},
      {px4_msgs__msg__PrecTakeoffStatus__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Precision takeoff status.\n"
  "#\n"
  "# Published by: navigator (prec_takeoff.cpp).\n"
  "# Subscribed by: vision_target_estimator, flight_mode_manager (FlightTaskAuto).\n"
  "#\n"
  "# ONGOING while a vertical takeoff setpoint is active and MIS_TKO_PREC is set. DONE is published when the\n"
  "# takeoff altitude is reached, then STOPPED once the takeoff is no longer active. Published every Navigator cycle.\n"
  "\n"
  "uint64 timestamp # [us] Time since system start\n"
  "\n"
  "uint8 state # [@enum PREC_TAKEOFF_STATE] Current precision-takeoff state\n"
  "bool setpoint_adjusted # True after a valid target adjusted the horizontal setpoint\n"
  "uint8 PREC_TAKEOFF_STATE_STOPPED = 0 # Not active\n"
  "uint8 PREC_TAKEOFF_STATE_ONGOING = 1 # Takeoff active; the estimator may still be acquiring the target\n"
  "uint8 PREC_TAKEOFF_STATE_DONE = 2 # Takeoff altitude reached";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__PrecTakeoffStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__PrecTakeoffStatus__TYPE_NAME, 30, 30},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 800, 800},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__PrecTakeoffStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__PrecTakeoffStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
