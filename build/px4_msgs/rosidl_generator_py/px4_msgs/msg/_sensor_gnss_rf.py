# generated from rosidl_generator_py/resource/_idl.py.em
# with input from px4_msgs:msg/SensorGnssRf.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SensorGnssRf(type):
    """Metaclass of message 'SensorGnssRf'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'ANTENNA_STATUS_INIT': 0,
        'ANTENNA_STATUS_UNKNOWN': 1,
        'ANTENNA_STATUS_OK': 2,
        'ANTENNA_STATUS_SHORT': 3,
        'ANTENNA_STATUS_OPEN': 4,
        'ANTENNA_POWER_OFF': 0,
        'ANTENNA_POWER_ON': 1,
        'ANTENNA_POWER_UNKNOWN': 2,
        'JAMMING_STATE_UNKNOWN': 0,
        'JAMMING_STATE_OK': 1,
        'JAMMING_STATE_WARNING': 2,
        'JAMMING_STATE_CRITICAL': 3,
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
                'px4_msgs.msg.SensorGnssRf')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__sensor_gnss_rf
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__sensor_gnss_rf
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__sensor_gnss_rf
            cls._TYPE_SUPPORT = module.type_support_msg__msg__sensor_gnss_rf
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__sensor_gnss_rf

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'ANTENNA_STATUS_INIT': cls.__constants['ANTENNA_STATUS_INIT'],
            'ANTENNA_STATUS_UNKNOWN': cls.__constants['ANTENNA_STATUS_UNKNOWN'],
            'ANTENNA_STATUS_OK': cls.__constants['ANTENNA_STATUS_OK'],
            'ANTENNA_STATUS_SHORT': cls.__constants['ANTENNA_STATUS_SHORT'],
            'ANTENNA_STATUS_OPEN': cls.__constants['ANTENNA_STATUS_OPEN'],
            'ANTENNA_POWER_OFF': cls.__constants['ANTENNA_POWER_OFF'],
            'ANTENNA_POWER_ON': cls.__constants['ANTENNA_POWER_ON'],
            'ANTENNA_POWER_UNKNOWN': cls.__constants['ANTENNA_POWER_UNKNOWN'],
            'JAMMING_STATE_UNKNOWN': cls.__constants['JAMMING_STATE_UNKNOWN'],
            'JAMMING_STATE_OK': cls.__constants['JAMMING_STATE_OK'],
            'JAMMING_STATE_WARNING': cls.__constants['JAMMING_STATE_WARNING'],
            'JAMMING_STATE_CRITICAL': cls.__constants['JAMMING_STATE_CRITICAL'],
        }

    @property
    def ANTENNA_STATUS_INIT(self):
        """Message constant 'ANTENNA_STATUS_INIT'."""
        return Metaclass_SensorGnssRf.__constants['ANTENNA_STATUS_INIT']

    @property
    def ANTENNA_STATUS_UNKNOWN(self):
        """Message constant 'ANTENNA_STATUS_UNKNOWN'."""
        return Metaclass_SensorGnssRf.__constants['ANTENNA_STATUS_UNKNOWN']

    @property
    def ANTENNA_STATUS_OK(self):
        """Message constant 'ANTENNA_STATUS_OK'."""
        return Metaclass_SensorGnssRf.__constants['ANTENNA_STATUS_OK']

    @property
    def ANTENNA_STATUS_SHORT(self):
        """Message constant 'ANTENNA_STATUS_SHORT'."""
        return Metaclass_SensorGnssRf.__constants['ANTENNA_STATUS_SHORT']

    @property
    def ANTENNA_STATUS_OPEN(self):
        """Message constant 'ANTENNA_STATUS_OPEN'."""
        return Metaclass_SensorGnssRf.__constants['ANTENNA_STATUS_OPEN']

    @property
    def ANTENNA_POWER_OFF(self):
        """Message constant 'ANTENNA_POWER_OFF'."""
        return Metaclass_SensorGnssRf.__constants['ANTENNA_POWER_OFF']

    @property
    def ANTENNA_POWER_ON(self):
        """Message constant 'ANTENNA_POWER_ON'."""
        return Metaclass_SensorGnssRf.__constants['ANTENNA_POWER_ON']

    @property
    def ANTENNA_POWER_UNKNOWN(self):
        """Message constant 'ANTENNA_POWER_UNKNOWN'."""
        return Metaclass_SensorGnssRf.__constants['ANTENNA_POWER_UNKNOWN']

    @property
    def JAMMING_STATE_UNKNOWN(self):
        """Message constant 'JAMMING_STATE_UNKNOWN'."""
        return Metaclass_SensorGnssRf.__constants['JAMMING_STATE_UNKNOWN']

    @property
    def JAMMING_STATE_OK(self):
        """Message constant 'JAMMING_STATE_OK'."""
        return Metaclass_SensorGnssRf.__constants['JAMMING_STATE_OK']

    @property
    def JAMMING_STATE_WARNING(self):
        """Message constant 'JAMMING_STATE_WARNING'."""
        return Metaclass_SensorGnssRf.__constants['JAMMING_STATE_WARNING']

    @property
    def JAMMING_STATE_CRITICAL(self):
        """Message constant 'JAMMING_STATE_CRITICAL'."""
        return Metaclass_SensorGnssRf.__constants['JAMMING_STATE_CRITICAL']


class SensorGnssRf(metaclass=Metaclass_SensorGnssRf):
    """
    Message class 'SensorGnssRf'.

    Constants:
      ANTENNA_STATUS_INIT
      ANTENNA_STATUS_UNKNOWN
      ANTENNA_STATUS_OK
      ANTENNA_STATUS_SHORT
      ANTENNA_STATUS_OPEN
      ANTENNA_POWER_OFF
      ANTENNA_POWER_ON
      ANTENNA_POWER_UNKNOWN
      JAMMING_STATE_UNKNOWN
      JAMMING_STATE_OK
      JAMMING_STATE_WARNING
      JAMMING_STATE_CRITICAL
    """

    __slots__ = [
        '_timestamp',
        '_timestamp_sample',
        '_device_id',
        '_block_id',
        '_antenna_status',
        '_antenna_power',
        '_post_status',
        '_noise_per_ms',
        '_automatic_gain_control',
        '_jamming_indicator',
        '_jamming_state',
        '_i_offset',
        '_i_magnitude',
        '_q_offset',
        '_q_magnitude',
        '_center_frequency',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'timestamp': 'uint64',
        'timestamp_sample': 'uint64',
        'device_id': 'uint32',
        'block_id': 'uint8',
        'antenna_status': 'uint8',
        'antenna_power': 'uint8',
        'post_status': 'uint32',
        'noise_per_ms': 'uint16',
        'automatic_gain_control': 'uint16',
        'jamming_indicator': 'uint8',
        'jamming_state': 'uint8',
        'i_offset': 'int8',
        'i_magnitude': 'uint8',
        'q_offset': 'int8',
        'q_magnitude': 'uint8',
        'center_frequency': 'uint32',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
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
        self.antenna_status = kwargs.get('antenna_status', int())
        self.antenna_power = kwargs.get('antenna_power', int())
        self.post_status = kwargs.get('post_status', int())
        self.noise_per_ms = kwargs.get('noise_per_ms', int())
        self.automatic_gain_control = kwargs.get('automatic_gain_control', int())
        self.jamming_indicator = kwargs.get('jamming_indicator', int())
        self.jamming_state = kwargs.get('jamming_state', int())
        self.i_offset = kwargs.get('i_offset', int())
        self.i_magnitude = kwargs.get('i_magnitude', int())
        self.q_offset = kwargs.get('q_offset', int())
        self.q_magnitude = kwargs.get('q_magnitude', int())
        self.center_frequency = kwargs.get('center_frequency', int())

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
        if self.antenna_status != other.antenna_status:
            return False
        if self.antenna_power != other.antenna_power:
            return False
        if self.post_status != other.post_status:
            return False
        if self.noise_per_ms != other.noise_per_ms:
            return False
        if self.automatic_gain_control != other.automatic_gain_control:
            return False
        if self.jamming_indicator != other.jamming_indicator:
            return False
        if self.jamming_state != other.jamming_state:
            return False
        if self.i_offset != other.i_offset:
            return False
        if self.i_magnitude != other.i_magnitude:
            return False
        if self.q_offset != other.q_offset:
            return False
        if self.q_magnitude != other.q_magnitude:
            return False
        if self.center_frequency != other.center_frequency:
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
    def antenna_status(self):
        """Message field 'antenna_status'."""
        return self._antenna_status

    @antenna_status.setter
    def antenna_status(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'antenna_status' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'antenna_status' field must be an unsigned integer in [0, 255]"
        self._antenna_status = value

    @builtins.property
    def antenna_power(self):
        """Message field 'antenna_power'."""
        return self._antenna_power

    @antenna_power.setter
    def antenna_power(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'antenna_power' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'antenna_power' field must be an unsigned integer in [0, 255]"
        self._antenna_power = value

    @builtins.property
    def post_status(self):
        """Message field 'post_status'."""
        return self._post_status

    @post_status.setter
    def post_status(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'post_status' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'post_status' field must be an unsigned integer in [0, 4294967295]"
        self._post_status = value

    @builtins.property
    def noise_per_ms(self):
        """Message field 'noise_per_ms'."""
        return self._noise_per_ms

    @noise_per_ms.setter
    def noise_per_ms(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'noise_per_ms' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'noise_per_ms' field must be an unsigned integer in [0, 65535]"
        self._noise_per_ms = value

    @builtins.property
    def automatic_gain_control(self):
        """Message field 'automatic_gain_control'."""
        return self._automatic_gain_control

    @automatic_gain_control.setter
    def automatic_gain_control(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'automatic_gain_control' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'automatic_gain_control' field must be an unsigned integer in [0, 65535]"
        self._automatic_gain_control = value

    @builtins.property
    def jamming_indicator(self):
        """Message field 'jamming_indicator'."""
        return self._jamming_indicator

    @jamming_indicator.setter
    def jamming_indicator(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'jamming_indicator' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'jamming_indicator' field must be an unsigned integer in [0, 255]"
        self._jamming_indicator = value

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
    def i_offset(self):
        """Message field 'i_offset'."""
        return self._i_offset

    @i_offset.setter
    def i_offset(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'i_offset' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'i_offset' field must be an integer in [-128, 127]"
        self._i_offset = value

    @builtins.property
    def i_magnitude(self):
        """Message field 'i_magnitude'."""
        return self._i_magnitude

    @i_magnitude.setter
    def i_magnitude(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'i_magnitude' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'i_magnitude' field must be an unsigned integer in [0, 255]"
        self._i_magnitude = value

    @builtins.property
    def q_offset(self):
        """Message field 'q_offset'."""
        return self._q_offset

    @q_offset.setter
    def q_offset(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'q_offset' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'q_offset' field must be an integer in [-128, 127]"
        self._q_offset = value

    @builtins.property
    def q_magnitude(self):
        """Message field 'q_magnitude'."""
        return self._q_magnitude

    @q_magnitude.setter
    def q_magnitude(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'q_magnitude' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'q_magnitude' field must be an unsigned integer in [0, 255]"
        self._q_magnitude = value

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
