// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/SensorsStatusGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensors_status_gnss.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "px4_msgs/msg/detail/sensors_status_gnss__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace px4_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const SensorsStatusGnss & msg,
  std::ostream & out)
{
  out << "{";
  // member: timestamp
  {
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: device_id_selected
  {
    out << "device_id_selected: ";
    rosidl_generator_traits::value_to_yaml(msg.device_id_selected, out);
    out << ", ";
  }

  // member: device_ids
  {
    if (msg.device_ids.size() == 0) {
      out << "device_ids: []";
    } else {
      out << "device_ids: [";
      size_t pending_items = msg.device_ids.size();
      for (auto item : msg.device_ids) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: order
  {
    if (msg.order.size() == 0) {
      out << "order: []";
    } else {
      out << "order: [";
      size_t pending_items = msg.order.size();
      for (auto item : msg.order) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: healthy
  {
    if (msg.healthy.size() == 0) {
      out << "healthy: []";
    } else {
      out << "healthy: [";
      size_t pending_items = msg.healthy.size();
      for (auto item : msg.healthy) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: failed_checks
  {
    if (msg.failed_checks.size() == 0) {
      out << "failed_checks: []";
    } else {
      out << "failed_checks: [";
      size_t pending_items = msg.failed_checks.size();
      for (auto item : msg.failed_checks) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: strict
  {
    if (msg.strict.size() == 0) {
      out << "strict: []";
    } else {
      out << "strict: [";
      size_t pending_items = msg.strict.size();
      for (auto item : msg.strict) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: drift_rate_horizontal
  {
    if (msg.drift_rate_horizontal.size() == 0) {
      out << "drift_rate_horizontal: []";
    } else {
      out << "drift_rate_horizontal: [";
      size_t pending_items = msg.drift_rate_horizontal.size();
      for (auto item : msg.drift_rate_horizontal) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: drift_rate_vertical
  {
    if (msg.drift_rate_vertical.size() == 0) {
      out << "drift_rate_vertical: []";
    } else {
      out << "drift_rate_vertical: [";
      size_t pending_items = msg.drift_rate_vertical.size();
      for (auto item : msg.drift_rate_vertical) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: speed_horizontal_filtered
  {
    if (msg.speed_horizontal_filtered.size() == 0) {
      out << "speed_horizontal_filtered: []";
    } else {
      out << "speed_horizontal_filtered: [";
      size_t pending_items = msg.speed_horizontal_filtered.size();
      for (auto item : msg.speed_horizontal_filtered) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SensorsStatusGnss & msg,
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

  // member: device_id_selected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "device_id_selected: ";
    rosidl_generator_traits::value_to_yaml(msg.device_id_selected, out);
    out << "\n";
  }

  // member: device_ids
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.device_ids.size() == 0) {
      out << "device_ids: []\n";
    } else {
      out << "device_ids:\n";
      for (auto item : msg.device_ids) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: order
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.order.size() == 0) {
      out << "order: []\n";
    } else {
      out << "order:\n";
      for (auto item : msg.order) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: healthy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.healthy.size() == 0) {
      out << "healthy: []\n";
    } else {
      out << "healthy:\n";
      for (auto item : msg.healthy) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: failed_checks
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.failed_checks.size() == 0) {
      out << "failed_checks: []\n";
    } else {
      out << "failed_checks:\n";
      for (auto item : msg.failed_checks) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: strict
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.strict.size() == 0) {
      out << "strict: []\n";
    } else {
      out << "strict:\n";
      for (auto item : msg.strict) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: drift_rate_horizontal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.drift_rate_horizontal.size() == 0) {
      out << "drift_rate_horizontal: []\n";
    } else {
      out << "drift_rate_horizontal:\n";
      for (auto item : msg.drift_rate_horizontal) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: drift_rate_vertical
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.drift_rate_vertical.size() == 0) {
      out << "drift_rate_vertical: []\n";
    } else {
      out << "drift_rate_vertical:\n";
      for (auto item : msg.drift_rate_vertical) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: speed_horizontal_filtered
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.speed_horizontal_filtered.size() == 0) {
      out << "speed_horizontal_filtered: []\n";
    } else {
      out << "speed_horizontal_filtered:\n";
      for (auto item : msg.speed_horizontal_filtered) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SensorsStatusGnss & msg, bool use_flow_style = false)
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
  const px4_msgs::msg::SensorsStatusGnss & msg,
  std::ostream & out, size_t indentation = 0)
{
  px4_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use px4_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const px4_msgs::msg::SensorsStatusGnss & msg)
{
  return px4_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<px4_msgs::msg::SensorsStatusGnss>()
{
  return "px4_msgs::msg::SensorsStatusGnss";
}

template<>
inline const char * name<px4_msgs::msg::SensorsStatusGnss>()
{
  return "px4_msgs/msg/SensorsStatusGnss";
}

template<>
struct has_fixed_size<px4_msgs::msg::SensorsStatusGnss>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<px4_msgs::msg::SensorsStatusGnss>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<px4_msgs::msg::SensorsStatusGnss>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__TRAITS_HPP_
