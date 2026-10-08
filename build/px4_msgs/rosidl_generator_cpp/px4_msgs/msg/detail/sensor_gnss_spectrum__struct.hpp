// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/SensorGnssSpectrum.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensor_gnss_spectrum.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__SensorGnssSpectrum __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__SensorGnssSpectrum __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SensorGnssSpectrum_
{
  using Type = SensorGnssSpectrum_<ContainerAllocator>;

  explicit SensorGnssSpectrum_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      this->device_id = 0ul;
      this->block_id = 0;
      std::fill<typename std::array<uint8_t, 256>::iterator, uint8_t>(this->spectrum.begin(), this->spectrum.end(), 0);
      this->spectrum_span = 0ul;
      this->resolution = 0ul;
      this->center_frequency = 0ul;
      this->programmable_gain_amplifier = 0;
    }
  }

  explicit SensorGnssSpectrum_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : spectrum(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      this->device_id = 0ul;
      this->block_id = 0;
      std::fill<typename std::array<uint8_t, 256>::iterator, uint8_t>(this->spectrum.begin(), this->spectrum.end(), 0);
      this->spectrum_span = 0ul;
      this->resolution = 0ul;
      this->center_frequency = 0ul;
      this->programmable_gain_amplifier = 0;
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
  using _spectrum_type =
    std::array<uint8_t, 256>;
  _spectrum_type spectrum;
  using _spectrum_span_type =
    uint32_t;
  _spectrum_span_type spectrum_span;
  using _resolution_type =
    uint32_t;
  _resolution_type resolution;
  using _center_frequency_type =
    uint32_t;
  _center_frequency_type center_frequency;
  using _programmable_gain_amplifier_type =
    uint8_t;
  _programmable_gain_amplifier_type programmable_gain_amplifier;

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
  Type & set__spectrum(
    const std::array<uint8_t, 256> & _arg)
  {
    this->spectrum = _arg;
    return *this;
  }
  Type & set__spectrum_span(
    const uint32_t & _arg)
  {
    this->spectrum_span = _arg;
    return *this;
  }
  Type & set__resolution(
    const uint32_t & _arg)
  {
    this->resolution = _arg;
    return *this;
  }
  Type & set__center_frequency(
    const uint32_t & _arg)
  {
    this->center_frequency = _arg;
    return *this;
  }
  Type & set__programmable_gain_amplifier(
    const uint8_t & _arg)
  {
    this->programmable_gain_amplifier = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__SensorGnssSpectrum
    std::shared_ptr<px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__SensorGnssSpectrum
    std::shared_ptr<px4_msgs::msg::SensorGnssSpectrum_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorGnssSpectrum_ & other) const
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
    if (this->spectrum != other.spectrum) {
      return false;
    }
    if (this->spectrum_span != other.spectrum_span) {
      return false;
    }
    if (this->resolution != other.resolution) {
      return false;
    }
    if (this->center_frequency != other.center_frequency) {
      return false;
    }
    if (this->programmable_gain_amplifier != other.programmable_gain_amplifier) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorGnssSpectrum_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorGnssSpectrum_

// alias to use template instance with default allocator
using SensorGnssSpectrum =
  px4_msgs::msg::SensorGnssSpectrum_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_SPECTRUM__STRUCT_HPP_
