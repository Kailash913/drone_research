// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/SensorGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/sensor_gnss__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_SensorGnss_corrections_msg_used
{
public:
  explicit Init_SensorGnss_corrections_msg_used(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::SensorGnss corrections_msg_used(::px4_msgs::msg::SensorGnss::_corrections_msg_used_type arg)
  {
    msg_.corrections_msg_used = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_corrections_crc_failed
{
public:
  explicit Init_SensorGnss_corrections_crc_failed(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_corrections_msg_used corrections_crc_failed(::px4_msgs::msg::SensorGnss::_corrections_crc_failed_type arg)
  {
    msg_.corrections_crc_failed = std::move(arg);
    return Init_SensorGnss_corrections_msg_used(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_corrections_protocol
{
public:
  explicit Init_SensorGnss_corrections_protocol(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_corrections_crc_failed corrections_protocol(::px4_msgs::msg::SensorGnss::_corrections_protocol_type arg)
  {
    msg_.corrections_protocol = std::move(arg);
    return Init_SensorGnss_corrections_crc_failed(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_selected_rtcm_instance
{
public:
  explicit Init_SensorGnss_selected_rtcm_instance(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_corrections_protocol selected_rtcm_instance(::px4_msgs::msg::SensorGnss::_selected_rtcm_instance_type arg)
  {
    msg_.selected_rtcm_instance = std::move(arg);
    return Init_SensorGnss_corrections_protocol(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_rtcm_injection_rate
{
public:
  explicit Init_SensorGnss_rtcm_injection_rate(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_selected_rtcm_instance rtcm_injection_rate(::px4_msgs::msg::SensorGnss::_rtcm_injection_rate_type arg)
  {
    msg_.rtcm_injection_rate = std::move(arg);
    return Init_SensorGnss_selected_rtcm_instance(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_system_error
{
public:
  explicit Init_SensorGnss_system_error(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_rtcm_injection_rate system_error(::px4_msgs::msg::SensorGnss::_system_error_type arg)
  {
    msg_.system_error = std::move(arg);
    return Init_SensorGnss_rtcm_injection_rate(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_satellites_used
{
public:
  explicit Init_SensorGnss_satellites_used(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_system_error satellites_used(::px4_msgs::msg::SensorGnss::_satellites_used_type arg)
  {
    msg_.satellites_used = std::move(arg);
    return Init_SensorGnss_system_error(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_time_utc_usec
{
public:
  explicit Init_SensorGnss_time_utc_usec(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_satellites_used time_utc_usec(::px4_msgs::msg::SensorGnss::_time_utc_usec_type arg)
  {
    msg_.time_utc_usec = std::move(arg);
    return Init_SensorGnss_satellites_used(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_timestamp_time_relative
{
public:
  explicit Init_SensorGnss_timestamp_time_relative(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_time_utc_usec timestamp_time_relative(::px4_msgs::msg::SensorGnss::_timestamp_time_relative_type arg)
  {
    msg_.timestamp_time_relative = std::move(arg);
    return Init_SensorGnss_time_utc_usec(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_vel_ned_valid
{
public:
  explicit Init_SensorGnss_vel_ned_valid(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_timestamp_time_relative vel_ned_valid(::px4_msgs::msg::SensorGnss::_vel_ned_valid_type arg)
  {
    msg_.vel_ned_valid = std::move(arg);
    return Init_SensorGnss_timestamp_time_relative(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_course
{
public:
  explicit Init_SensorGnss_course(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_vel_ned_valid course(::px4_msgs::msg::SensorGnss::_course_type arg)
  {
    msg_.course = std::move(arg);
    return Init_SensorGnss_vel_ned_valid(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_vel_down
{
public:
  explicit Init_SensorGnss_vel_down(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_course vel_down(::px4_msgs::msg::SensorGnss::_vel_down_type arg)
  {
    msg_.vel_down = std::move(arg);
    return Init_SensorGnss_course(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_vel_east
{
public:
  explicit Init_SensorGnss_vel_east(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_vel_down vel_east(::px4_msgs::msg::SensorGnss::_vel_east_type arg)
  {
    msg_.vel_east = std::move(arg);
    return Init_SensorGnss_vel_down(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_vel_north
{
public:
  explicit Init_SensorGnss_vel_north(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_vel_east vel_north(::px4_msgs::msg::SensorGnss::_vel_north_type arg)
  {
    msg_.vel_north = std::move(arg);
    return Init_SensorGnss_vel_east(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_ground_speed
{
public:
  explicit Init_SensorGnss_ground_speed(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_vel_north ground_speed(::px4_msgs::msg::SensorGnss::_ground_speed_type arg)
  {
    msg_.ground_speed = std::move(arg);
    return Init_SensorGnss_vel_north(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_authentication_state
{
public:
  explicit Init_SensorGnss_authentication_state(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_ground_speed authentication_state(::px4_msgs::msg::SensorGnss::_authentication_state_type arg)
  {
    msg_.authentication_state = std::move(arg);
    return Init_SensorGnss_ground_speed(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_spoofing_state
{
public:
  explicit Init_SensorGnss_spoofing_state(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_authentication_state spoofing_state(::px4_msgs::msg::SensorGnss::_spoofing_state_type arg)
  {
    msg_.spoofing_state = std::move(arg);
    return Init_SensorGnss_authentication_state(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_jamming_indicator
{
public:
  explicit Init_SensorGnss_jamming_indicator(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_spoofing_state jamming_indicator(::px4_msgs::msg::SensorGnss::_jamming_indicator_type arg)
  {
    msg_.jamming_indicator = std::move(arg);
    return Init_SensorGnss_spoofing_state(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_jamming_state
{
public:
  explicit Init_SensorGnss_jamming_state(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_jamming_indicator jamming_state(::px4_msgs::msg::SensorGnss::_jamming_state_type arg)
  {
    msg_.jamming_state = std::move(arg);
    return Init_SensorGnss_jamming_indicator(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_automatic_gain_control
{
public:
  explicit Init_SensorGnss_automatic_gain_control(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_jamming_state automatic_gain_control(::px4_msgs::msg::SensorGnss::_automatic_gain_control_type arg)
  {
    msg_.automatic_gain_control = std::move(arg);
    return Init_SensorGnss_jamming_state(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_noise
{
public:
  explicit Init_SensorGnss_noise(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_automatic_gain_control noise(::px4_msgs::msg::SensorGnss::_noise_type arg)
  {
    msg_.noise = std::move(arg);
    return Init_SensorGnss_automatic_gain_control(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_vdop
{
public:
  explicit Init_SensorGnss_vdop(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_noise vdop(::px4_msgs::msg::SensorGnss::_vdop_type arg)
  {
    msg_.vdop = std::move(arg);
    return Init_SensorGnss_noise(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_hdop
{
public:
  explicit Init_SensorGnss_hdop(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_vdop hdop(::px4_msgs::msg::SensorGnss::_hdop_type arg)
  {
    msg_.hdop = std::move(arg);
    return Init_SensorGnss_vdop(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_epv
{
public:
  explicit Init_SensorGnss_epv(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_hdop epv(::px4_msgs::msg::SensorGnss::_epv_type arg)
  {
    msg_.epv = std::move(arg);
    return Init_SensorGnss_hdop(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_eph
{
public:
  explicit Init_SensorGnss_eph(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_epv eph(::px4_msgs::msg::SensorGnss::_eph_type arg)
  {
    msg_.eph = std::move(arg);
    return Init_SensorGnss_epv(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_fix_type
{
public:
  explicit Init_SensorGnss_fix_type(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_eph fix_type(::px4_msgs::msg::SensorGnss::_fix_type_type arg)
  {
    msg_.fix_type = std::move(arg);
    return Init_SensorGnss_eph(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_course_accuracy
{
public:
  explicit Init_SensorGnss_course_accuracy(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_fix_type course_accuracy(::px4_msgs::msg::SensorGnss::_course_accuracy_type arg)
  {
    msg_.course_accuracy = std::move(arg);
    return Init_SensorGnss_fix_type(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_speed_accuracy
{
public:
  explicit Init_SensorGnss_speed_accuracy(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_course_accuracy speed_accuracy(::px4_msgs::msg::SensorGnss::_speed_accuracy_type arg)
  {
    msg_.speed_accuracy = std::move(arg);
    return Init_SensorGnss_course_accuracy(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_altitude_ellipsoid
{
public:
  explicit Init_SensorGnss_altitude_ellipsoid(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_speed_accuracy altitude_ellipsoid(::px4_msgs::msg::SensorGnss::_altitude_ellipsoid_type arg)
  {
    msg_.altitude_ellipsoid = std::move(arg);
    return Init_SensorGnss_speed_accuracy(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_altitude_msl
{
public:
  explicit Init_SensorGnss_altitude_msl(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_altitude_ellipsoid altitude_msl(::px4_msgs::msg::SensorGnss::_altitude_msl_type arg)
  {
    msg_.altitude_msl = std::move(arg);
    return Init_SensorGnss_altitude_ellipsoid(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_longitude
{
public:
  explicit Init_SensorGnss_longitude(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_altitude_msl longitude(::px4_msgs::msg::SensorGnss::_longitude_type arg)
  {
    msg_.longitude = std::move(arg);
    return Init_SensorGnss_altitude_msl(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_latitude
{
public:
  explicit Init_SensorGnss_latitude(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_longitude latitude(::px4_msgs::msg::SensorGnss::_latitude_type arg)
  {
    msg_.latitude = std::move(arg);
    return Init_SensorGnss_longitude(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_device_id
{
public:
  explicit Init_SensorGnss_device_id(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_latitude device_id(::px4_msgs::msg::SensorGnss::_device_id_type arg)
  {
    msg_.device_id = std::move(arg);
    return Init_SensorGnss_latitude(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_timestamp_sample
{
public:
  explicit Init_SensorGnss_timestamp_sample(::px4_msgs::msg::SensorGnss & msg)
  : msg_(msg)
  {}
  Init_SensorGnss_device_id timestamp_sample(::px4_msgs::msg::SensorGnss::_timestamp_sample_type arg)
  {
    msg_.timestamp_sample = std::move(arg);
    return Init_SensorGnss_device_id(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

class Init_SensorGnss_timestamp
{
public:
  Init_SensorGnss_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorGnss_timestamp_sample timestamp(::px4_msgs::msg::SensorGnss::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_SensorGnss_timestamp_sample(msg_);
  }

private:
  ::px4_msgs::msg::SensorGnss msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::SensorGnss>()
{
  return px4_msgs::msg::builder::Init_SensorGnss_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__BUILDER_HPP_
