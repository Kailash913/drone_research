// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/PrecTakeoffStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/prec_takeoff_status.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/prec_takeoff_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_PrecTakeoffStatus_setpoint_adjusted
{
public:
  explicit Init_PrecTakeoffStatus_setpoint_adjusted(::px4_msgs::msg::PrecTakeoffStatus & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::PrecTakeoffStatus setpoint_adjusted(::px4_msgs::msg::PrecTakeoffStatus::_setpoint_adjusted_type arg)
  {
    msg_.setpoint_adjusted = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::PrecTakeoffStatus msg_;
};

class Init_PrecTakeoffStatus_state
{
public:
  explicit Init_PrecTakeoffStatus_state(::px4_msgs::msg::PrecTakeoffStatus & msg)
  : msg_(msg)
  {}
  Init_PrecTakeoffStatus_setpoint_adjusted state(::px4_msgs::msg::PrecTakeoffStatus::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_PrecTakeoffStatus_setpoint_adjusted(msg_);
  }

private:
  ::px4_msgs::msg::PrecTakeoffStatus msg_;
};

class Init_PrecTakeoffStatus_timestamp
{
public:
  Init_PrecTakeoffStatus_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PrecTakeoffStatus_state timestamp(::px4_msgs::msg::PrecTakeoffStatus::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_PrecTakeoffStatus_state(msg_);
  }

private:
  ::px4_msgs::msg::PrecTakeoffStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::PrecTakeoffStatus>()
{
  return px4_msgs::msg::builder::Init_PrecTakeoffStatus_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__BUILDER_HPP_
