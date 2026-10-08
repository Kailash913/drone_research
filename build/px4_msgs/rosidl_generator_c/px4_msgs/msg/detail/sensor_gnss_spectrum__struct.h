// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/SensorGnssSpectrum.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss_spectrum.h"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/SensorGnssSpectrum in the package px4_msgs.
/**
  * GNSS spectrum analysis
  *
  * Reports a basic RF spectrum analysis for a GNSS receiver, decoded from the u-blox UBX-MON-SPAN message.
  * Published by the `gps` driver (UBX protocol only), once per RF block, via the block-specific topics below.
  * The center frequency of bin i is: f(i) = center_frequency + spectrum_span * (i - 127) / 256
 */
typedef struct px4_msgs__msg__SensorGnssSpectrum
{
  /// Time since system start
  uint64_t timestamp;
  /// Timestamp of the raw data
  uint64_t timestamp_sample;
  /// Unique device ID for the sensor that does not change between power cycles
  uint32_t device_id;
  /// Only used for multi-topic publishing. Use center_frequency to determine which RF band it is.
  uint8_t block_id;
  /// Spectrum magnitude per bin (number of points = spectrum_span / resolution)
  uint8_t spectrum[256];
  /// Frequency span covered by the spectrum
  uint32_t spectrum_span;
  /// Frequency resolution of the spectrum (bin width)
  uint32_t resolution;
  /// Center frequency of the spectrum span
  uint32_t center_frequency;
  /// Programmable gain amplifier setting
  uint8_t programmable_gain_amplifier;
} px4_msgs__msg__SensorGnssSpectrum;

// Struct for a sequence of px4_msgs__msg__SensorGnssSpectrum.
typedef struct px4_msgs__msg__SensorGnssSpectrum__Sequence
{
  px4_msgs__msg__SensorGnssSpectrum * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__SensorGnssSpectrum__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__STRUCT_H_
