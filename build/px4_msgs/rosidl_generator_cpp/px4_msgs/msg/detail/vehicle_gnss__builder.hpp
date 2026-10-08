// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/VehicleGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/vehicle_gnss.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/vehicle_gnss__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_VehicleGnss_failed_checks
{
public:
  explicit Init_VehicleGnss_failed_checks(::px4_msgs::msg::VehicleGnss & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::VehicleGnss failed_checks(::px4_msgs::msg::VehicleGnss::_failed_checks_type arg)
  {
    msg_.failed_checks = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::VehicleGnss msg_;
};

class Init_VehicleGnss_usable
{
public:
  explicit Init_VehicleGnss_usable(::px4_msgs::msg::VehicleGnss & msg)
  : msg_(msg)
  {}
  Init_VehicleGnss_failed_checks usable(::px4_msgs::msg::VehicleGnss::_usable_type arg)
  {
    msg_.usable = std::move(arg);
    return Init_VehicleGnss_failed_checks(msg_);
  }

private:
  ::px4_msgs::msg::VehicleGnss msg_;
};

class Init_VehicleGnss_selection_count
{
public:
  explicit Init_VehicleGnss_selection_count(::px4_msgs::msg::VehicleGnss & msg)
  : msg_(msg)
  {}
  Init_VehicleGnss_usable selection_count(::px4_msgs::msg::VehicleGnss::_selection_count_type arg)
  {
    msg_.selection_count = std::move(arg);
    return Init_VehicleGnss_usable(msg_);
  }

private:
  ::px4_msgs::msg::VehicleGnss msg_;
};

class Init_VehicleGnss_selected_instance
{
public:
  explicit Init_VehicleGnss_selected_instance(::px4_msgs::msg::VehicleGnss & msg)
  : msg_(msg)
  {}
  Init_VehicleGnss_selection_count selected_instance(::px4_msgs::msg::VehicleGnss::_selected_instance_type arg)
  {
    msg_.selected_instance = std::move(arg);
    return Init_VehicleGnss_selection_count(msg_);
  }

private:
  ::px4_msgs::msg::VehicleGnss msg_;
};

class Init_VehicleGnss_antenna_offset
{
public:
  explicit Init_VehicleGnss_antenna_offset(::px4_msgs::msg::VehicleGnss & msg)
  : msg_(msg)
  {}
  Init_VehicleGnss_selected_instance antenna_offset(::px4_msgs::msg::VehicleGnss::_antenna_offset_type arg)
  {
    msg_.antenna_offset = std::move(arg);
    return Init_VehicleGnss_selected_instance(msg_);
  }

private:
  ::px4_msgs::msg::VehicleGnss msg_;
};

class Init_VehicleGnss_receiver
{
public:
  explicit Init_VehicleGnss_receiver(::px4_msgs::msg::VehicleGnss & msg)
  : msg_(msg)
  {}
  Init_VehicleGnss_antenna_offset receiver(::px4_msgs::msg::VehicleGnss::_receiver_type arg)
  {
    msg_.receiver = std::move(arg);
    return Init_VehicleGnss_antenna_offset(msg_);
  }

private:
  ::px4_msgs::msg::VehicleGnss msg_;
};

class Init_VehicleGnss_timestamp_sample
{
public:
  explicit Init_VehicleGnss_timestamp_sample(::px4_msgs::msg::VehicleGnss & msg)
  : msg_(msg)
  {}
  Init_VehicleGnss_receiver timestamp_sample(::px4_msgs::msg::VehicleGnss::_timestamp_sample_type arg)
  {
    msg_.timestamp_sample = std::move(arg);
    return Init_VehicleGnss_receiver(msg_);
  }

private:
  ::px4_msgs::msg::VehicleGnss msg_;
};

class Init_VehicleGnss_timestamp
{
public:
  Init_VehicleGnss_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleGnss_timestamp_sample timestamp(::px4_msgs::msg::VehicleGnss::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_VehicleGnss_timestamp_sample(msg_);
  }

private:
  ::px4_msgs::msg::VehicleGnss msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::VehicleGnss>()
{
  return px4_msgs::msg::builder::Init_VehicleGnss_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__BUILDER_HPP_
