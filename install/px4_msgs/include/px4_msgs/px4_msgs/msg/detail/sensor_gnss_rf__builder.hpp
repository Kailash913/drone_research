// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/SensorGnssRf.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss_rf.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/sensor_gnss_rf__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_SensorGnssRf_center_frequency
{
public:
  explicit Init_SensorGnssRf_center_frequency(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::SensorGnssRf center_frequency(::px4_msgs::msg::SensorGnssRf::_center_frequency_type arg)
  {
    msg_.center_frequency = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_q_magnitude
{
public:
  explicit Init_SensorGnssRf_q_magnitude(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_center_frequency q_magnitude(::px4_msgs::msg::SensorGnssRf::_q_magnitude_type arg)
  {
    msg_.q_magnitude = std::move(arg);
    return Init_SensorGnssRf_center_frequency(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_q_offset
{
public:
  explicit Init_SensorGnssRf_q_offset(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_q_magnitude q_offset(::px4_msgs::msg::SensorGnssRf::_q_offset_type arg)
  {
    msg_.q_offset = std::move(arg);
    return Init_SensorGnssRf_q_magnitude(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_i_magnitude
{
public:
  explicit Init_SensorGnssRf_i_magnitude(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_q_offset i_magnitude(::px4_msgs::msg::SensorGnssRf::_i_magnitude_type arg)
  {
    msg_.i_magnitude = std::move(arg);
    return Init_SensorGnssRf_q_offset(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_i_offset
{
public:
  explicit Init_SensorGnssRf_i_offset(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_i_magnitude i_offset(::px4_msgs::msg::SensorGnssRf::_i_offset_type arg)
  {
    msg_.i_offset = std::move(arg);
    return Init_SensorGnssRf_i_magnitude(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_jamming_state
{
public:
  explicit Init_SensorGnssRf_jamming_state(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_i_offset jamming_state(::px4_msgs::msg::SensorGnssRf::_jamming_state_type arg)
  {
    msg_.jamming_state = std::move(arg);
    return Init_SensorGnssRf_i_offset(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_jamming_indicator
{
public:
  explicit Init_SensorGnssRf_jamming_indicator(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_jamming_state jamming_indicator(::px4_msgs::msg::SensorGnssRf::_jamming_indicator_type arg)
  {
    msg_.jamming_indicator = std::move(arg);
    return Init_SensorGnssRf_jamming_state(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_automatic_gain_control
{
public:
  explicit Init_SensorGnssRf_automatic_gain_control(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_jamming_indicator automatic_gain_control(::px4_msgs::msg::SensorGnssRf::_automatic_gain_control_type arg)
  {
    msg_.automatic_gain_control = std::move(arg);
    return Init_SensorGnssRf_jamming_indicator(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_noise_per_ms
{
public:
  explicit Init_SensorGnssRf_noise_per_ms(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_automatic_gain_control noise_per_ms(::px4_msgs::msg::SensorGnssRf::_noise_per_ms_type arg)
  {
    msg_.noise_per_ms = std::move(arg);
    return Init_SensorGnssRf_automatic_gain_control(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_post_status
{
public:
  explicit Init_SensorGnssRf_post_status(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_noise_per_ms post_status(::px4_msgs::msg::SensorGnssRf::_post_status_type arg)
  {
    msg_.post_status = std::move(arg);
    return Init_SensorGnssRf_noise_per_ms(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_antenna_power
{
public:
  explicit Init_SensorGnssRf_antenna_power(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_post_status antenna_power(::px4_msgs::msg::SensorGnssRf::_antenna_power_type arg)
  {
    msg_.antenna_power = std::move(arg);
    return Init_SensorGnssRf_post_status(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_antenna_status
{
public:
  explicit Init_SensorGnssRf_antenna_status(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_antenna_power antenna_status(::px4_msgs::msg::SensorGnssRf::_antenna_status_type arg)
  {
    msg_.antenna_status = std::move(arg);
    return Init_SensorGnssRf_antenna_power(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_block_id
{
public:
  explicit Init_SensorGnssRf_block_id(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_antenna_status block_id(::px4_msgs::msg::SensorGnssRf::_block_id_type arg)
  {
    msg_.block_id = std::move(arg);
    return Init_SensorGnssRf_antenna_status(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_device_id
{
public:
  explicit Init_SensorGnssRf_device_id(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_block_id device_id(::px4_msgs::msg::SensorGnssRf::_device_id_type arg)
  {
    msg_.device_id = std::move(arg);
    return Init_SensorGnssRf_block_id(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_timestamp_sample
{
public:
  explicit Init_SensorGnssRf_timestamp_sample(::px4_msgs::msg::SensorGnssRf & msg)
  : msg_(msg)
  {}
  Init_SensorGnssRf_device_id timestamp_sample(::px4_msgs::msg::SensorGnssRf::_timestamp_sample_type arg)
  {
    msg_.timestamp_sample = std::move(arg);
    return Init_SensorGnssRf_device_id(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

class Init_SensorGnssRf_timestamp
{
public:
  Init_SensorGnssRf_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorGnssRf_timestamp_sample timestamp(::px4_msgs::msg::SensorGnssRf::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_SensorGnssRf_timestamp_sample(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssRf msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::SensorGnssRf>()
{
  return px4_msgs::msg::builder::Init_SensorGnssRf_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__BUILDER_HPP_
