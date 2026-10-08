// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from px4_msgs:msg/SensorGnssSpectrum.idl
// generated code does not contain a copyright notice
#include "px4_msgs/msg/detail/sensor_gnss_spectrum__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
px4_msgs__msg__SensorGnssSpectrum__init(px4_msgs__msg__SensorGnssSpectrum * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  // timestamp_sample
  // device_id
  // block_id
  // spectrum
  // spectrum_span
  // resolution
  // center_frequency
  // programmable_gain_amplifier
  return true;
}

void
px4_msgs__msg__SensorGnssSpectrum__fini(px4_msgs__msg__SensorGnssSpectrum * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  // timestamp_sample
  // device_id
  // block_id
  // spectrum
  // spectrum_span
  // resolution
  // center_frequency
  // programmable_gain_amplifier
}

bool
px4_msgs__msg__SensorGnssSpectrum__are_equal(const px4_msgs__msg__SensorGnssSpectrum * lhs, const px4_msgs__msg__SensorGnssSpectrum * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // timestamp
  if (lhs->timestamp != rhs->timestamp) {
    return false;
  }
  // timestamp_sample
  if (lhs->timestamp_sample != rhs->timestamp_sample) {
    return false;
  }
  // device_id
  if (lhs->device_id != rhs->device_id) {
    return false;
  }
  // block_id
  if (lhs->block_id != rhs->block_id) {
    return false;
  }
  // spectrum
  for (size_t i = 0; i < 256; ++i) {
    if (lhs->spectrum[i] != rhs->spectrum[i]) {
      return false;
    }
  }
  // spectrum_span
  if (lhs->spectrum_span != rhs->spectrum_span) {
    return false;
  }
  // resolution
  if (lhs->resolution != rhs->resolution) {
    return false;
  }
  // center_frequency
  if (lhs->center_frequency != rhs->center_frequency) {
    return false;
  }
  // programmable_gain_amplifier
  if (lhs->programmable_gain_amplifier != rhs->programmable_gain_amplifier) {
    return false;
  }
  return true;
}

bool
px4_msgs__msg__SensorGnssSpectrum__copy(
  const px4_msgs__msg__SensorGnssSpectrum * input,
  px4_msgs__msg__SensorGnssSpectrum * output)
{
  if (!input || !output) {
    return false;
  }
  // timestamp
  output->timestamp = input->timestamp;
  // timestamp_sample
  output->timestamp_sample = input->timestamp_sample;
  // device_id
  output->device_id = input->device_id;
  // block_id
  output->block_id = input->block_id;
  // spectrum
  for (size_t i = 0; i < 256; ++i) {
    output->spectrum[i] = input->spectrum[i];
  }
  // spectrum_span
  output->spectrum_span = input->spectrum_span;
  // resolution
  output->resolution = input->resolution;
  // center_frequency
  output->center_frequency = input->center_frequency;
  // programmable_gain_amplifier
  output->programmable_gain_amplifier = input->programmable_gain_amplifier;
  return true;
}

px4_msgs__msg__SensorGnssSpectrum *
px4_msgs__msg__SensorGnssSpectrum__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGnssSpectrum * msg = (px4_msgs__msg__SensorGnssSpectrum *)allocator.allocate(sizeof(px4_msgs__msg__SensorGnssSpectrum), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(px4_msgs__msg__SensorGnssSpectrum));
  bool success = px4_msgs__msg__SensorGnssSpectrum__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
px4_msgs__msg__SensorGnssSpectrum__destroy(px4_msgs__msg__SensorGnssSpectrum * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    px4_msgs__msg__SensorGnssSpectrum__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
px4_msgs__msg__SensorGnssSpectrum__Sequence__init(px4_msgs__msg__SensorGnssSpectrum__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGnssSpectrum * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(px4_msgs__msg__SensorGnssSpectrum)) {
      return false;
    }
    data = (px4_msgs__msg__SensorGnssSpectrum *)allocator.zero_allocate(size, sizeof(px4_msgs__msg__SensorGnssSpectrum), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = px4_msgs__msg__SensorGnssSpectrum__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        px4_msgs__msg__SensorGnssSpectrum__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
px4_msgs__msg__SensorGnssSpectrum__Sequence__fini(px4_msgs__msg__SensorGnssSpectrum__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      px4_msgs__msg__SensorGnssSpectrum__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

px4_msgs__msg__SensorGnssSpectrum__Sequence *
px4_msgs__msg__SensorGnssSpectrum__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGnssSpectrum__Sequence * array = (px4_msgs__msg__SensorGnssSpectrum__Sequence *)allocator.allocate(sizeof(px4_msgs__msg__SensorGnssSpectrum__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = px4_msgs__msg__SensorGnssSpectrum__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
px4_msgs__msg__SensorGnssSpectrum__Sequence__destroy(px4_msgs__msg__SensorGnssSpectrum__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    px4_msgs__msg__SensorGnssSpectrum__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
px4_msgs__msg__SensorGnssSpectrum__Sequence__are_equal(const px4_msgs__msg__SensorGnssSpectrum__Sequence * lhs, const px4_msgs__msg__SensorGnssSpectrum__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!px4_msgs__msg__SensorGnssSpectrum__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__SensorGnssSpectrum__Sequence__copy(
  const px4_msgs__msg__SensorGnssSpectrum__Sequence * input,
  px4_msgs__msg__SensorGnssSpectrum__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(px4_msgs__msg__SensorGnssSpectrum)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(px4_msgs__msg__SensorGnssSpectrum);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    px4_msgs__msg__SensorGnssSpectrum * data =
      (px4_msgs__msg__SensorGnssSpectrum *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!px4_msgs__msg__SensorGnssSpectrum__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          px4_msgs__msg__SensorGnssSpectrum__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!px4_msgs__msg__SensorGnssSpectrum__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
