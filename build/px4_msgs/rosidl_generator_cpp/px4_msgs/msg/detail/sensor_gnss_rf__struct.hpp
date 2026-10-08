// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/SensorGnssRf.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss_rf.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__SensorGnssRf __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__SensorGnssRf __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SensorGnssRf_
{
  using Type = SensorGnssRf_<ContainerAllocator>;

  explicit SensorGnssRf_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      this->device_id = 0ul;
      this->block_id = 0;
      this->antenna_status = 0;
      this->antenna_power = 0;
      this->post_status = 0ul;
      this->noise_per_ms = 0;
      this->automatic_gain_control = 0;
      this->jamming_indicator = 0;
      this->jamming_state = 0;
      this->i_offset = 0;
      this->i_magnitude = 0;
      this->q_offset = 0;
      this->q_magnitude = 0;
      this->center_frequency = 0ul;
    }
  }

  explicit SensorGnssRf_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      this->device_id = 0ul;
      this->block_id = 0;
      this->antenna_status = 0;
      this->antenna_power = 0;
      this->post_status = 0ul;
      this->noise_per_ms = 0;
      this->automatic_gain_control = 0;
      this->jamming_indicator = 0;
      this->jamming_state = 0;
      this->i_offset = 0;
      this->i_magnitude = 0;
      this->q_offset = 0;
      this->q_magnitude = 0;
      this->center_frequency = 0ul;
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
  using _block_id_type =
    uint8_t;
  _block_id_type block_id;
  using _antenna_status_type =
    uint8_t;
  _antenna_status_type antenna_status;
  using _antenna_power_type =
    uint8_t;
  _antenna_power_type antenna_power;
  using _post_status_type =
    uint32_t;
  _post_status_type post_status;
  using _noise_per_ms_type =
    uint16_t;
  _noise_per_ms_type noise_per_ms;
  using _automatic_gain_control_type =
    uint16_t;
  _automatic_gain_control_type automatic_gain_control;
  using _jamming_indicator_type =
    uint8_t;
  _jamming_indicator_type jamming_indicator;
  using _jamming_state_type =
    uint8_t;
  _jamming_state_type jamming_state;
  using _i_offset_type =
    int8_t;
  _i_offset_type i_offset;
  using _i_magnitude_type =
    uint8_t;
  _i_magnitude_type i_magnitude;
  using _q_offset_type =
    int8_t;
  _q_offset_type q_offset;
  using _q_magnitude_type =
    uint8_t;
  _q_magnitude_type q_magnitude;
  using _center_frequency_type =
    uint32_t;
  _center_frequency_type center_frequency;

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
  Type & set__block_id(
    const uint8_t & _arg)
  {
    this->block_id = _arg;
    return *this;
  }
  Type & set__antenna_status(
    const uint8_t & _arg)
  {
    this->antenna_status = _arg;
    return *this;
  }
  Type & set__antenna_power(
    const uint8_t & _arg)
  {
    this->antenna_power = _arg;
    return *this;
  }
  Type & set__post_status(
    const uint32_t & _arg)
  {
    this->post_status = _arg;
    return *this;
  }
  Type & set__noise_per_ms(
    const uint16_t & _arg)
  {
    this->noise_per_ms = _arg;
    return *this;
  }
  Type & set__automatic_gain_control(
    const uint16_t & _arg)
  {
    this->automatic_gain_control = _arg;
    return *this;
  }
  Type & set__jamming_indicator(
    const uint8_t & _arg)
  {
    this->jamming_indicator = _arg;
    return *this;
  }
  Type & set__jamming_state(
    const uint8_t & _arg)
  {
    this->jamming_state = _arg;
    return *this;
  }
  Type & set__i_offset(
    const int8_t & _arg)
  {
    this->i_offset = _arg;
    return *this;
  }
  Type & set__i_magnitude(
    const uint8_t & _arg)
  {
    this->i_magnitude = _arg;
    return *this;
  }
  Type & set__q_offset(
    const int8_t & _arg)
  {
    this->q_offset = _arg;
    return *this;
  }
  Type & set__q_magnitude(
    const uint8_t & _arg)
  {
    this->q_magnitude = _arg;
    return *this;
  }
  Type & set__center_frequency(
    const uint32_t & _arg)
  {
    this->center_frequency = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t ANTENNA_STATUS_INIT =
    0u;
  static constexpr uint8_t ANTENNA_STATUS_UNKNOWN =
    1u;
  static constexpr uint8_t ANTENNA_STATUS_OK =
    2u;
  static constexpr uint8_t ANTENNA_STATUS_SHORT =
    3u;
  static constexpr uint8_t ANTENNA_STATUS_OPEN =
    4u;
  static constexpr uint8_t ANTENNA_POWER_OFF =
    0u;
  static constexpr uint8_t ANTENNA_POWER_ON =
    1u;
  static constexpr uint8_t ANTENNA_POWER_UNKNOWN =
    2u;
  static constexpr uint8_t JAMMING_STATE_UNKNOWN =
    0u;
  static constexpr uint8_t JAMMING_STATE_OK =
    1u;
  static constexpr uint8_t JAMMING_STATE_WARNING =
    2u;
  static constexpr uint8_t JAMMING_STATE_CRITICAL =
    3u;

  // pointer types
  using RawPtr =
    px4_msgs::msg::SensorGnssRf_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::SensorGnssRf_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::SensorGnssRf_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::SensorGnssRf_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::SensorGnssRf_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::SensorGnssRf_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::SensorGnssRf_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::SensorGnssRf_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::SensorGnssRf_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::SensorGnssRf_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__SensorGnssRf
    std::shared_ptr<px4_msgs::msg::SensorGnssRf_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__SensorGnssRf
    std::shared_ptr<px4_msgs::msg::SensorGnssRf_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorGnssRf_ & other) const
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
    if (this->block_id != other.block_id) {
      return false;
    }
    if (this->antenna_status != other.antenna_status) {
      return false;
    }
    if (this->antenna_power != other.antenna_power) {
      return false;
    }
    if (this->post_status != other.post_status) {
      return false;
    }
    if (this->noise_per_ms != other.noise_per_ms) {
      return false;
    }
    if (this->automatic_gain_control != other.automatic_gain_control) {
      return false;
    }
    if (this->jamming_indicator != other.jamming_indicator) {
      return false;
    }
    if (this->jamming_state != other.jamming_state) {
      return false;
    }
    if (this->i_offset != other.i_offset) {
      return false;
    }
    if (this->i_magnitude != other.i_magnitude) {
      return false;
    }
    if (this->q_offset != other.q_offset) {
      return false;
    }
    if (this->q_magnitude != other.q_magnitude) {
      return false;
    }
    if (this->center_frequency != other.center_frequency) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorGnssRf_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorGnssRf_

// alias to use template instance with default allocator
using SensorGnssRf =
  px4_msgs::msg::SensorGnssRf_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::ANTENNA_STATUS_INIT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::ANTENNA_STATUS_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::ANTENNA_STATUS_OK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::ANTENNA_STATUS_SHORT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::ANTENNA_STATUS_OPEN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::ANTENNA_POWER_OFF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::ANTENNA_POWER_ON;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::ANTENNA_POWER_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::JAMMING_STATE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::JAMMING_STATE_OK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::JAMMING_STATE_WARNING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorGnssRf_<ContainerAllocator>::JAMMING_STATE_CRITICAL;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RF__STRUCT_HPP_
