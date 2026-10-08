# generated from rosidl_generator_py/resource/_idl.py.em
# with input from px4_msgs:msg/VehicleGnssHeading.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_VehicleGnssHeading(type):
    """Metaclass of message 'VehicleGnssHeading'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('px4_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'px4_msgs.msg.VehicleGnssHeading')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__vehicle_gnss_heading
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__vehicle_gnss_heading
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__vehicle_gnss_heading
            cls._TYPE_SUPPORT = module.type_support_msg__msg__vehicle_gnss_heading
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__vehicle_gnss_heading

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class VehicleGnssHeading(metaclass=Metaclass_VehicleGnssHeading):
    """Message class 'VehicleGnssHeading'."""

    __slots__ = [
        '_timestamp',
        '_timestamp_sample',
        '_device_id',
        '_heading',
        '_heading_accuracy',
        '_heading_offset',
        '_baseline_length',
        '_jamming_state',
        '_spoofing_state',
        '_usable',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'timestamp': 'uint64',
        'timestamp_sample': 'uint64',
        'device_id': 'uint32',
        'heading': 'float',
        'heading_accuracy': 'float',
        'heading_offset': 'float',
        'baseline_length': 'float',
        'jamming_state': 'uint8',
        'spoofing_state': 'uint8',
        'usable': 'boolean',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.timestamp = kwargs.get('timestamp', int())
        self.timestamp_sample = kwargs.get('timestamp_sample', int())
        self.device_id = kwargs.get('device_id', int())
        self.heading = kwargs.get('heading', float())
        self.heading_accuracy = kwargs.get('heading_accuracy', float())
        self.heading_offset = kwargs.get('heading_offset', float())
        self.baseline_length = kwargs.get('baseline_length', float())
        self.jamming_state = kwargs.get('jamming_state', int())
        self.spoofing_state = kwargs.get('spoofing_state', int())
        self.usable = kwargs.get('usable', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.timestamp != other.timestamp:
            return False
        if self.timestamp_sample != other.timestamp_sample:
            return False
        if self.device_id != other.device_id:
            return False
        if self.heading != other.heading:
            return False
        if self.heading_accuracy != other.heading_accuracy:
            return False
        if self.heading_offset != other.heading_offset:
            return False
        if self.baseline_length != other.baseline_length:
            return False
        if self.jamming_state != other.jamming_state:
            return False
        if self.spoofing_state != other.spoofing_state:
            return False
        if self.usable != other.usable:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def timestamp(self):
        """Message field 'timestamp'."""
        return self._timestamp

    @timestamp.setter
    def timestamp(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'timestamp' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timestamp' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timestamp = value

    @builtins.property
    def timestamp_sample(self):
        """Message field 'timestamp_sample'."""
        return self._timestamp_sample

    @timestamp_sample.setter
    def timestamp_sample(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'timestamp_sample' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timestamp_sample' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timestamp_sample = value

    @builtins.property
    def device_id(self):
        """Message field 'device_id'."""
        return self._device_id

    @device_id.setter
    def device_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'device_id' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'device_id' field must be an unsigned integer in [0, 4294967295]"
        self._device_id = value

    @builtins.property
    def heading(self):
        """Message field 'heading'."""
        return self._heading

    @heading.setter
    def heading(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'heading' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'heading' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._heading = value

    @builtins.property
    def heading_accuracy(self):
        """Message field 'heading_accuracy'."""
        return self._heading_accuracy

    @heading_accuracy.setter
    def heading_accuracy(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'heading_accuracy' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'heading_accuracy' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._heading_accuracy = value

    @builtins.property
    def heading_offset(self):
        """Message field 'heading_offset'."""
        return self._heading_offset

    @heading_offset.setter
    def heading_offset(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'heading_offset' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'heading_offset' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._heading_offset = value

    @builtins.property
    def baseline_length(self):
        """Message field 'baseline_length'."""
        return self._baseline_length

    @baseline_length.setter
    def baseline_length(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'baseline_length' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'baseline_length' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._baseline_length = value

    @builtins.property
    def jamming_state(self):
        """Message field 'jamming_state'."""
        return self._jamming_state

    @jamming_state.setter
    def jamming_state(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'jamming_state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'jamming_state' field must be an unsigned integer in [0, 255]"
        self._jamming_state = value

    @builtins.property
    def spoofing_state(self):
        """Message field 'spoofing_state'."""
        return self._spoofing_state

    @spoofing_state.setter
    def spoofing_state(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'spoofing_state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'spoofing_state' field must be an unsigned integer in [0, 255]"
        self._spoofing_state = value

    @builtins.property
    def usable(self):
        """Message field 'usable'."""
        return self._usable

    @usable.setter
    def usable(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'usable' field must be of type 'bool'"
        self._usable = value
