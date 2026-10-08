// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/SensorsStatusGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensors_status_gnss.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/sensors_status_gnss__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_SensorsStatusGnss_speed_horizontal_filtered
{
public:
  explicit Init_SensorsStatusGnss_speed_horizontal_filtered(::px4_msgs::msg::SensorsStatusGnss & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::SensorsStatusGnss speed_horizontal_filtered(::px4_msgs::msg::SensorsStatusGnss::_speed_horizontal_filtered_type arg)
  {
    msg_.speed_horizontal_filtered = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::SensorsStatusGnss msg_;
};

class Init_SensorsStatusGnss_drift_rate_vertical
{
public:
  explicit Init_SensorsStatusGnss_drift_rate_vertical(::px4_msgs::msg::SensorsStatusGnss & msg)
  : msg_(msg)
  {}
  Init_SensorsStatusGnss_speed_horizontal_filtered drift_rate_vertical(::px4_msgs::msg::SensorsStatusGnss::_drift_rate_vertical_type arg)
  {
    msg_.drift_rate_vertical = std::move(arg);
    return Init_SensorsStatusGnss_speed_horizontal_filtered(msg_);
  }

private:
  ::px4_msgs::msg::SensorsStatusGnss msg_;
};

class Init_SensorsStatusGnss_drift_rate_horizontal
{
public:
  explicit Init_SensorsStatusGnss_drift_rate_horizontal(::px4_msgs::msg::SensorsStatusGnss & msg)
  : msg_(msg)
  {}
  Init_SensorsStatusGnss_drift_rate_vertical drift_rate_horizontal(::px4_msgs::msg::SensorsStatusGnss::_drift_rate_horizontal_type arg)
  {
    msg_.drift_rate_horizontal = std::move(arg);
    return Init_SensorsStatusGnss_drift_rate_vertical(msg_);
  }

private:
  ::px4_msgs::msg::SensorsStatusGnss msg_;
};

class Init_SensorsStatusGnss_strict
{
public:
  explicit Init_SensorsStatusGnss_strict(::px4_msgs::msg::SensorsStatusGnss & msg)
  : msg_(msg)
  {}
  Init_SensorsStatusGnss_drift_rate_horizontal strict(::px4_msgs::msg::SensorsStatusGnss::_strict_type arg)
  {
    msg_.strict = std::move(arg);
    return Init_SensorsStatusGnss_drift_rate_horizontal(msg_);
  }

private:
  ::px4_msgs::msg::SensorsStatusGnss msg_;
};

class Init_SensorsStatusGnss_failed_checks
{
public:
  explicit Init_SensorsStatusGnss_failed_checks(::px4_msgs::msg::SensorsStatusGnss & msg)
  : msg_(msg)
  {}
  Init_SensorsStatusGnss_strict failed_checks(::px4_msgs::msg::SensorsStatusGnss::_failed_checks_type arg)
  {
    msg_.failed_checks = std::move(arg);
    return Init_SensorsStatusGnss_strict(msg_);
  }

private:
  ::px4_msgs::msg::SensorsStatusGnss msg_;
};

class Init_SensorsStatusGnss_healthy
{
public:
  explicit Init_SensorsStatusGnss_healthy(::px4_msgs::msg::SensorsStatusGnss & msg)
  : msg_(msg)
  {}
  Init_SensorsStatusGnss_failed_checks healthy(::px4_msgs::msg::SensorsStatusGnss::_healthy_type arg)
  {
    msg_.healthy = std::move(arg);
    return Init_SensorsStatusGnss_failed_checks(msg_);
  }

private:
  ::px4_msgs::msg::SensorsStatusGnss msg_;
};

class Init_SensorsStatusGnss_order
{
public:
  explicit Init_SensorsStatusGnss_order(::px4_msgs::msg::SensorsStatusGnss & msg)
  : msg_(msg)
  {}
  Init_SensorsStatusGnss_healthy order(::px4_msgs::msg::SensorsStatusGnss::_order_type arg)
  {
    msg_.order = std::move(arg);
    return Init_SensorsStatusGnss_healthy(msg_);
  }

private:
  ::px4_msgs::msg::SensorsStatusGnss msg_;
};

class Init_SensorsStatusGnss_device_ids
{
public:
  explicit Init_SensorsStatusGnss_device_ids(::px4_msgs::msg::SensorsStatusGnss & msg)
  : msg_(msg)
  {}
  Init_SensorsStatusGnss_order device_ids(::px4_msgs::msg::SensorsStatusGnss::_device_ids_type arg)
  {
    msg_.device_ids = std::move(arg);
    return Init_SensorsStatusGnss_order(msg_);
  }

private:
  ::px4_msgs::msg::SensorsStatusGnss msg_;
};

class Init_SensorsStatusGnss_device_id_selected
{
public:
  explicit Init_SensorsStatusGnss_device_id_selected(::px4_msgs::msg::SensorsStatusGnss & msg)
  : msg_(msg)
  {}
  Init_SensorsStatusGnss_device_ids device_id_selected(::px4_msgs::msg::SensorsStatusGnss::_device_id_selected_type arg)
  {
    msg_.device_id_selected = std::move(arg);
    return Init_SensorsStatusGnss_device_ids(msg_);
  }

private:
  ::px4_msgs::msg::SensorsStatusGnss msg_;
};

class Init_SensorsStatusGnss_timestamp
{
public:
  Init_SensorsStatusGnss_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorsStatusGnss_device_id_selected timestamp(::px4_msgs::msg::SensorsStatusGnss::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_SensorsStatusGnss_device_id_selected(msg_);
  }

private:
  ::px4_msgs::msg::SensorsStatusGnss msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::SensorsStatusGnss>()
{
  return px4_msgs::msg::builder::Init_SensorsStatusGnss_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__BUILDER_HPP_
