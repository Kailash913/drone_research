// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/SensorGnssRf.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss_rf.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "px4_msgs/msg/detail/sensor_gnss_rf__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace px4_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const SensorGnssRf & msg,
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

  // member: block_id
  {
    out << "block_id: ";
    rosidl_generator_traits::value_to_yaml(msg.block_id, out);
    out << ", ";
  }

  // member: antenna_status
  {
    out << "antenna_status: ";
    rosidl_generator_traits::value_to_yaml(msg.antenna_status, out);
    out << ", ";
  }

  // member: antenna_power
  {
    out << "antenna_power: ";
    rosidl_generator_traits::value_to_yaml(msg.antenna_power, out);
    out << ", ";
  }

  // member: post_status
  {
    out << "post_status: ";
    rosidl_generator_traits::value_to_yaml(msg.post_status, out);
    out << ", ";
  }

  // member: noise_per_ms
  {
    out << "noise_per_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.noise_per_ms, out);
    out << ", ";
  }

  // member: automatic_gain_control
  {
    out << "automatic_gain_control: ";
    rosidl_generator_traits::value_to_yaml(msg.automatic_gain_control, out);
    out << ", ";
  }

  // member: jamming_indicator
  {
    out << "jamming_indicator: ";
    rosidl_generator_traits::value_to_yaml(msg.jamming_indicator, out);
    out << ", ";
  }

  // member: jamming_state
  {
    out << "jamming_state: ";
    rosidl_generator_traits::value_to_yaml(msg.jamming_state, out);
    out << ", ";
  }

  // member: i_offset
  {
    out << "i_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.i_offset, out);
    out << ", ";
  }

  // member: i_magnitude
  {
    out << "i_magnitude: ";
    rosidl_generator_traits::value_to_yaml(msg.i_magnitude, out);
    out << ", ";
  }

  // member: q_offset
  {
    out << "q_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.q_offset, out);
    out << ", ";
  }

  // member: q_magnitude
  {
    out << "q_magnitude: ";
    rosidl_generator_traits::value_to_yaml(msg.q_magnitude, out);
    out << ", ";
  }

  // member: center_frequency
  {
    out << "center_frequency: ";
    rosidl_generator_traits::value_to_yaml(msg.center_frequency, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SensorGnssRf & msg,
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

  // member: block_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "block_id: ";
    rosidl_generator_traits::value_to_yaml(msg.block_id, out);
    out << "\n";
  }

  // member: antenna_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "antenna_status: ";
    rosidl_generator_traits::value_to_yaml(msg.antenna_status, out);
    out << "\n";
  }

  // member: antenna_power
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "antenna_power: ";
    rosidl_generator_traits::value_to_yaml(msg.antenna_power, out);
    out << "\n";
  }

  // member: post_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "post_status: ";
    rosidl_generator_traits::value_to_yaml(msg.post_status, out);
    out << "\n";
  }

  // member: noise_per_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "noise_per_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.noise_per_ms, out);
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

  // member: jamming_indicator
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "jamming_indicator: ";
    rosidl_generator_traits::value_to_yaml(msg.jamming_indicator, out);
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

  // member: i_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "i_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.i_offset, out);
    out << "\n";
  }

  // member: i_magnitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "i_magnitude: ";
    rosidl_generator_traits::value_to_yaml(msg.i_magnitude, out);
    out << "\n";
  }

  // member: q_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "q_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.q_offset, out);
    out << "\n";
  }

  // member: q_magnitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "q_magnitude: ";
    rosidl_generator_traits::value_to_yaml(msg.q_magnitude, out);
    out << "\n";
  }

  // member: center_frequency
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "center_frequency: ";
    rosidl_generator_traits::value_to_yaml(msg.center_frequency, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SensorGnssRf & msg, bool use_flow_style = false)
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
  const px4_msgs::msg::SensorGnssRf & msg,
  std::ostream & out, size_t indentation = 0)
{
  px4_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use px4_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const px4_msgs::msg::SensorGnssRf & msg)
{
  return px4_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<px4_msgs::msg::SensorGnssRf>()
{
  return "px4_msgs::msg::SensorGnssRf";
}

template<>
inline const char * name<px4_msgs::msg::SensorGnssRf>()
{
  return "px4_msgs/msg/SensorGnssRf";
}

template<>
struct has_fixed_size<px4_msgs::msg::SensorGnssRf>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<px4_msgs::msg::SensorGnssRf>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<px4_msgs::msg::SensorGnssRf>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__TRAITS_HPP_
