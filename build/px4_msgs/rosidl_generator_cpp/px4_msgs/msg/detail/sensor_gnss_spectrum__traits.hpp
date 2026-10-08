// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/SensorGnssSpectrum.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss_spectrum.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "px4_msgs/msg/detail/sensor_gnss_spectrum__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace px4_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const SensorGnssSpectrum & msg,
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

  // member: spectrum
  {
    if (msg.spectrum.size() == 0) {
      out << "spectrum: []";
    } else {
      out << "spectrum: [";
      size_t pending_items = msg.spectrum.size();
      for (auto item : msg.spectrum) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: spectrum_span
  {
    out << "spectrum_span: ";
    rosidl_generator_traits::value_to_yaml(msg.spectrum_span, out);
    out << ", ";
  }

  // member: resolution
  {
    out << "resolution: ";
    rosidl_generator_traits::value_to_yaml(msg.resolution, out);
    out << ", ";
  }

  // member: center_frequency
  {
    out << "center_frequency: ";
    rosidl_generator_traits::value_to_yaml(msg.center_frequency, out);
    out << ", ";
  }

  // member: programmable_gain_amplifier
  {
    out << "programmable_gain_amplifier: ";
    rosidl_generator_traits::value_to_yaml(msg.programmable_gain_amplifier, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SensorGnssSpectrum & msg,
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

  // member: spectrum
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.spectrum.size() == 0) {
      out << "spectrum: []\n";
    } else {
      out << "spectrum:\n";
      for (auto item : msg.spectrum) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: spectrum_span
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "spectrum_span: ";
    rosidl_generator_traits::value_to_yaml(msg.spectrum_span, out);
    out << "\n";
  }

  // member: resolution
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "resolution: ";
    rosidl_generator_traits::value_to_yaml(msg.resolution, out);
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

  // member: programmable_gain_amplifier
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "programmable_gain_amplifier: ";
    rosidl_generator_traits::value_to_yaml(msg.programmable_gain_amplifier, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SensorGnssSpectrum & msg, bool use_flow_style = false)
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
  const px4_msgs::msg::SensorGnssSpectrum & msg,
  std::ostream & out, size_t indentation = 0)
{
  px4_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use px4_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const px4_msgs::msg::SensorGnssSpectrum & msg)
{
  return px4_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<px4_msgs::msg::SensorGnssSpectrum>()
{
  return "px4_msgs::msg::SensorGnssSpectrum";
}

template<>
inline const char * name<px4_msgs::msg::SensorGnssSpectrum>()
{
  return "px4_msgs/msg/SensorGnssSpectrum";
}

template<>
struct has_fixed_size<px4_msgs::msg::SensorGnssSpectrum>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<px4_msgs::msg::SensorGnssSpectrum>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<px4_msgs::msg::SensorGnssSpectrum>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__TRAITS_HPP_
