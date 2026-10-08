// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/SensorUwb.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_uwb.h"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_UWB__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SENSOR_UWB__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/SensorUwb in the package px4_msgs.
/**
  * Ultra-wideband (UWB) distance sensor
  *
  * Distance and angle-of-arrival ranging data from an ultra-wideband (UWB) positioning
  * system, such as Pozyx or NXP Rddrone. Published and consumed internally by the UWB
  * ranging driver (src/drivers/uwb/uwb_sr150), which parses serial ranging results from
  * the sensor module and publishes them on this topic; no other module in the codebase
  * currently subscribes to it.
 */
typedef struct px4_msgs__msg__SensorUwb
{
  /// Time since system start
  uint64_t timestamp;
  /// UWB SessionID
  uint32_t sessionid;
  /// Time between Ranging Rounds in ms
  uint32_t time_offset;
  /// Number of Ranges since last Start of Ranging
  uint32_t counter;
  /// MAC address of Initiator (controller)
  uint16_t mac;
  /// MAC address of Responder (Controlee)
  uint16_t mac_dest;
  /// Ranging status code passed through from the UWB module's measurement result
  uint16_t status;
  /// Non-line-of-sight condition (y/n)
  uint8_t nlos;
  /// Distance to the UWB receiver
  float distance;
  /// Angle of arrival, Angle in Degree -60..+60; FOV in both axis is 120 degrees
  ///  [deg] Angle of arrival of first incoming RX msg
  float aoa_azimuth_dev;
  /// Angle of arrival of first incoming RX msg
  float aoa_elevation_dev;
  /// Angle of arrival of first incoming RX msg at the responder
  float aoa_azimuth_resp;
  /// Angle of arrival of first incoming RX msg at the responder
  float aoa_elevation_resp;
  /// Figure of merit for the angle measurements
  /// AOA Azimuth Figure of Merit (FOM)
  uint8_t aoa_azimuth_fom;
  /// AOA Elevation FOM
  uint8_t aoa_elevation_fom;
  /// AOA Azimuth FOM
  uint8_t aoa_dest_azimuth_fom;
  /// AOA Elevation FOM
  uint8_t aoa_dest_elevation_fom;
  /// Initiator physical configuration
  /// Direction the sensor faces from MAV_SENSOR_ORIENTATION enum. Standard configuration has antennas facing down and azimuth aligned in the forward direction.
  uint8_t orientation;
  /// UWB initiator offset in X axis (NED drone frame)
  float offset_x;
  /// UWB initiator offset in Y axis (NED drone frame)
  float offset_y;
  /// UWB initiator offset in Z axis (NED drone frame)
  float offset_z;
} px4_msgs__msg__SensorUwb;

// Struct for a sequence of px4_msgs__msg__SensorUwb.
typedef struct px4_msgs__msg__SensorUwb__Sequence
{
  px4_msgs__msg__SensorUwb * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__SensorUwb__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_UWB__STRUCT_H_
