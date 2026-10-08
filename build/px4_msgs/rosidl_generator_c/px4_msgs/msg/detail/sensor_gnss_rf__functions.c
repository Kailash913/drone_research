// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from px4_msgs:msg/SensorGnssRf.idl
// generated code does not contain a copyright notice
#include "px4_msgs/msg/detail/sensor_gnss_rf__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
px4_msgs__msg__SensorGnssRf__init(px4_msgs__msg__SensorGnssRf * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  // timestamp_sample
  // device_id
  // block_id
  // antenna_status
  // antenna_power
  // post_status
  // noise_per_ms
  // automatic_gain_control
  // jamming_indicator
  // jamming_state
  // i_offset
  // i_magnitude
  // q_offset
  // q_magnitude
  // center_frequency
  return true;
}

void
px4_msgs__msg__SensorGnssRf__fini(px4_msgs__msg__SensorGnssRf * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  // timestamp_sample
  // device_id
  // block_id
  // antenna_status
  // antenna_power
  // post_status
  // noise_per_ms
  // automatic_gain_control
  // jamming_indicator
  // jamming_state
  // i_offset
  // i_magnitude
  // q_offset
  // q_magnitude
  // center_frequency
}

bool
px4_msgs__msg__SensorGnssRf__are_equal(const px4_msgs__msg__SensorGnssRf * lhs, const px4_msgs__msg__SensorGnssRf * rhs)
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
  // antenna_status
  if (lhs->antenna_status != rhs->antenna_status) {
    return false;
  }
  // antenna_power
  if (lhs->antenna_power != rhs->antenna_power) {
    return false;
  }
  // post_status
  if (lhs->post_status != rhs->post_status) {
    return false;
  }
  // noise_per_ms
  if (lhs->noise_per_ms != rhs->noise_per_ms) {
    return false;
  }
  // automatic_gain_control
  if (lhs->automatic_gain_control != rhs->automatic_gain_control) {
    return false;
  }
  // jamming_indicator
  if (lhs->jamming_indicator != rhs->jamming_indicator) {
    return false;
  }
  // jamming_state
  if (lhs->jamming_state != rhs->jamming_state) {
    return false;
  }
  // i_offset
  if (lhs->i_offset != rhs->i_offset) {
    return false;
  }
  // i_magnitude
  if (lhs->i_magnitude != rhs->i_magnitude) {
    return false;
  }
  // q_offset
  if (lhs->q_offset != rhs->q_offset) {
    return false;
  }
  // q_magnitude
  if (lhs->q_magnitude != rhs->q_magnitude) {
    return false;
  }
  // center_frequency
  if (lhs->center_frequency != rhs->center_frequency) {
    return false;
  }
  return true;
}

bool
px4_msgs__msg__SensorGnssRf__copy(
  const px4_msgs__msg__SensorGnssRf * input,
  px4_msgs__msg__SensorGnssRf * output)
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
  // antenna_status
  output->antenna_status = input->antenna_status;
  // antenna_power
  output->antenna_power = input->antenna_power;
  // post_status
  output->post_status = input->post_status;
  // noise_per_ms
  output->noise_per_ms = input->noise_per_ms;
  // automatic_gain_control
  output->automatic_gain_control = input->automatic_gain_control;
  // jamming_indicator
  output->jamming_indicator = input->jamming_indicator;
  // jamming_state
  output->jamming_state = input->jamming_state;
  // i_offset
  output->i_offset = input->i_offset;
  // i_magnitude
  output->i_magnitude = input->i_magnitude;
  // q_offset
  output->q_offset = input->q_offset;
  // q_magnitude
  output->q_magnitude = input->q_magnitude;
  // center_frequency
  output->center_frequency = input->center_frequency;
  return true;
}

px4_msgs__msg__SensorGnssRf *
px4_msgs__msg__SensorGnssRf__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGnssRf * msg = (px4_msgs__msg__SensorGnssRf *)allocator.allocate(sizeof(px4_msgs__msg__SensorGnssRf), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(px4_msgs__msg__SensorGnssRf));
  bool success = px4_msgs__msg__SensorGnssRf__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
px4_msgs__msg__SensorGnssRf__destroy(px4_msgs__msg__SensorGnssRf * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    px4_msgs__msg__SensorGnssRf__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
px4_msgs__msg__SensorGnssRf__Sequence__init(px4_msgs__msg__SensorGnssRf__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGnssRf * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(px4_msgs__msg__SensorGnssRf)) {
      return false;
    }
    data = (px4_msgs__msg__SensorGnssRf *)allocator.zero_allocate(size, sizeof(px4_msgs__msg__SensorGnssRf), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = px4_msgs__msg__SensorGnssRf__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        px4_msgs__msg__SensorGnssRf__fini(&data[i - 1]);
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
px4_msgs__msg__SensorGnssRf__Sequence__fini(px4_msgs__msg__SensorGnssRf__Sequence * array)
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
      px4_msgs__msg__SensorGnssRf__fini(&array->data[i]);
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

px4_msgs__msg__SensorGnssRf__Sequence *
px4_msgs__msg__SensorGnssRf__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGnssRf__Sequence * array = (px4_msgs__msg__SensorGnssRf__Sequence *)allocator.allocate(sizeof(px4_msgs__msg__SensorGnssRf__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = px4_msgs__msg__SensorGnssRf__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
px4_msgs__msg__SensorGnssRf__Sequence__destroy(px4_msgs__msg__SensorGnssRf__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    px4_msgs__msg__SensorGnssRf__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
px4_msgs__msg__SensorGnssRf__Sequence__are_equal(const px4_msgs__msg__SensorGnssRf__Sequence * lhs, const px4_msgs__msg__SensorGnssRf__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!px4_msgs__msg__SensorGnssRf__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__SensorGnssRf__Sequence__copy(
  const px4_msgs__msg__SensorGnssRf__Sequence * input,
  px4_msgs__msg__SensorGnssRf__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(px4_msgs__msg__SensorGnssRf)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(px4_msgs__msg__SensorGnssRf);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    px4_msgs__msg__SensorGnssRf * data =
      (px4_msgs__msg__SensorGnssRf *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!px4_msgs__msg__SensorGnssRf__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          px4_msgs__msg__SensorGnssRf__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!px4_msgs__msg__SensorGnssRf__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
