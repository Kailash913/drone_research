// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from px4_msgs:msg/SensorGnss.idl
// generated code does not contain a copyright notice
#include "px4_msgs/msg/detail/sensor_gnss__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
px4_msgs__msg__SensorGnss__init(px4_msgs__msg__SensorGnss * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  // timestamp_sample
  // device_id
  // latitude
  // longitude
  // altitude_msl
  // altitude_ellipsoid
  // speed_accuracy
  // course_accuracy
  // fix_type
  // eph
  // epv
  // hdop
  // vdop
  // noise
  // automatic_gain_control
  // jamming_state
  // jamming_indicator
  // spoofing_state
  // authentication_state
  // ground_speed
  // vel_north
  // vel_east
  // vel_down
  // course
  // vel_ned_valid
  // timestamp_time_relative
  // time_utc_usec
  // satellites_used
  // system_error
  // rtcm_injection_rate
  // selected_rtcm_instance
  // corrections_protocol
  // corrections_crc_failed
  // corrections_msg_used
  return true;
}

void
px4_msgs__msg__SensorGnss__fini(px4_msgs__msg__SensorGnss * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  // timestamp_sample
  // device_id
  // latitude
  // longitude
  // altitude_msl
  // altitude_ellipsoid
  // speed_accuracy
  // course_accuracy
  // fix_type
  // eph
  // epv
  // hdop
  // vdop
  // noise
  // automatic_gain_control
  // jamming_state
  // jamming_indicator
  // spoofing_state
  // authentication_state
  // ground_speed
  // vel_north
  // vel_east
  // vel_down
  // course
  // vel_ned_valid
  // timestamp_time_relative
  // time_utc_usec
  // satellites_used
  // system_error
  // rtcm_injection_rate
  // selected_rtcm_instance
  // corrections_protocol
  // corrections_crc_failed
  // corrections_msg_used
}

bool
px4_msgs__msg__SensorGnss__are_equal(const px4_msgs__msg__SensorGnss * lhs, const px4_msgs__msg__SensorGnss * rhs)
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
  // latitude
  if (lhs->latitude != rhs->latitude) {
    return false;
  }
  // longitude
  if (lhs->longitude != rhs->longitude) {
    return false;
  }
  // altitude_msl
  if (lhs->altitude_msl != rhs->altitude_msl) {
    return false;
  }
  // altitude_ellipsoid
  if (lhs->altitude_ellipsoid != rhs->altitude_ellipsoid) {
    return false;
  }
  // speed_accuracy
  if (lhs->speed_accuracy != rhs->speed_accuracy) {
    return false;
  }
  // course_accuracy
  if (lhs->course_accuracy != rhs->course_accuracy) {
    return false;
  }
  // fix_type
  if (lhs->fix_type != rhs->fix_type) {
    return false;
  }
  // eph
  if (lhs->eph != rhs->eph) {
    return false;
  }
  // epv
  if (lhs->epv != rhs->epv) {
    return false;
  }
  // hdop
  if (lhs->hdop != rhs->hdop) {
    return false;
  }
  // vdop
  if (lhs->vdop != rhs->vdop) {
    return false;
  }
  // noise
  if (lhs->noise != rhs->noise) {
    return false;
  }
  // automatic_gain_control
  if (lhs->automatic_gain_control != rhs->automatic_gain_control) {
    return false;
  }
  // jamming_state
  if (lhs->jamming_state != rhs->jamming_state) {
    return false;
  }
  // jamming_indicator
  if (lhs->jamming_indicator != rhs->jamming_indicator) {
    return false;
  }
  // spoofing_state
  if (lhs->spoofing_state != rhs->spoofing_state) {
    return false;
  }
  // authentication_state
  if (lhs->authentication_state != rhs->authentication_state) {
    return false;
  }
  // ground_speed
  if (lhs->ground_speed != rhs->ground_speed) {
    return false;
  }
  // vel_north
  if (lhs->vel_north != rhs->vel_north) {
    return false;
  }
  // vel_east
  if (lhs->vel_east != rhs->vel_east) {
    return false;
  }
  // vel_down
  if (lhs->vel_down != rhs->vel_down) {
    return false;
  }
  // course
  if (lhs->course != rhs->course) {
    return false;
  }
  // vel_ned_valid
  if (lhs->vel_ned_valid != rhs->vel_ned_valid) {
    return false;
  }
  // timestamp_time_relative
  if (lhs->timestamp_time_relative != rhs->timestamp_time_relative) {
    return false;
  }
  // time_utc_usec
  if (lhs->time_utc_usec != rhs->time_utc_usec) {
    return false;
  }
  // satellites_used
  if (lhs->satellites_used != rhs->satellites_used) {
    return false;
  }
  // system_error
  if (lhs->system_error != rhs->system_error) {
    return false;
  }
  // rtcm_injection_rate
  if (lhs->rtcm_injection_rate != rhs->rtcm_injection_rate) {
    return false;
  }
  // selected_rtcm_instance
  if (lhs->selected_rtcm_instance != rhs->selected_rtcm_instance) {
    return false;
  }
  // corrections_protocol
  if (lhs->corrections_protocol != rhs->corrections_protocol) {
    return false;
  }
  // corrections_crc_failed
  if (lhs->corrections_crc_failed != rhs->corrections_crc_failed) {
    return false;
  }
  // corrections_msg_used
  if (lhs->corrections_msg_used != rhs->corrections_msg_used) {
    return false;
  }
  return true;
}

