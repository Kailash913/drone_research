// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/SensorGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__SensorGnss __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__SensorGnss __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SensorGnss_
{
  using Type = SensorGnss_<ContainerAllocator>;

  explicit SensorGnss_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      this->device_id = 0ul;
      this->latitude = 0.0;
      this->longitude = 0.0;
      this->altitude_msl = 0.0;
      this->altitude_ellipsoid = 0.0;
      this->speed_accuracy = 0.0f;
      this->course_accuracy = 0.0f;
      this->fix_type = 0;
      this->eph = 0.0f;
      this->epv = 0.0f;
      this->hdop = 0.0f;
      this->vdop = 0.0f;
      this->noise = 0l;
      this->automatic_gain_control = 0;
      this->jamming_state = 0;
      this->jamming_indicator = 0l;
      this->spoofing_state = 0;
      this->authentication_state = 0;
      this->ground_speed = 0.0f;
      this->vel_north = 0.0f;
      this->vel_east = 0.0f;
      this->vel_down = 0.0f;
      this->course = 0.0f;
      this->vel_ned_valid = false;
      this->timestamp_time_relative = 0l;
      this->time_utc_usec = 0ull;
      this->satellites_used = 0;
      this->system_error = 0ul;
      this->rtcm_injection_rate = 0.0f;
      this->selected_rtcm_instance = 0;
      this->corrections_protocol = 0;
      this->corrections_crc_failed = false;
      this->corrections_msg_used = 0;
    }
  }

  explicit SensorGnss_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      this->device_id = 0ul;
      this->latitude = 0.0;
      this->longitude = 0.0;
      this->altitude_msl = 0.0;
      this->altitude_ellipsoid = 0.0;
      this->speed_accuracy = 0.0f;
      this->course_accuracy = 0.0f;
      this->fix_type = 0;
      this->eph = 0.0f;
      this->epv = 0.0f;
      this->hdop = 0.0f;
      this->vdop = 0.0f;
      this->noise = 0l;
      this->automatic_gain_control = 0;
      this->jamming_state = 0;
      this->jamming_indicator = 0l;
      this->spoofing_state = 0;
      this->authentication_state = 0;
      this->ground_speed = 0.0f;
      this->vel_north = 0.0f;
      this->vel_east = 0.0f;
      this->vel_down = 0.0f;
      this->course = 0.0f;
      this->vel_ned_valid = false;
      this->timestamp_time_relative = 0l;
      this->time_utc_usec = 0ull;
      this->satellites_used = 0;
      this->system_error = 0ul;
      this->rtcm_injection_rate = 0.0f;
      this->selected_rtcm_instance = 0;
      this->corrections_protocol = 0;
      this->corrections_crc_failed = false;
      this->corrections_msg_used = 0;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _timestamp_sample_type =
    uint64_t;
  _timestamp_sample_type timestamp_sample;
  using _device_id_type =
    uint32_t;
  _device_id_type device_id;
  using _latitude_type =
    double;
  _latitude_type latitude;
  using _longitude_type =
    double;
  _longitude_type longitude;
  using _altitude_msl_type =
    double;
  _altitude_msl_type altitude_msl;
  using _altitude_ellipsoid_type =
    double;
  _altitude_ellipsoid_type altitude_ellipsoid;
  using _speed_accuracy_type =
    float;
  _speed_accuracy_type speed_accuracy;
  using _course_accuracy_type =
    float;
  _course_accuracy_type course_accuracy;
  using _fix_type_type =
    uint8_t;
  _fix_type_type fix_type;
  using _eph_type =
    float;
  _eph_type eph;
  using _epv_type =
    float;
  _epv_type epv;
  using _hdop_type =
    float;
  _hdop_type hdop;
  using _vdop_type =
    float;
  _vdop_type vdop;
  using _noise_type =
    int32_t;
  _noise_type noise;
  using _automatic_gain_control_type =
    uint16_t;
  _automatic_gain_control_type automatic_gain_control;
  using _jamming_state_type =
    uint8_t;
  _jamming_state_type jamming_state;
  using _jamming_indicator_type =
    int32_t;
  _jamming_indicator_type jamming_indicator;
  using _spoofing_state_type =
    uint8_t;
  _spoofing_state_type spoofing_state;
  using _authentication_state_type =
    uint8_t;
  _authentication_state_type authentication_state;
  using _ground_speed_type =
    float;
  _ground_speed_type ground_speed;
  using _vel_north_type =
    float;
  _vel_north_type vel_north;
  using _vel_east_type =
    float;
  _vel_east_type vel_east;
  using _vel_down_type =
    float;
  _vel_down_type vel_down;
  using _course_type =
    float;
  _course_type course;
  using _vel_ned_valid_type =
    bool;
  _vel_ned_valid_type vel_ned_valid;
  using _timestamp_time_relative_type =
    int32_t;
  _timestamp_time_relative_type timestamp_time_relative;
  using _time_utc_usec_type =
    uint64_t;
  _time_utc_usec_type time_utc_usec;
  using _satellites_used_type =
    uint8_t;
  _satellites_used_type satellites_used;
  using _system_error_type =
    uint32_t;
  _system_error_type system_error;
  using _rtcm_injection_rate_type =
    float;
  _rtcm_injection_rate_type rtcm_injection_rate;
  using _selected_rtcm_instance_type =
    uint8_t;
  _selected_rtcm_instance_type selected_rtcm_instance;
  using _corrections_protocol_type =
    uint8_t;
  _corrections_protocol_type corrections_protocol;
  using _corrections_crc_failed_type =
    bool;
  _corrections_crc_failed_type corrections_crc_failed;
  using _corrections_msg_used_type =
    uint8_t;
  _corrections_msg_used_type corrections_msg_used;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__timestamp_sample(
    const uint64_t & _arg)
  {
    this->timestamp_sample = _arg;
    return *this;
  }
  Type & set__device_id(
    const uint32_t & _arg)
  {
    this->device_id = _arg;
    return *this;
  }
  Type & set__latitude(
    const double & _arg)
  {
    this->latitude = _arg;
    return *this;
  }
  Type & set__longitude(
    const double & _arg)
  {
    this->longitude = _arg;
    return *this;
  }
  Type & set__altitude_msl(
    const double & _arg)
  {
    this->altitude_msl = _arg;
    return *this;
  }
  Type & set__altitude_ellipsoid(
    const double & _arg)
  {
    this->altitude_ellipsoid = _arg;
    return *this;
  }
  Type & set__speed_accuracy(
    const float & _arg)
  {
    this->speed_accuracy = _arg;
    return *this;
  }
  Type & set__course_accuracy(
    const float & _arg)
  {
    this->course_accuracy = _arg;
    return *this;
  }
  Type & set__fix_type(
    const uint8_t & _arg)
  {
    this->fix_type = _arg;
    return *this;
  }
  Type & set__eph(
    const float & _arg)
  {
    this->eph = _arg;
    return *this;
  }
  Type & set__epv(
    const float & _arg)
  {
    this->epv = _arg;
    return *this;
  }
  Type & set__hdop(
    const float & _arg)
  {
    this->hdop = _arg;
    return *this;
  }
  Type & set__vdop(
    const float & _arg)
  {
    this->vdop = _arg;
    return *this;
  }
  Type & set__noise(
    const int32_t & _arg)
  {
    this->noise = _arg;
    return *this;
  }
  Type & set__automatic_gain_control(
    const uint16_t & _arg)
  {
    this->automatic_gain_control = _arg;
    return *this;
  }
  Type & set__jamming_state(
    const uint8_t & _arg)
  {
    this->jamming_state = _arg;
    return *this;
  }
  Type & set__jamming_indicator(
    const int32_t & _arg)
  {
    this->jamming_indicator = _arg;
    return *this;
  }
  Type & set__spoofing_state(
    const uint8_t & _arg)
  {
    this->spoofing_state = _arg;
    return *this;
  }
  Type & set__authentication_state(
    const uint8_t & _arg)
  {
    this->authentication_state = _arg;
    return *this;
  }
  Type & set__ground_speed(
    const float & _arg)
  {
    this->ground_speed = _arg;
    return *this;
  }
  Type & set__vel_north(
    const float & _arg)
  {
    this->vel_north = _arg;
    return *this;
  }
  Type & set__vel_east(
    const float & _arg)
  {
    this->vel_east = _arg;
    return *this;
  }
  Type & set__vel_down(
    const float & _arg)
  {
    this->vel_down = _arg;
    return *this;
  }
  Type & set__course(
    const float & _arg)
  {
    this->course = _arg;
    return *this;
  }
  Type & set__vel_ned_valid(
    const bool & _arg)
  {
    this->vel_ned_valid = _arg;
    return *this;
  }
  Type & set__timestamp_time_relative(
    const int32_t & _arg)
  {
    this->timestamp_time_relative = _arg;
    return *this;
  }
  Type & set__time_utc_usec(
    const uint64_t & _arg)
  {
    this->time_utc_usec = _arg;
    return *this;
  }
  Type & set__satellites_used(
    const uint8_t & _arg)
  {
    this->satellites_used = _arg;
    return *this;
  }
  Type & set__system_error(
    const uint32_t & _arg)
  {
    this->system_error = _arg;
    return *this;
  }
  Type & set__rtcm_injection_rate(
    const float & _arg)
  {
    this->rtcm_injection_rate = _arg;
    return *this;
  }
  Type & set__selected_rtcm_instance(
    const uint8_t & _arg)
  {
    this->selected_rtcm_instance = _arg;
    return *this;
  }
  Type & set__corrections_protocol(
    const uint8_t & _arg)
  {
    this->corrections_protocol = _arg;
    return *this;
  }
  Type & set__corrections_crc_failed(
    const bool & _arg)
  {
    this->corrections_crc_failed = _arg;
    return *this;
  }
  Type & set__corrections_msg_used(
    const uint8_t & _arg)
  {
    this->corrections_msg_used = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t FIX_TYPE_NONE =
    1u;
  static constexpr uint8_t FIX_TYPE_2D =
    2u;
  static constexpr uint8_t FIX_TYPE_3D =
    3u;
  static constexpr uint8_t FIX_TYPE_RTCM_CODE_DIFFERENTIAL =
    4u;
  static constexpr uint8_t FIX_TYPE_RTK_FLOAT =
    5u;
  static constexpr uint8_t FIX_TYPE_RTK_FIXED =
    6u;
  static constexpr uint8_t FIX_TYPE_EXTRAPOLATED =
    8u;
  static constexpr uint8_t JAMMING_STATE_UNKNOWN =
    0u;
  static constexpr uint8_t JAMMING_STATE_OK =
    1u;
  static constexpr uint8_t JAMMING_STATE_MITIGATED =
    2u;
  static constexpr uint8_t JAMMING_STATE_DETECTED =
    3u;
  static constexpr uint8_t SPOOFING_STATE_UNKNOWN =
    0u;
  static constexpr uint8_t SPOOFING_STATE_OK =
    1u;
  static constexpr uint8_t SPOOFING_STATE_MITIGATED =
    2u;
  static constexpr uint8_t SPOOFING_STATE_DETECTED =
    3u;
  static constexpr uint8_t AUTHENTICATION_STATE_UNKNOWN =
    0u;
  static constexpr uint8_t AUTHENTICATION_STATE_INITIALIZING =
    1u;
  static constexpr uint8_t AUTHENTICATION_STATE_ERROR =
    2u;
  static constexpr uint8_t AUTHENTICATION_STATE_OK =
    3u;
  static constexpr uint8_t AUTHENTICATION_STATE_DISABLED =
    4u;
  static constexpr uint32_t SYSTEM_ERROR_OK =
    0u;
  static constexpr uint32_t SYSTEM_ERROR_INCOMING_CORRECTIONS =
    1u;
  static constexpr uint32_t SYSTEM_ERROR_CONFIGURATION =
    2u;
  static constexpr uint32_t SYSTEM_ERROR_SOFTWARE =
    4u;
  static constexpr uint32_t SYSTEM_ERROR_ANTENNA =
    8u;
  static constexpr uint32_t SYSTEM_ERROR_EVENT_CONGESTION =
    16u;
  static constexpr uint32_t SYSTEM_ERROR_CPU_OVERLOAD =
    32u;
  static constexpr uint32_t SYSTEM_ERROR_OUTPUT_CONGESTION =
    64u;
  static constexpr uint8_t CORRECTIONS_PROTOCOL_UNKNOWN =
    0u;
  static constexpr uint8_t CORRECTIONS_PROTOCOL_RTCM3 =
    1u;
  static constexpr uint8_t CORRECTIONS_PROTOCOL_SPARTN =
    2u;
  static constexpr uint8_t CORRECTIONS_PROTOCOL_HAS =
    3u;
  static constexpr uint8_t CORRECTIONS_PROTOCOL_PMP =
    4u;
  static constexpr uint8_t CORRECTIONS_PROTOCOL_QZSS_L6 =
    5u;
  static constexpr uint8_t CORRECTIONS_MSG_USED_UNKNOWN =
    0u;
  static constexpr uint8_t CORRECTIONS_MSG_USED_NOT_USED =
    1u;
  static constexpr uint8_t CORRECTIONS_MSG_USED_USED =
    2u;

  // pointer types
  using RawPtr =
    px4_msgs::msg::SensorGnss_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::SensorGnss_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::SensorGnss_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::SensorGnss_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::SensorGnss_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::SensorGnss_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::SensorGnss_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::SensorGnss_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::SensorGnss_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::SensorGnss_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__SensorGnss
    std::shared_ptr<px4_msgs::msg::SensorGnss_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__SensorGnss
    std::shared_ptr<px4_msgs::msg::SensorGnss_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorGnss_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->timestamp_sample != other.timestamp_sample) {
      return false;
    }
    if (this->device_id != other.device_id) {
      return false;
    }
    if (this->latitude != other.latitude) {
      return false;
    }
    if (this->longitude != other.longitude) {
      return false;
    }
    if (this->altitude_msl != other.altitude_msl) {
      return false;
    }
    if (this->altitude_ellipsoid != other.altitude_ellipsoid) {
      return false;
    }
    if (this->speed_accuracy != other.speed_accuracy) {
      return false;
    }
    if (this->course_accuracy != other.course_accuracy) {
      return false;
    }
    if (this->fix_type != other.fix_type) {
      return false;
    }
    if (this->eph != other.eph) {
      return false;
    }
    if (this->epv != other.epv) {
      return false;
    }
    if (this->hdop != other.hdop) {
      return false;
    }
    if (this->vdop != other.vdop) {
      return false;
    }
    if (this->noise != other.noise) {
      return false;
    }
    if (this->automatic_gain_control != other.automatic_gain_control) {
      return false;
    }
    if (this->jamming_state != other.jamming_state) {
      return false;
    }
    if (this->jamming_indicator != other.jamming_indicator) {
      return false;
    }
    if (this->spoofing_state != other.spoofing_state) {
      return false;
    }
    if (this->authentication_state != other.authentication_state) {
      return false;
    }
    if (this->ground_speed != other.ground_speed) {
      return false;
    }
    if (this->vel_north != other.vel_north) {
      return false;
    }
    if (this->vel_east != other.vel_east) {
      return false;
    }
    if (this->vel_down != other.vel_down) {
      return false;
    }
    if (this->course != other.course) {
      return false;
    }
    if (this->vel_ned_valid != other.vel_ned_valid) {
      return false;
    }
    if (this->timestamp_time_relative != other.timestamp_time_relative) {
      return false;
    }
    if (this->time_utc_usec != other.time_utc_usec) {
      return false;
    }
    if (this->satellites_used != other.satellites_used) {
      return false;
    }
    if (this->system_error != other.system_error) {
      return false;
    }
    if (this->rtcm_injection_rate != other.rtcm_injection_rate) {
      return false;
    }
    if (this->selected_rtcm_instance != other.selected_rtcm_instance) {
      return false;
    }
    if (this->corrections_protocol != other.corrections_protocol) {
      return false;
    }
    if (this->corrections_crc_failed != other.corrections_crc_failed) {
      return false;
    }
    if (this->corrections_msg_used != other.corrections_msg_used) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorGnss_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorGnss_

