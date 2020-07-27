cmake_minimum_required(VERSION 2.8.3)
project(mpu6050_imu_converter)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  sensor_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES mpu6050_imu_converter
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)


## Declare a C++ executable
add_executable(mpu6050_imu_converter_node src/mpu6050_imu_converter_node.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(mpu6050_imu_converter_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(mpu6050_imu_converter_node
   ${catkin_LIBRARIES}
)


