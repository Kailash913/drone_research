// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/VehicleGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/vehicle_gnss.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "px4_msgs/msg/detail/vehicle_gnss__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'receiver'
#include "px4_msgs/msg/detail/sensor_gnss__traits.hpp"

namespace px4_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const VehicleGnss & msg,
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

  // member: receiver
  {
    out << "receiver: ";
    to_flow_style_yaml(msg.receiver, out);
    out << ", ";
  }

  // member: antenna_offset
  {
    if (msg.antenna_offset.size() == 0) {
      out << "antenna_offset: []";
    } else {
      out << "antenna_offset: [";
      size_t pending_items = msg.antenna_offset.size();
      for (auto item : msg.antenna_offset) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: selected_instance
  {
    out << "selected_instance: ";
    rosidl_generator_traits::value_to_yaml(msg.selected_instance, out);
    out << ", ";
  }

  // member: selection_count
  {
    out << "selection_count: ";
    rosidl_generator_traits::value_to_yaml(msg.selection_count, out);
    out << ", ";
  }

  // member: usable
  {
    out << "usable: ";
    rosidl_generator_traits::value_to_yaml(msg.usable, out);
    out << ", ";
  }

  // member: failed_checks
  {
    out << "failed_checks: ";
    rosidl_generator_traits::value_to_yaml(msg.failed_checks, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VehicleGnss & msg,
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

  // member: receiver
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "receiver:\n";
    to_block_style_yaml(msg.receiver, out, indentation + 2);
  }

  // member: antenna_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.antenna_offset.size() == 0) {
      out << "antenna_offset: []\n";
    } else {
      out << "antenna_offset:\n";
      for (auto item : msg.antenna_offset) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: selected_instance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "selected_instance: ";
    rosidl_generator_traits::value_to_yaml(msg.selected_instance, out);
    out << "\n";
  }

  // member: selection_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "selection_count: ";
    rosidl_generator_traits::value_to_yaml(msg.selection_count, out);
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

  // member: failed_checks
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "failed_checks: ";
    rosidl_generator_traits::value_to_yaml(msg.failed_checks, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VehicleGnss & msg, bool use_flow_style = false)
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
  const px4_msgs::msg::VehicleGnss & msg,
  std::ostream & out, size_t indentation = 0)
{
  px4_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use px4_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const px4_msgs::msg::VehicleGnss & msg)
{
  return px4_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<px4_msgs::msg::VehicleGnss>()
{
  return "px4_msgs::msg::VehicleGnss";
}

template<>
inline const char * name<px4_msgs::msg::VehicleGnss>()
{
  return "px4_msgs/msg/VehicleGnss";
}

template<>
struct has_fixed_size<px4_msgs::msg::VehicleGnss>
  : std::integral_constant<bool, has_fixed_size<px4_msgs::msg::SensorGnss>::value> {};

template<>
struct has_bounded_size<px4_msgs::msg::VehicleGnss>
  : std::integral_constant<bool, has_bounded_size<px4_msgs::msg::SensorGnss>::value> {};

template<>
struct is_message<px4_msgs::msg::VehicleGnss>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__TRAITS_HPP_
