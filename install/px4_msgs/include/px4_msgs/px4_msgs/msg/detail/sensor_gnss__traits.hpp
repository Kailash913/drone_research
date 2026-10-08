// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/SensorGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "px4_msgs/msg/detail/sensor_gnss__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace px4_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const SensorGnss & msg,
  std::ostream & out)
{
  out << "{";
  // member: timestamp
  {
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: timestamp_sample
  {
    out << "timestamp_sample: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp_sample, out);
    out << ", ";
  }

  // member: device_id
  {
    out << "device_id: ";
    rosidl_generator_traits::value_to_yaml(msg.device_id, out);
    out << ", ";
  }

  // member: latitude
  {
    out << "latitude: ";
    rosidl_generator_traits::value_to_yaml(msg.latitude, out);
    out << ", ";
  }

  // member: longitude
  {
    out << "longitude: ";
    rosidl_generator_traits::value_to_yaml(msg.longitude, out);
    out << ", ";
  }

  // member: altitude_msl
  {
    out << "altitude_msl: ";
    rosidl_generator_traits::value_to_yaml(msg.altitude_msl, out);
    out << ", ";
  }

  // member: altitude_ellipsoid
  {
    out << "altitude_ellipsoid: ";
    rosidl_generator_traits::value_to_yaml(msg.altitude_ellipsoid, out);
    out << ", ";
  }

  // member: speed_accuracy
  {
    out << "speed_accuracy: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_accuracy, out);
    out << ", ";
  }

  // member: course_accuracy
  {
    out << "course_accuracy: ";
    rosidl_generator_traits::value_to_yaml(msg.course_accuracy, out);
    out << ", ";
  }

  // member: fix_type
  {
    out << "fix_type: ";
    rosidl_generator_traits::value_to_yaml(msg.fix_type, out);
    out << ", ";
  }

  // member: eph
  {
    out << "eph: ";
    rosidl_generator_traits::value_to_yaml(msg.eph, out);
    out << ", ";
  }

  // member: epv
  {
    out << "epv: ";
    rosidl_generator_traits::value_to_yaml(msg.epv, out);
    out << ", ";
  }

  // member: hdop
  {
    out << "hdop: ";
    rosidl_generator_traits::value_to_yaml(msg.hdop, out);
    out << ", ";
  }

  // member: vdop
  {
    out << "vdop: ";
    rosidl_generator_traits::value_to_yaml(msg.vdop, out);
    out << ", ";
  }

  // member: noise
  {
    out << "noise: ";
    rosidl_generator_traits::value_to_yaml(msg.noise, out);
    out << ", ";
  }

  // member: automatic_gain_control
  {
    out << "automatic_gain_control: ";
    rosidl_generator_traits::value_to_yaml(msg.automatic_gain_control, out);
    out << ", ";
  }

  // member: jamming_state
  {
    out << "jamming_state: ";
    rosidl_generator_traits::value_to_yaml(msg.jamming_state, out);
    out << ", ";
  }

  // member: jamming_indicator
  {
    out << "jamming_indicator: ";
    rosidl_generator_traits::value_to_yaml(msg.jamming_indicator, out);
    out << ", ";
  }

  // member: spoofing_state
  {
    out << "spoofing_state: ";
    rosidl_generator_traits::value_to_yaml(msg.spoofing_state, out);
    out << ", ";
  }

  // member: authentication_state
  {
    out << "authentication_state: ";
    rosidl_generator_traits::value_to_yaml(msg.authentication_state, out);
    out << ", ";
  }

  // member: ground_speed
  {
    out << "ground_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.ground_speed, out);
    out << ", ";
  }

  // member: vel_north
  {
    out << "vel_north: ";
    rosidl_generator_traits::value_to_yaml(msg.vel_north, out);
    out << ", ";
  }

  // member: vel_east
  {
    out << "vel_east: ";
    rosidl_generator_traits::value_to_yaml(msg.vel_east, out);
    out << ", ";
  }

  // member: vel_down
  {
    out << "vel_down: ";
    rosidl_generator_traits::value_to_yaml(msg.vel_down, out);
    out << ", ";
  }

  // member: course
  {
    out << "course: ";
    rosidl_generator_traits::value_to_yaml(msg.course, out);
    out << ", ";
  }

  // member: vel_ned_valid
  {
    out << "vel_ned_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.vel_ned_valid, out);
    out << ", ";
  }

  // member: timestamp_time_relative
  {
    out << "timestamp_time_relative: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp_time_relative, out);
    out << ", ";
  }

  // member: time_utc_usec
  {
    out << "time_utc_usec: ";
    rosidl_generator_traits::value_to_yaml(msg.time_utc_usec, out);
    out << ", ";
  }

  // member: satellites_used
  {
    out << "satellites_used: ";
    rosidl_generator_traits::value_to_yaml(msg.satellites_used, out);
    out << ", ";
  }

  // member: system_error
  {
    out << "system_error: ";
    rosidl_generator_traits::value_to_yaml(msg.system_error, out);
    out << ", ";
  }

  // member: rtcm_injection_rate
  {
    out << "rtcm_injection_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.rtcm_injection_rate, out);
    out << ", ";
  }

  // member: selected_rtcm_instance
  {
    out << "selected_rtcm_instance: ";
    rosidl_generator_traits::value_to_yaml(msg.selected_rtcm_instance, out);
    out << ", ";
  }

  // member: corrections_protocol
  {
    out << "corrections_protocol: ";
    rosidl_generator_traits::value_to_yaml(msg.corrections_protocol, out);
    out << ", ";
  }

  // member: corrections_crc_failed
  {
    out << "corrections_crc_failed: ";
    rosidl_generator_traits::value_to_yaml(msg.corrections_crc_failed, out);
    out << ", ";
  }

  // member: corrections_msg_used
  {
    out << "corrections_msg_used: ";
    rosidl_generator_traits::value_to_yaml(msg.corrections_msg_used, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SensorGnss & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: timestamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << "\n";
  }

  // member: timestamp_sample
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp_sample: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp_sample, out);
    out << "\n";
  }

  // member: device_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "device_id: ";
    rosidl_generator_traits::value_to_yaml(msg.device_id, out);
    out << "\n";
  }

  // member: latitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "latitude: ";
    rosidl_generator_traits::value_to_yaml(msg.latitude, out);
    out << "\n";
  }

  // member: longitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "longitude: ";
    rosidl_generator_traits::value_to_yaml(msg.longitude, out);
    out << "\n";
  }

  // member: altitude_msl
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "altitude_msl: ";
    rosidl_generator_traits::value_to_yaml(msg.altitude_msl, out);
    out << "\n";
  }

  // member: altitude_ellipsoid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "altitude_ellipsoid: ";
    rosidl_generator_traits::value_to_yaml(msg.altitude_ellipsoid, out);
    out << "\n";
  }

  // member: speed_accuracy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed_accuracy: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_accuracy, out);
    out << "\n";
  }

  // member: course_accuracy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "course_accuracy: ";
    rosidl_generator_traits::value_to_yaml(msg.course_accuracy, out);
    out << "\n";
  }

  // member: fix_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fix_type: ";
    rosidl_generator_traits::value_to_yaml(msg.fix_type, out);
    out << "\n";
  }

  // member: eph
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eph: ";
    rosidl_generator_traits::value_to_yaml(msg.eph, out);
    out << "\n";
  }

  // member: epv
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "epv: ";
    rosidl_generator_traits::value_to_yaml(msg.epv, out);
    out << "\n";
  }

  // member: hdop
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hdop: ";
    rosidl_generator_traits::value_to_yaml(msg.hdop, out);
    out << "\n";
  }

  // member: vdop
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vdop: ";
    rosidl_generator_traits::value_to_yaml(msg.vdop, out);
    out << "\n";
  }

  // member: noise
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "noise: ";
    rosidl_generator_traits::value_to_yaml(msg.noise, out);
    out << "\n";
  }

  // member: automatic_gain_control
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "automatic_gain_control: ";
    rosidl_generator_traits::value_to_yaml(msg.automatic_gain_control, out);
    out << "\n";
  }

  // member: jamming_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "jamming_state: ";
    rosidl_generator_traits::value_to_yaml(msg.jamming_state, out);
    out << "\n";
  }

  // member: jamming_indicator
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "jamming_indicator: ";
    rosidl_generator_traits::value_to_yaml(msg.jamming_indicator, out);
    out << "\n";
  }

  // member: spoofing_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "spoofing_state: ";
    rosidl_generator_traits::value_to_yaml(msg.spoofing_state, out);
    out << "\n";
  }

  // member: authentication_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "authentication_state: ";
    rosidl_generator_traits::value_to_yaml(msg.authentication_state, out);
    out << "\n";
  }

  // member: ground_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ground_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.ground_speed, out);
    out << "\n";
  }

  // member: vel_north
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vel_north: ";
    rosidl_generator_traits::value_to_yaml(msg.vel_north, out);
    out << "\n";
  }

  // member: vel_east
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vel_east: ";
    rosidl_generator_traits::value_to_yaml(msg.vel_east, out);
    out << "\n";
  }

  // member: vel_down
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vel_down: ";
    rosidl_generator_traits::value_to_yaml(msg.vel_down, out);
    out << "\n";
  }

  // member: course
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "course: ";
    rosidl_generator_traits::value_to_yaml(msg.course, out);
    out << "\n";
  }

  // member: vel_ned_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vel_ned_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.vel_ned_valid, out);
    out << "\n";
  }

  // member: timestamp_time_relative
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp_time_relative: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp_time_relative, out);
    out << "\n";
  }

  // member: time_utc_usec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_utc_usec: ";
    rosidl_generator_traits::value_to_yaml(msg.time_utc_usec, out);
    out << "\n";
  }

  // member: satellites_used
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "satellites_used: ";
    rosidl_generator_traits::value_to_yaml(msg.satellites_used, out);
    out << "\n";
  }

  // member: system_error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "system_error: ";
    rosidl_generator_traits::value_to_yaml(msg.system_error, out);
    out << "\n";
  }

  // member: rtcm_injection_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rtcm_injection_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.rtcm_injection_rate, out);
    out << "\n";
  }

  // member: selected_rtcm_instance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "selected_rtcm_instance: ";
    rosidl_generator_traits::value_to_yaml(msg.selected_rtcm_instance, out);
    out << "\n";
  }

  // member: corrections_protocol
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "corrections_protocol: ";
    rosidl_generator_traits::value_to_yaml(msg.corrections_protocol, out);
    out << "\n";
  }

  // member: corrections_crc_failed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "corrections_crc_failed: ";
    rosidl_generator_traits::value_to_yaml(msg.corrections_crc_failed, out);
    out << "\n";
  }

  // member: corrections_msg_used
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "corrections_msg_used: ";
    rosidl_generator_traits::value_to_yaml(msg.corrections_msg_used, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SensorGnss & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace px4_msgs

namespace rosidl_generator_traits
{

[[deprecated("use px4_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const px4_msgs::msg::SensorGnss & msg,
  std::ostream & out, size_t indentation = 0)
{
  px4_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use px4_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const px4_msgs::msg::SensorGnss & msg)
{
  return px4_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<px4_msgs::msg::SensorGnss>()
{
  return "px4_msgs::msg::SensorGnss";
}

template<>
inline const char * name<px4_msgs::msg::SensorGnss>()
{
  return "px4_msgs/msg/SensorGnss";
}

template<>
struct has_fixed_size<px4_msgs::msg::SensorGnss>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<px4_msgs::msg::SensorGnss>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<px4_msgs::msg::SensorGnss>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__TRAITS_HPP_
