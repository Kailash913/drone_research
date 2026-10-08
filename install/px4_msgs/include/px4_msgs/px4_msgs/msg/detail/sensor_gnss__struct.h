// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/SensorGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss.h"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'FIX_TYPE_NONE'.
enum
{
  px4_msgs__msg__SensorGnss__FIX_TYPE_NONE = 1
};

/// Constant 'FIX_TYPE_2D'.
enum
{
  px4_msgs__msg__SensorGnss__FIX_TYPE_2D = 2
};

/// Constant 'FIX_TYPE_3D'.
enum
{
  px4_msgs__msg__SensorGnss__FIX_TYPE_3D = 3
};

/// Constant 'FIX_TYPE_RTCM_CODE_DIFFERENTIAL'.
enum
{
  px4_msgs__msg__SensorGnss__FIX_TYPE_RTCM_CODE_DIFFERENTIAL = 4
};

/// Constant 'FIX_TYPE_RTK_FLOAT'.
enum
{
  px4_msgs__msg__SensorGnss__FIX_TYPE_RTK_FLOAT = 5
};

/// Constant 'FIX_TYPE_RTK_FIXED'.
enum
{
  px4_msgs__msg__SensorGnss__FIX_TYPE_RTK_FIXED = 6
};

/// Constant 'FIX_TYPE_EXTRAPOLATED'.
enum
{
  px4_msgs__msg__SensorGnss__FIX_TYPE_EXTRAPOLATED = 8
};

/// Constant 'JAMMING_STATE_UNKNOWN'.
enum
{
  px4_msgs__msg__SensorGnss__JAMMING_STATE_UNKNOWN = 0
};

/// Constant 'JAMMING_STATE_OK'.
enum
{
  px4_msgs__msg__SensorGnss__JAMMING_STATE_OK = 1
};

/// Constant 'JAMMING_STATE_MITIGATED'.
enum
{
  px4_msgs__msg__SensorGnss__JAMMING_STATE_MITIGATED = 2
};

/// Constant 'JAMMING_STATE_DETECTED'.
enum
{
  px4_msgs__msg__SensorGnss__JAMMING_STATE_DETECTED = 3
};

/// Constant 'SPOOFING_STATE_UNKNOWN'.
enum
{
  px4_msgs__msg__SensorGnss__SPOOFING_STATE_UNKNOWN = 0
};

/// Constant 'SPOOFING_STATE_OK'.
enum
{
  px4_msgs__msg__SensorGnss__SPOOFING_STATE_OK = 1
};

/// Constant 'SPOOFING_STATE_MITIGATED'.
enum
{
  px4_msgs__msg__SensorGnss__SPOOFING_STATE_MITIGATED = 2
};

/// Constant 'SPOOFING_STATE_DETECTED'.
enum
{
  px4_msgs__msg__SensorGnss__SPOOFING_STATE_DETECTED = 3
};

/// Constant 'AUTHENTICATION_STATE_UNKNOWN'.
enum
{
  px4_msgs__msg__SensorGnss__AUTHENTICATION_STATE_UNKNOWN = 0
};

/// Constant 'AUTHENTICATION_STATE_INITIALIZING'.
enum
{
  px4_msgs__msg__SensorGnss__AUTHENTICATION_STATE_INITIALIZING = 1
};

/// Constant 'AUTHENTICATION_STATE_ERROR'.
enum
{
  px4_msgs__msg__SensorGnss__AUTHENTICATION_STATE_ERROR = 2
};

/// Constant 'AUTHENTICATION_STATE_OK'.
enum
{
  px4_msgs__msg__SensorGnss__AUTHENTICATION_STATE_OK = 3
};

/// Constant 'AUTHENTICATION_STATE_DISABLED'.
enum
{
  px4_msgs__msg__SensorGnss__AUTHENTICATION_STATE_DISABLED = 4
};

/// Constant 'SYSTEM_ERROR_OK'.
enum
{
  px4_msgs__msg__SensorGnss__SYSTEM_ERROR_OK = 0ul
};

/// Constant 'SYSTEM_ERROR_INCOMING_CORRECTIONS'.
enum
{
  px4_msgs__msg__SensorGnss__SYSTEM_ERROR_INCOMING_CORRECTIONS = 1ul
};

/// Constant 'SYSTEM_ERROR_CONFIGURATION'.
enum
{
  px4_msgs__msg__SensorGnss__SYSTEM_ERROR_CONFIGURATION = 2ul
};

/// Constant 'SYSTEM_ERROR_SOFTWARE'.
enum
{
  px4_msgs__msg__SensorGnss__SYSTEM_ERROR_SOFTWARE = 4ul
};

/// Constant 'SYSTEM_ERROR_ANTENNA'.
enum
{
  px4_msgs__msg__SensorGnss__SYSTEM_ERROR_ANTENNA = 8ul
};

/// Constant 'SYSTEM_ERROR_EVENT_CONGESTION'.
enum
{
  px4_msgs__msg__SensorGnss__SYSTEM_ERROR_EVENT_CONGESTION = 16ul
};

/// Constant 'SYSTEM_ERROR_CPU_OVERLOAD'.
enum
{
  px4_msgs__msg__SensorGnss__SYSTEM_ERROR_CPU_OVERLOAD = 32ul
};

