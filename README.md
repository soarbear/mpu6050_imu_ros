# mpu6050_imu_ros

Arduino code(mpu6050_imu_driver/firmaware) employing rosserial to retrieve a quaternion from the mpu6050 DMP. 

Then, another ROS node(mpu6050_imu_converter) publishing IMU & Pose messages to ROS. 

The package is tested on Arduino Uno compatible & Asus Tinker board(Raspiberry Pi or PC maybe OK).

# Test Environment

・MPU-6050 GY521

・DFRobot Romeo mini v1.1(or Arduino UNO compatible etc)

・ROS kinetic(or melodic)

・Ubuntu 18.04 Tinker board(or Raspiberry Pi, PC etc)

# Demo

$roslaunch mpu6050_imu_driver mpu6050_imu.launch

Video on youtube -> https://youtu.be/h508BTedKtk

# Explanation

<a href="https://memo.soarcloud.com/mpu6050%e3%82%92%e3%83%ad%e3%83%9c%e3%83%83%e3%83%88%e3%81%ab%e7%b5%84%e3%81%bf%e8%be%bc%e3%82%82%e3%81%86/">Explained in Japanese</a>

# Reference

<a href="https://github.com/jrowberg/i2cdevlib">jrowberg/i2cdevlib</a>

# Todo

Optimization
