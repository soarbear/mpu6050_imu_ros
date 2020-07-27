cmake_minimum_required(VERSION 2.8.3)
project(mpu6050_imu_driver)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  rosserial_arduino
  rosserial_client
  roscpp
  geometry_msgs
)

catkin_package(
)

rosserial_generate_ros_lib(
  PACKAGE rosserial_arduino
  SCRIPT make_libraries.py
)

#rosserial_configure_client(
# DIRECTORY firmware
#  TOOLCHAIN_FILE ${ROSSERIAL_ARDUINO_TOOLCHAIN}
#)

#rosserial_add_client_target(firmware mpu6050_imu ALL)
#rosserial_add_client_target(firmware mpu6050_imu-upload)
