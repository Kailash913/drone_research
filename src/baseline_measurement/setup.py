from setuptools import find_packages, setup

package_name = 'baseline_measurement'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        (
            'share/ament_index/resource_index/packages',
            ['resource/' + package_name]
        ),
        (
            'share/' + package_name,
            ['package.xml']
        ),
        ('share/' + package_name + '/config', ['config/baseline.yaml']),
    ],
    install_requires=['setuptools', 'psutil', 'PyYAML'],
    zip_safe=True,
    maintainer='kailash',
    maintainer_email='kailash@example.com',
    description='PX4 ROS2 baseline measurement node',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'baseline_node = baseline_measurement.baseline_node:main',
            'mission_node = baseline_measurement.mission_node:main',
        ],
    },
)
