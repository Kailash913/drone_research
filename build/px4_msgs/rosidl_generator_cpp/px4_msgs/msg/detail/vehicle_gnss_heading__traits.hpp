// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/VehicleGnssHeading.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/vehicle_gnss_heading.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS_HEADING__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS_HEADING__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "px4_msgs/msg/detail/vehicle_gnss_heading__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace px4_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const VehicleGnssHeading & msg,
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

  // member: heading
  {
    out << "heading: ";
    rosidl_generator_traits::value_to_yaml(msg.heading, out);
    out << ", ";
  }

  // member: heading_accuracy
  {
    out << "heading_accuracy: ";
    rosidl_generator_traits::value_to_yaml(msg.heading_accuracy, out);
    out << ", ";
  }

  // member: heading_offset
  {
    out << "heading_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.heading_offset, out);
    out << ", ";
  }

  // member: baseline_length
  {
    out << "baseline_length: ";
    rosidl_generator_traits::value_to_yaml(msg.baseline_length, out);
    out << ", ";
  }

  // member: jamming_state
  {
    out << "jamming_state: ";
    rosidl_generator_traits::value_to_yaml(msg.jamming_state, out);
    out << ", ";
  }

  // member: spoofing_state
  {
    out << "spoofing_state: ";
    rosidl_generator_traits::value_to_yaml(msg.spoofing_state, out);
    out << ", ";
  }

  // member: usable
  {
    out << "usable: ";
    rosidl_generator_traits::value_to_yaml(msg.usable, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VehicleGnssHeading & msg,
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

  // member: heading
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "heading: ";
    rosidl_generator_traits::value_to_yaml(msg.heading, out);
    out << "\n";
  }

  // member: heading_accuracy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "heading_accuracy: ";
    rosidl_generator_traits::value_to_yaml(msg.heading_accuracy, out);
    out << "\n";
  }

  // member: heading_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "heading_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.heading_offset, out);
    out << "\n";
  }

  // member: baseline_length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "baseline_length: ";
    rosidl_generator_traits::value_to_yaml(msg.baseline_length, out);
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

  // member: spoofing_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "spoofing_state: ";
    rosidl_generator_traits::value_to_yaml(msg.spoofing_state, out);
    out << "\n";
  }

  // member: usable
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "usable: ";
    rosidl_generator_traits::value_to_yaml(msg.usable, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VehicleGnssHeading & msg, bool use_flow_style = false)
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
  const px4_msgs::msg::VehicleGnssHeading & msg,
  std::ostream & out, size_t indentation = 0)
{
  px4_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use px4_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const px4_msgs::msg::VehicleGnssHeading & msg)
{
  return px4_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<px4_msgs::msg::VehicleGnssHeading>()
{
  return "px4_msgs::msg::VehicleGnssHeading";
}

template<>
inline const char * name<px4_msgs::msg::VehicleGnssHeading>()
{
  return "px4_msgs/msg/VehicleGnssHeading";
}

template<>
struct has_fixed_size<px4_msgs::msg::VehicleGnssHeading>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<px4_msgs::msg::VehicleGnssHeading>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<px4_msgs::msg::VehicleGnssHeading>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS_HEADING__TRAITS_HPP_