// alias to use template instance with default allocator
using SensorGnss =
  px4_msgs::msg::SensorGnss_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::FIX_TYPE_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::FIX_TYPE_2D;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::FIX_TYPE_3D;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::FIX_TYPE_RTCM_CODE_DIFFERENTIAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::FIX_TYPE_RTK_FLOAT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::FIX_TYPE_RTK_FIXED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::FIX_TYPE_EXTRAPOLATED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::JAMMING_STATE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::JAMMING_STATE_OK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::JAMMING_STATE_MITIGATED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::JAMMING_STATE_DETECTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::SPOOFING_STATE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::SPOOFING_STATE_OK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::SPOOFING_STATE_MITIGATED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::SPOOFING_STATE_DETECTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::AUTHENTICATION_STATE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::AUTHENTICATION_STATE_INITIALIZING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::AUTHENTICATION_STATE_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::AUTHENTICATION_STATE_OK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::AUTHENTICATION_STATE_DISABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SensorGnss_<ContainerAllocator>::SYSTEM_ERROR_OK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SensorGnss_<ContainerAllocator>::SYSTEM_ERROR_INCOMING_CORRECTIONS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SensorGnss_<ContainerAllocator>::SYSTEM_ERROR_CONFIGURATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SensorGnss_<ContainerAllocator>::SYSTEM_ERROR_SOFTWARE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SensorGnss_<ContainerAllocator>::SYSTEM_ERROR_ANTENNA;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SensorGnss_<ContainerAllocator>::SYSTEM_ERROR_EVENT_CONGESTION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SensorGnss_<ContainerAllocator>::SYSTEM_ERROR_CPU_OVERLOAD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SensorGnss_<ContainerAllocator>::SYSTEM_ERROR_OUTPUT_CONGESTION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::CORRECTIONS_PROTOCOL_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::CORRECTIONS_PROTOCOL_RTCM3;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::CORRECTIONS_PROTOCOL_SPARTN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::CORRECTIONS_PROTOCOL_HAS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::CORRECTIONS_PROTOCOL_PMP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::CORRECTIONS_PROTOCOL_QZSS_L6;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::CORRECTIONS_MSG_USED_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::CORRECTIONS_MSG_USED_NOT_USED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnss_<ContainerAllocator>::CORRECTIONS_MSG_USED_USED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS__STRUCT_HPP_
