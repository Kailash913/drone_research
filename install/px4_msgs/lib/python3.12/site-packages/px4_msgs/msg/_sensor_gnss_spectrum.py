# generated from rosidl_generator_py/resource/_idl.py.em
# with input from px4_msgs:msg/SensorGnssSpectrum.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

# Member 'spectrum'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SensorGnssSpectrum(type):
    """Metaclass of message 'SensorGnssSpectrum'."""

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
                'px4_msgs.msg.SensorGnssSpectrum')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__sensor_gnss_spectrum
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__sensor_gnss_spectrum
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__sensor_gnss_spectrum
            cls._TYPE_SUPPORT = module.type_support_msg__msg__sensor_gnss_spectrum
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__sensor_gnss_spectrum

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SensorGnssSpectrum(metaclass=Metaclass_SensorGnssSpectrum):
    """Message class 'SensorGnssSpectrum'."""

    __slots__ = [
        '_timestamp',
        '_timestamp_sample',
        '_device_id',
        '_block_id',
        '_spectrum',
        '_spectrum_span',
        '_resolution',
        '_center_frequency',
        '_programmable_gain_amplifier',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'timestamp': 'uint64',
        'timestamp_sample': 'uint64',
        'device_id': 'uint32',
        'block_id': 'uint8',
        'spectrum': 'uint8[256]',
        'spectrum_span': 'uint32',
        'resolution': 'uint32',
        'center_frequency': 'uint32',
        'programmable_gain_amplifier': 'uint8',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint8'), 256),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
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
        self.block_id = kwargs.get('block_id', int())
        if 'spectrum' not in kwargs:
            self.spectrum = numpy.zeros(256, dtype=numpy.uint8)
        else:
            self.spectrum = kwargs.get('spectrum')
        self.spectrum_span = kwargs.get('spectrum_span', int())
        self.resolution = kwargs.get('resolution', int())
        self.center_frequency = kwargs.get('center_frequency', int())
        self.programmable_gain_amplifier = kwargs.get('programmable_gain_amplifier', int())

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
        if self.block_id != other.block_id:
            return False
        if any(self.spectrum != other.spectrum):
            return False
        if self.spectrum_span != other.spectrum_span:
            return False
        if self.resolution != other.resolution:
            return False
        if self.center_frequency != other.center_frequency:
            return False
        if self.programmable_gain_amplifier != other.programmable_gain_amplifier:
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
    def block_id(self):
        """Message field 'block_id'."""
        return self._block_id

    @block_id.setter
    def block_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'block_id' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'block_id' field must be an unsigned integer in [0, 255]"
        self._block_id = value

    @builtins.property
    def spectrum(self):
        """Message field 'spectrum'."""
        return self._spectrum

    @spectrum.setter
    def spectrum(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.uint8, \
                    "The 'spectrum' numpy.ndarray() must have the dtype of 'numpy.uint8'"
                assert value.size == 256, \
                    "The 'spectrum' numpy.ndarray() must have a size of 256"
                self._spectrum = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 256 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'spectrum' field must be a set or sequence with length 256 and each value of type 'int' and each unsigned integer in [0, 255]"
        self._spectrum = numpy.array(value, dtype=numpy.uint8)

    @builtins.property
    def spectrum_span(self):
        """Message field 'spectrum_span'."""
        return self._spectrum_span

    @spectrum_span.setter
    def spectrum_span(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'spectrum_span' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'spectrum_span' field must be an unsigned integer in [0, 4294967295]"
        self._spectrum_span = value

    @builtins.property
    def resolution(self):
        """Message field 'resolution'."""
        return self._resolution

    @resolution.setter
    def resolution(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'resolution' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'resolution' field must be an unsigned integer in [0, 4294967295]"
        self._resolution = value

    @builtins.property
    def center_frequency(self):
        """Message field 'center_frequency'."""
        return self._center_frequency

    @center_frequency.setter
    def center_frequency(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'center_frequency' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'center_frequency' field must be an unsigned integer in [0, 4294967295]"
        self._center_frequency = value

    @builtins.property
    def programmable_gain_amplifier(self):
        """Message field 'programmable_gain_amplifier'."""
        return self._programmable_gain_amplifier

    @programmable_gain_amplifier.setter
    def programmable_gain_amplifier(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'programmable_gain_amplifier' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'programmable_gain_amplifier' field must be an unsigned integer in [0, 255]"
        self._programmable_gain_amplifier = value
