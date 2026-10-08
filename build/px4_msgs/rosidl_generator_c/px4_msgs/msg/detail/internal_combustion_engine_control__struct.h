// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/InternalCombustionEngineControl.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/internal_combustion_engine_control.h"


#ifndef PX4_MSGS__MSG__DETAIL__INTERNAL_COMBUSTION_ENGINE_CONTROL__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__INTERNAL_COMBUSTION_ENGINE_CONTROL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/InternalCombustionEngineControl in the package px4_msgs.
/**
  * Internal combustion engine (ICE) actuator setpoints
  *
  * Published by the `internal_combustion_engine_control` module, which runs the engine
  * start/stop state machine and the idle RPM governor.
  * The mixer maps these setpoints onto the IC Engine output functions (ignition,
  * throttle, choke, starter), which are assigned to the flight controller outputs.
  * The resulting state machine state is reported in `InternalCombustionEngineStatus`.
 */
typedef struct px4_msgs__msg__InternalCombustionEngineControl
{
  /// Time since system start
  uint64_t timestamp;
  /// Activate/deactivate the ignition (spark plug)
  bool ignition_on;
  /// [norm] [@range 0, 1] [@invalid NaN Stops the engine: output goes to its disarmed value] Throttle actuator setpoint, rate limited by `ICE_THR_SLEW`. 0 is closed throttle
  float throttle_control;
  /// [@range 0, 1] Choke actuator setpoint, 1 is fully closed
  float choke_control;
  /// [@range 0, 1] (Electric) starter motor setpoint
  float starter_engine_control;
  /// User intent for the engine to be running, from the source selected by `ICE_ON_SOURCE`
  bool user_request_motor_on;
} px4_msgs__msg__InternalCombustionEngineControl;

// Struct for a sequence of px4_msgs__msg__InternalCombustionEngineControl.
typedef struct px4_msgs__msg__InternalCombustionEngineControl__Sequence
{
  px4_msgs__msg__InternalCombustionEngineControl * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__InternalCombustionEngineControl__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__INTERNAL_COMBUSTION_ENGINE_CONTROL__STRUCT_H_
