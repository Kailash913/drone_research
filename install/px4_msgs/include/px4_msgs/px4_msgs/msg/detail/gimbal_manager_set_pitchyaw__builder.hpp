// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/GimbalManagerSetPitchyaw.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/gimbal_manager_set_pitchyaw.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__GIMBAL_MANAGER_SET_PITCHYAW__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__GIMBAL_MANAGER_SET_PITCHYAW__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/gimbal_manager_set_pitchyaw__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_GimbalManagerSetPitchyaw_yaw_rate
{
public:
  explicit Init_GimbalManagerSetPitchyaw_yaw_rate(::px4_msgs::msg::GimbalManagerSetPitchyaw & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::GimbalManagerSetPitchyaw yaw_rate(::px4_msgs::msg::GimbalManagerSetPitchyaw::_yaw_rate_type arg)
  {
    msg_.yaw_rate = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::GimbalManagerSetPitchyaw msg_;
};

class Init_GimbalManagerSetPitchyaw_pitch_rate
{
public:
  explicit Init_GimbalManagerSetPitchyaw_pitch_rate(::px4_msgs::msg::GimbalManagerSetPitchyaw & msg)
  : msg_(msg)
  {}
  Init_GimbalManagerSetPitchyaw_yaw_rate pitch_rate(::px4_msgs::msg::GimbalManagerSetPitchyaw::_pitch_rate_type arg)
  {
    msg_.pitch_rate = std::move(arg);
    return Init_GimbalManagerSetPitchyaw_yaw_rate(msg_);
  }

private:
  ::px4_msgs::msg::GimbalManagerSetPitchyaw msg_;
};

class Init_GimbalManagerSetPitchyaw_yaw
{
public:
  explicit Init_GimbalManagerSetPitchyaw_yaw(::px4_msgs::msg::GimbalManagerSetPitchyaw & msg)
  : msg_(msg)
  {}
  Init_GimbalManagerSetPitchyaw_pitch_rate yaw(::px4_msgs::msg::GimbalManagerSetPitchyaw::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_GimbalManagerSetPitchyaw_pitch_rate(msg_);
  }

private:
  ::px4_msgs::msg::GimbalManagerSetPitchyaw msg_;
};

class Init_GimbalManagerSetPitchyaw_pitch
{
public:
  explicit Init_GimbalManagerSetPitchyaw_pitch(::px4_msgs::msg::GimbalManagerSetPitchyaw & msg)
  : msg_(msg)
  {}
  Init_GimbalManagerSetPitchyaw_yaw pitch(::px4_msgs::msg::GimbalManagerSetPitchyaw::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_GimbalManagerSetPitchyaw_yaw(msg_);
  }

private:
  ::px4_msgs::msg::GimbalManagerSetPitchyaw msg_;
};

class Init_GimbalManagerSetPitchyaw_flags
{
public:
  explicit Init_GimbalManagerSetPitchyaw_flags(::px4_msgs::msg::GimbalManagerSetPitchyaw & msg)
  : msg_(msg)
  {}
  Init_GimbalManagerSetPitchyaw_pitch flags(::px4_msgs::msg::GimbalManagerSetPitchyaw::_flags_type arg)
  {
    msg_.flags = std::move(arg);
    return Init_GimbalManagerSetPitchyaw_pitch(msg_);
  }

private:
  ::px4_msgs::msg::GimbalManagerSetPitchyaw msg_;
};

class Init_GimbalManagerSetPitchyaw_gimbal_device_id
{
public:
  explicit Init_GimbalManagerSetPitchyaw_gimbal_device_id(::px4_msgs::msg::GimbalManagerSetPitchyaw & msg)
  : msg_(msg)
  {}
  Init_GimbalManagerSetPitchyaw_flags gimbal_device_id(::px4_msgs::msg::GimbalManagerSetPitchyaw::_gimbal_device_id_type arg)
  {
    msg_.gimbal_device_id = std::move(arg);
    return Init_GimbalManagerSetPitchyaw_flags(msg_);
  }

private:
  ::px4_msgs::msg::GimbalManagerSetPitchyaw msg_;
};

class Init_GimbalManagerSetPitchyaw_target_component
{
public:
  explicit Init_GimbalManagerSetPitchyaw_target_component(::px4_msgs::msg::GimbalManagerSetPitchyaw & msg)
  : msg_(msg)
  {}
  Init_GimbalManagerSetPitchyaw_gimbal_device_id target_component(::px4_msgs::msg::GimbalManagerSetPitchyaw::_target_component_type arg)
  {
    msg_.target_component = std::move(arg);
    return Init_GimbalManagerSetPitchyaw_gimbal_device_id(msg_);
  }

private:
  ::px4_msgs::msg::GimbalManagerSetPitchyaw msg_;
};

class Init_GimbalManagerSetPitchyaw_target_system
{
public:
  explicit Init_GimbalManagerSetPitchyaw_target_system(::px4_msgs::msg::GimbalManagerSetPitchyaw & msg)
  : msg_(msg)
  {}
  Init_GimbalManagerSetPitchyaw_target_component target_system(::px4_msgs::msg::GimbalManagerSetPitchyaw::_target_system_type arg)
  {
    msg_.target_system = std::move(arg);
    return Init_GimbalManagerSetPitchyaw_target_component(msg_);
  }

private:
  ::px4_msgs::msg::GimbalManagerSetPitchyaw msg_;
};

class Init_GimbalManagerSetPitchyaw_timestamp
{
public:
  Init_GimbalManagerSetPitchyaw_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GimbalManagerSetPitchyaw_target_system timestamp(::px4_msgs::msg::GimbalManagerSetPitchyaw::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_GimbalManagerSetPitchyaw_target_system(msg_);
  }

private:
  ::px4_msgs::msg::GimbalManagerSetPitchyaw msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::GimbalManagerSetPitchyaw>()
{
  return px4_msgs::msg::builder::Init_GimbalManagerSetPitchyaw_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__GIMBAL_MANAGER_SET_PITCHYAW__BUILDER_HPP_