bool
px4_msgs__msg__SensorGnss__copy(
  const px4_msgs__msg__SensorGnss * input,
  px4_msgs__msg__SensorGnss * output)
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
  // latitude
  output->latitude = input->latitude;
  // longitude
  output->longitude = input->longitude;
  // altitude_msl
  output->altitude_msl = input->altitude_msl;
  // altitude_ellipsoid
  output->altitude_ellipsoid = input->altitude_ellipsoid;
  // speed_accuracy
  output->speed_accuracy = input->speed_accuracy;
  // course_accuracy
  output->course_accuracy = input->course_accuracy;
  // fix_type
  output->fix_type = input->fix_type;
  // eph
  output->eph = input->eph;
  // epv
  output->epv = input->epv;
  // hdop
  output->hdop = input->hdop;
  // vdop
  output->vdop = input->vdop;
  // noise
  output->noise = input->noise;
  // automatic_gain_control
  output->automatic_gain_control = input->automatic_gain_control;
  // jamming_state
  output->jamming_state = input->jamming_state;
  // jamming_indicator
  output->jamming_indicator = input->jamming_indicator;
  // spoofing_state
  output->spoofing_state = input->spoofing_state;
  // authentication_state
  output->authentication_state = input->authentication_state;
  // ground_speed
  output->ground_speed = input->ground_speed;
  // vel_north
  output->vel_north = input->vel_north;
  // vel_east
  output->vel_east = input->vel_east;
  // vel_down
  output->vel_down = input->vel_down;
  // course
  output->course = input->course;
  // vel_ned_valid
  output->vel_ned_valid = input->vel_ned_valid;
  // timestamp_time_relative
  output->timestamp_time_relative = input->timestamp_time_relative;
  // time_utc_usec
  output->time_utc_usec = input->time_utc_usec;
  // satellites_used
  output->satellites_used = input->satellites_used;
  // system_error
  output->system_error = input->system_error;
  // rtcm_injection_rate
  output->rtcm_injection_rate = input->rtcm_injection_rate;
  // selected_rtcm_instance
  output->selected_rtcm_instance = input->selected_rtcm_instance;
  // corrections_protocol
  output->corrections_protocol = input->corrections_protocol;
  // corrections_crc_failed
  output->corrections_crc_failed = input->corrections_crc_failed;
  // corrections_msg_used
  output->corrections_msg_used = input->corrections_msg_used;
  return true;
}

px4_msgs__msg__SensorGnss *
px4_msgs__msg__SensorGnss__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGnss * msg = (px4_msgs__msg__SensorGnss *)allocator.allocate(sizeof(px4_msgs__msg__SensorGnss), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(px4_msgs__msg__SensorGnss));
  bool success = px4_msgs__msg__SensorGnss__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
px4_msgs__msg__SensorGnss__destroy(px4_msgs__msg__SensorGnss * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    px4_msgs__msg__SensorGnss__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
px4_msgs__msg__SensorGnss__Sequence__init(px4_msgs__msg__SensorGnss__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGnss * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(px4_msgs__msg__SensorGnss)) {
      return false;
    }
    data = (px4_msgs__msg__SensorGnss *)allocator.zero_allocate(size, sizeof(px4_msgs__msg__SensorGnss), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = px4_msgs__msg__SensorGnss__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        px4_msgs__msg__SensorGnss__fini(&data[i - 1]);
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
px4_msgs__msg__SensorGnss__Sequence__fini(px4_msgs__msg__SensorGnss__Sequence * array)
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
      px4_msgs__msg__SensorGnss__fini(&array->data[i]);
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

px4_msgs__msg__SensorGnss__Sequence *
px4_msgs__msg__SensorGnss__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGnss__Sequence * array = (px4_msgs__msg__SensorGnss__Sequence *)allocator.allocate(sizeof(px4_msgs__msg__SensorGnss__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = px4_msgs__msg__SensorGnss__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
px4_msgs__msg__SensorGnss__Sequence__destroy(px4_msgs__msg__SensorGnss__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    px4_msgs__msg__SensorGnss__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
px4_msgs__msg__SensorGnss__Sequence__are_equal(const px4_msgs__msg__SensorGnss__Sequence * lhs, const px4_msgs__msg__SensorGnss__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!px4_msgs__msg__SensorGnss__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__SensorGnss__Sequence__copy(
  const px4_msgs__msg__SensorGnss__Sequence * input,
  px4_msgs__msg__SensorGnss__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(px4_msgs__msg__SensorGnss)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(px4_msgs__msg__SensorGnss);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    px4_msgs__msg__SensorGnss * data =
      (px4_msgs__msg__SensorGnss *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!px4_msgs__msg__SensorGnss__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          px4_msgs__msg__SensorGnss__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!px4_msgs__msg__SensorGnss__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