/// Constant 'SYSTEM_ERROR_OUTPUT_CONGESTION'.
enum
{
  px4_msgs__msg__SensorGnss__SYSTEM_ERROR_OUTPUT_CONGESTION = 64ul
};

/// Constant 'CORRECTIONS_PROTOCOL_UNKNOWN'.
enum
{
  px4_msgs__msg__SensorGnss__CORRECTIONS_PROTOCOL_UNKNOWN = 0
};

/// Constant 'CORRECTIONS_PROTOCOL_RTCM3'.
enum
{
  px4_msgs__msg__SensorGnss__CORRECTIONS_PROTOCOL_RTCM3 = 1
};

/// Constant 'CORRECTIONS_PROTOCOL_SPARTN'.
enum
{
  px4_msgs__msg__SensorGnss__CORRECTIONS_PROTOCOL_SPARTN = 2
};

/// Constant 'CORRECTIONS_PROTOCOL_HAS'.
/**
  * Galileo High Accuracy Service, received on E6
 */
enum
{
  px4_msgs__msg__SensorGnss__CORRECTIONS_PROTOCOL_HAS = 3
};

/// Constant 'CORRECTIONS_PROTOCOL_PMP'.
/**
  * SPARTN over L-band (u-blox NEO-D9S)
 */
enum
{
  px4_msgs__msg__SensorGnss__CORRECTIONS_PROTOCOL_PMP = 4
};

/// Constant 'CORRECTIONS_PROTOCOL_QZSS_L6'.
/**
  * QZSS CLAS
 */
enum
{
  px4_msgs__msg__SensorGnss__CORRECTIONS_PROTOCOL_QZSS_L6 = 5
};

/// Constant 'CORRECTIONS_MSG_USED_UNKNOWN'.
enum
{
  px4_msgs__msg__SensorGnss__CORRECTIONS_MSG_USED_UNKNOWN = 0
};

/// Constant 'CORRECTIONS_MSG_USED_NOT_USED'.
enum
{
  px4_msgs__msg__SensorGnss__CORRECTIONS_MSG_USED_NOT_USED = 1
};

/// Constant 'CORRECTIONS_MSG_USED_USED'.
enum
{
  px4_msgs__msg__SensorGnss__CORRECTIONS_MSG_USED_USED = 2
};

/// Struct defined in msg/SensorGnss in the package px4_msgs.
/**
  * GNSS receiver report, position in WGS84
  *
  * One instance per receiver, published by its driver: the receiver's own solution, unmodified.
  * The sensors module publishes the selected receiver on vehicle_gnss.
 */
typedef struct px4_msgs__msg__SensorGnss
{
  /// Time since system start
  uint64_t timestamp;
  /// Measurement time if the driver knows it, else 0 or equal to timestamp. vehicle_gnss carries the corrected value
  uint64_t timestamp_sample;
  /// Unique device ID for the sensor that does not change between power cycles
  uint32_t device_id;
  /// Latitude, allows centimeter level RTK precision
  double latitude;
  /// Longitude, allows centimeter level RTK precision
  double longitude;
  /// Altitude above MSL, from the receiver's own geoid model
  double altitude_msl;
  /// Altitude above the WGS84 ellipsoid
  double altitude_ellipsoid;
  /// Speed accuracy estimate
  float speed_accuracy;
  /// Course accuracy estimate
  float course_accuracy;
  /// Value 0 is also valid to represent no fix
  uint8_t fix_type;
  /// Horizontal position accuracy
  float eph;
  /// Vertical position accuracy
  float epv;
  /// Horizontal dilution of precision
  float hdop;
  /// Vertical dilution of precision
  float vdop;
  /// Noise level per millisecond
  int32_t noise;
  /// Automatic gain control monitor
  uint16_t automatic_gain_control;
  uint8_t jamming_state;
  /// Jamming indicator
  int32_t jamming_indicator;
  uint8_t spoofing_state;
  /// Combined signal authentication state (e.g. Galileo OSNMA)
  uint8_t authentication_state;
  /// Ground speed
  float ground_speed;
  /// North velocity
  float vel_north;
  /// East velocity
  float vel_east;
  /// Down velocity
  float vel_down;
  /// [@range -PI, PI] Course over ground, not heading
  float course;
  /// NED velocity is valid
  bool vel_ned_valid;
  /// timestamp + timestamp_time_relative = time of the UTC timestamp since system start
  int32_t timestamp_time_relative;
  /// UTC time from the receiver, 0 until known
  uint64_t time_utc_usec;
  /// Satellites used in the solution
  uint8_t satellites_used;
  /// Bitmask of receiver errors
  uint32_t system_error;
  /// Correction injection rate
  float rtcm_injection_rate;
  /// uORB instance used for corrections
  uint8_t selected_rtcm_instance;
  /// Protocol of the last correction message the receiver parsed
  uint8_t corrections_protocol;
  /// Last correction message failed its CRC or content check
  bool corrections_crc_failed;
  /// Whether the receiver used the last correction message
  uint8_t corrections_msg_used;
} px4_msgs__msg__SensorGnss;

// Struct for a sequence of px4_msgs__msg__SensorGnss.
typedef struct px4_msgs__msg__SensorGnss__Sequence
{
  px4_msgs__msg__SensorGnss * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__SensorGnss__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__STRUCT_H_
