// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/SensorGnssSpectrum.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss_spectrum.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/sensor_gnss_spectrum__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_SensorGnssSpectrum_programmable_gain_amplifier
{
public:
  explicit Init_SensorGnssSpectrum_programmable_gain_amplifier(::px4_msgs::msg::SensorGnssSpectrum & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::SensorGnssSpectrum programmable_gain_amplifier(::px4_msgs::msg::SensorGnssSpectrum::_programmable_gain_amplifier_type arg)
  {
    msg_.programmable_gain_amplifier = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssSpectrum msg_;
};

class Init_SensorGnssSpectrum_center_frequency
{
public:
  explicit Init_SensorGnssSpectrum_center_frequency(::px4_msgs::msg::SensorGnssSpectrum & msg)
  : msg_(msg)
  {}
  Init_SensorGnssSpectrum_programmable_gain_amplifier center_frequency(::px4_msgs::msg::SensorGnssSpectrum::_center_frequency_type arg)
  {
    msg_.center_frequency = std::move(arg);
    return Init_SensorGnssSpectrum_programmable_gain_amplifier(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssSpectrum msg_;
};

class Init_SensorGnssSpectrum_resolution
{
public:
  explicit Init_SensorGnssSpectrum_resolution(::px4_msgs::msg::SensorGnssSpectrum & msg)
  : msg_(msg)
  {}
  Init_SensorGnssSpectrum_center_frequency resolution(::px4_msgs::msg::SensorGnssSpectrum::_resolution_type arg)
  {
    msg_.resolution = std::move(arg);
    return Init_SensorGnssSpectrum_center_frequency(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssSpectrum msg_;
};

class Init_SensorGnssSpectrum_spectrum_span
{
public:
  explicit Init_SensorGnssSpectrum_spectrum_span(::px4_msgs::msg::SensorGnssSpectrum & msg)
  : msg_(msg)
  {}
  Init_SensorGnssSpectrum_resolution spectrum_span(::px4_msgs::msg::SensorGnssSpectrum::_spectrum_span_type arg)
  {
    msg_.spectrum_span = std::move(arg);
    return Init_SensorGnssSpectrum_resolution(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssSpectrum msg_;
};

class Init_SensorGnssSpectrum_spectrum
{
public:
  explicit Init_SensorGnssSpectrum_spectrum(::px4_msgs::msg::SensorGnssSpectrum & msg)
  : msg_(msg)
  {}
  Init_SensorGnssSpectrum_spectrum_span spectrum(::px4_msgs::msg::SensorGnssSpectrum::_spectrum_type arg)
  {
    msg_.spectrum = std::move(arg);
    return Init_SensorGnssSpectrum_spectrum_span(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssSpectrum msg_;
};

class Init_SensorGnssSpectrum_block_id
{
public:
  explicit Init_SensorGnssSpectrum_block_id(::px4_msgs::msg::SensorGnssSpectrum & msg)
  : msg_(msg)
  {}
  Init_SensorGnssSpectrum_spectrum block_id(::px4_msgs::msg::SensorGnssSpectrum::_block_id_type arg)
  {
    msg_.block_id = std::move(arg);
    return Init_SensorGnssSpectrum_spectrum(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssSpectrum msg_;
};

class Init_SensorGnssSpectrum_device_id
{
public:
  explicit Init_SensorGnssSpectrum_device_id(::px4_msgs::msg::SensorGnssSpectrum & msg)
  : msg_(msg)
  {}
  Init_SensorGnssSpectrum_block_id device_id(::px4_msgs::msg::SensorGnssSpectrum::_device_id_type arg)
  {
    msg_.device_id = std::move(arg);
    return Init_SensorGnssSpectrum_block_id(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssSpectrum msg_;
};

class Init_SensorGnssSpectrum_timestamp_sample
{
public:
  explicit Init_SensorGnssSpectrum_timestamp_sample(::px4_msgs::msg::SensorGnssSpectrum & msg)
  : msg_(msg)
  {}
  Init_SensorGnssSpectrum_device_id timestamp_sample(::px4_msgs::msg::SensorGnssSpectrum::_timestamp_sample_type arg)
  {
    msg_.timestamp_sample = std::move(arg);
    return Init_SensorGnssSpectrum_device_id(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssSpectrum msg_;
};

class Init_SensorGnssSpectrum_timestamp
{
public:
  Init_SensorGnssSpectrum_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorGnssSpectrum_timestamp_sample timestamp(::px4_msgs::msg::SensorGnssSpectrum::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_SensorGnssSpectrum_timestamp_sample(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnssSpectrum msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::SensorGnssSpectrum>()
{
  return px4_msgs::msg::builder::Init_SensorGnssSpectrum_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__BUILDER_HPP_
