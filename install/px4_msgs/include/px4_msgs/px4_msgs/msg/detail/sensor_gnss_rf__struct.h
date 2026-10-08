// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/SensorGnssRf.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss_rf.h"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'ANTENNA_STATUS_INIT'.
/**
  * Initializing
 */
enum
{
  px4_msgs__msg__SensorGnssRf__ANTENNA_STATUS_INIT = 0
};

/// Constant 'ANTENNA_STATUS_UNKNOWN'.
/**
  * Status unknown
 */
enum
{
  px4_msgs__msg__SensorGnssRf__ANTENNA_STATUS_UNKNOWN = 1
};

/// Constant 'ANTENNA_STATUS_OK'.
/**
  * Antenna OK
 */
enum
{
  px4_msgs__msg__SensorGnssRf__ANTENNA_STATUS_OK = 2
};

/// Constant 'ANTENNA_STATUS_SHORT'.
/**
  * Short circuit detected
 */
enum
{
  px4_msgs__msg__SensorGnssRf__ANTENNA_STATUS_SHORT = 3
};

/// Constant 'ANTENNA_STATUS_OPEN'.
/**
  * Open circuit detected
 */
enum
{
  px4_msgs__msg__SensorGnssRf__ANTENNA_STATUS_OPEN = 4
};

/// Constant 'ANTENNA_POWER_OFF'.
/**
  * Power off
 */
enum
{
  px4_msgs__msg__SensorGnssRf__ANTENNA_POWER_OFF = 0
};

/// Constant 'ANTENNA_POWER_ON'.
/**
  * Power on
 */
enum
{
  px4_msgs__msg__SensorGnssRf__ANTENNA_POWER_ON = 1
};

/// Constant 'ANTENNA_POWER_UNKNOWN'.
/**
  * Power state unknown
 */
enum
{
  px4_msgs__msg__SensorGnssRf__ANTENNA_POWER_UNKNOWN = 2
};

/// Constant 'JAMMING_STATE_UNKNOWN'.
/**
  * Unknown
 */
enum
{
  px4_msgs__msg__SensorGnssRf__JAMMING_STATE_UNKNOWN = 0
};

/// Constant 'JAMMING_STATE_OK'.
/**
  * No jamming detected
 */
enum
{
  px4_msgs__msg__SensorGnssRf__JAMMING_STATE_OK = 1
};

/// Constant 'JAMMING_STATE_WARNING'.
/**
  * Interference visible but fix OK
 */
enum
{
  px4_msgs__msg__SensorGnssRf__JAMMING_STATE_WARNING = 2
};

/// Constant 'JAMMING_STATE_CRITICAL'.
/**
  * Interference visible and no fix
 */
enum
{
  px4_msgs__msg__SensorGnssRf__JAMMING_STATE_CRITICAL = 3
};

/// Struct defined in msg/SensorGnssRf in the package px4_msgs.
/**
  * GNSS RF status
  *
  * Reports RF block status for a GNSS receiver, decoded from the u-blox UBX-MON-RF message.
  * Includes antenna status/power, jamming/interference indicators, automatic gain control (AGC),
  * noise level, and I/Q demodulation metrics. Published by the `gps` driver (UBX protocol only), once
  * per RF block, via the block-specific topics below.
 */
typedef struct px4_msgs__msg__SensorGnssRf
{
  /// Time since system start
  uint64_t timestamp;
  /// Timestamp of the raw data
  uint64_t timestamp_sample;
  /// Unique device ID for the sensor that does not change between power cycles
  uint32_t device_id;
  /// Only used for multi-topic publishing
  uint8_t block_id;
  /// Status of the antenna supervisor state machine
  uint8_t antenna_status;
  /// Antenna power state
  uint8_t antenna_power;
  /// Power-on self-test (POST) status word (vendor-specific bitmask)
  uint32_t post_status;
  /// Noise level as measured by the GNSS receiver core
  uint16_t noise_per_ms;
  /// [@range 0, 8191] Automatic Gain Control (AGC) monitor value (8191 = 100% of max gain)
  uint16_t automatic_gain_control;
  /// [@range 0, 255] Continuous wave (CW) jamming indicator (0 = no CW jamming, 255 = strong CW jamming)
  uint8_t jamming_indicator;
  /// Jamming state
  uint8_t jamming_state;
  /// [@range -128, 127] Imbalance of the I-part of the complex signal (0 = no imbalance)
  int8_t i_offset;
  /// [@range 0, 255] Magnitude of the I-part of the complex signal (0 = no signal, 255 = max magnitude)
  uint8_t i_magnitude;
  /// [@range -128, 127] Imbalance of the Q-part of the complex signal (0 = no imbalance)
  int8_t q_offset;
  /// [@range 0, 255] Magnitude of the Q-part of the complex signal (0 = no signal, 255 = max magnitude)
  uint8_t q_magnitude;
  /// Nominal center frequency of the RF block. 0 = unknown.
  uint32_t center_frequency;
} px4_msgs__msg__SensorGnssRf;

// Struct for a sequence of px4_msgs__msg__SensorGnssRf.
typedef struct px4_msgs__msg__SensorGnssRf__Sequence
{
  px4_msgs__msg__SensorGnssRf * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__SensorGnssRf__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__STRUCT_H_
