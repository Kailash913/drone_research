// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/PrecTakeoffStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/prec_takeoff_status.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "px4_msgs/msg/detail/prec_takeoff_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace px4_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PrecTakeoffStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: timestamp
  {
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: setpoint_adjusted
  {
    out << "setpoint_adjusted: ";
    rosidl_generator_traits::value_to_yaml(msg.setpoint_adjusted, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PrecTakeoffStatus & msg,
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

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }

  // member: setpoint_adjusted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "setpoint_adjusted: ";
    rosidl_generator_traits::value_to_yaml(msg.setpoint_adjusted, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PrecTakeoffStatus & msg, bool use_flow_style = false)
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
  const px4_msgs::msg::PrecTakeoffStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  px4_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use px4_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const px4_msgs::msg::PrecTakeoffStatus & msg)
{
  return px4_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<px4_msgs::msg::PrecTakeoffStatus>()
{
  return "px4_msgs::msg::PrecTakeoffStatus";
}

template<>
inline const char * name<px4_msgs::msg::PrecTakeoffStatus>()
{
  return "px4_msgs/msg/PrecTakeoffStatus";
}

template<>
struct has_fixed_size<px4_msgs::msg::PrecTakeoffStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<px4_msgs::msg::PrecTakeoffStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<px4_msgs::msg::PrecTakeoffStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__TRAITS_HPP_
