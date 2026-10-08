// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from px4_msgs:msg/InternalCombustionEngineControl.idl
// generated code does not contain a copyright notice

#include "px4_msgs/msg/detail/internal_combustion_engine_control__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_px4_msgs
const rosidl_type_hash_t *
px4_msgs__msg__InternalCombustionEngineControl__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xe7, 0xb7, 0x06, 0xc9, 0x58, 0xc0, 0xc9, 0x5b,
      0x60, 0x96, 0x87, 0x4b, 0xfb, 0x74, 0x81, 0x74,
      0x6f, 0xe3, 0xcf, 0x94, 0xf9, 0xb7, 0xc5, 0x80,
      0x88, 0x77, 0x77, 0x5d, 0x7d, 0xe5, 0xd1, 0xbf,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char px4_msgs__msg__InternalCombustionEngineControl__TYPE_NAME[] = "px4_msgs/msg/InternalCombustionEngineControl";

// Define type names, field names, and default values
static char px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__timestamp[] = "timestamp";
static char px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__ignition_on[] = "ignition_on";
static char px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__throttle_control[] = "throttle_control";
static char px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__choke_control[] = "choke_control";
static char px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__starter_engine_control[] = "starter_engine_control";
static char px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__user_request_motor_on[] = "user_request_motor_on";

static rosidl_runtime_c__type_description__Field px4_msgs__msg__InternalCombustionEngineControl__FIELDS[] = {
  {
    {px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__ignition_on, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__throttle_control, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__choke_control, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__starter_engine_control, 22, 22},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {px4_msgs__msg__InternalCombustionEngineControl__FIELD_NAME__user_request_motor_on, 21, 21},
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
px4_msgs__msg__InternalCombustionEngineControl__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {px4_msgs__msg__InternalCombustionEngineControl__TYPE_NAME, 44, 44},
      {px4_msgs__msg__InternalCombustionEngineControl__FIELDS, 6, 6},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Internal combustion engine (ICE) actuator setpoints\n"
  "#\n"
  "# Published by the `internal_combustion_engine_control` module, which runs the engine\n"
  "# start/stop state machine and the idle RPM governor.\n"
  "# The mixer maps these setpoints onto the IC Engine output functions (ignition,\n"
  "# throttle, choke, starter), which are assigned to the flight controller outputs.\n"
  "# The resulting state machine state is reported in `InternalCombustionEngineStatus`.\n"
  "\n"
  "uint64 timestamp # [us] Time since system start\n"
  "\n"
  "bool ignition_on # Activate/deactivate the ignition (spark plug)\n"
  "float32 throttle_control # [norm] [@range 0, 1] [@invalid NaN Stops the engine: output goes to its disarmed value] Throttle actuator setpoint, rate limited by `ICE_THR_SLEW`. 0 is closed throttle\n"
  "float32 choke_control # [norm] [@range 0, 1] Choke actuator setpoint, 1 is fully closed\n"
  "float32 starter_engine_control # [norm] [@range 0, 1] (Electric) starter motor setpoint\n"
  "\n"
  "bool user_request_motor_on # User intent for the engine to be running, from the source selected by `ICE_ON_SOURCE`";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
px4_msgs__msg__InternalCombustionEngineControl__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {px4_msgs__msg__InternalCombustionEngineControl__TYPE_NAME, 44, 44},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 1046, 1046},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
px4_msgs__msg__InternalCombustionEngineControl__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *px4_msgs__msg__InternalCombustionEngineControl__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
