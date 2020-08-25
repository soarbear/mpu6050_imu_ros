//=================================================================================================
// Copyright (c) 2014, Christian Rose, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Simulation, Systems Optimization and Robotics
//       group, TU Darmstadt nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/Imu.h>

ros::Publisher imuPub_;
ros::Publisher posePub_;

geometry_msgs::PoseStamped pose_msg;

sensor_msgs::Imu imu_msg;

void quaternionCb(const geometry_msgs::Quaternion::ConstPtr& msg){

  bool pose_subscribed = (posePub_.getNumSubscribers() > 0);
  bool imu_subscribed  = (imuPub_.getNumSubscribers() > 0);

  if (pose_subscribed || imu_subscribed){

    //@TODO make time offset param
    ros::Time sensor_data_time = ros::Time::now() - ros::Duration(0.002);

    if (imu_subscribed){
      imu_msg.header.stamp = sensor_data_time;

      imu_msg.orientation = *msg;

      imuPub_.publish(imu_msg);
    }

    if (pose_subscribed){
      pose_msg.header.stamp = sensor_data_time;

      pose_msg.pose.orientation = *msg;

      posePub_.publish(pose_msg);
    }
  }
}

int main(int argc, char** argv){

    ros::init(argc, argv, "mpu6050_imu_converter");

    ros::NodeHandle _nh;
    ros::NodeHandle _pnh("~");

    double linear_acceleration_stdev, angular_velocity_stdev;
    std::string frame_id;
    std::string frame_id2;

    ros::param::param<double>("~linear_acceleration_stdev", linear_acceleration_stdev, 0.06);
    ros::param::param<double>("~angular_velocity_stdev", angular_velocity_stdev, 0.005);
    ros::param::param<std::string>("~frame_id", frame_id, std::string("imu_link"));

    double linear_acceleration_cov = linear_acceleration_stdev * linear_acceleration_stdev;
    double angular_velocity_cov = angular_velocity_stdev * angular_velocity_stdev;


    imu_msg.header.frame_id = frame_id;
    pose_msg.header.frame_id = frame_id;

    imu_msg.orientation_covariance[0] = 0.1;
    imu_msg.orientation_covariance[4] = 0.1;
    imu_msg.orientation_covariance[8] = 0.1;


    // Angular velocity entries are not filled, so set to -1.0
    imu_msg.angular_velocity_covariance[0] = 0.0; //angular_velocity_cov;
    imu_msg.angular_velocity_covariance[4] = angular_velocity_cov;
    imu_msg.angular_velocity_covariance[8] = angular_velocity_cov;

    // Linear acceleration entries are not filled, so set to -1.0
    imu_msg.linear_acceleration_covariance[0] = 0.0;
    imu_msg.linear_acceleration_covariance[4] = linear_acceleration_cov;
    imu_msg.linear_acceleration_covariance[8] = linear_acceleration_cov;

    posePub_ = _pnh.advertise<geometry_msgs::PoseStamped>("pose", 10);
    imuPub_ = _pnh.advertise<sensor_msgs::Imu>("imu", 10);

    ros::Subscriber quatSub_ = _nh.subscribe("quaternion", 10, quaternionCb);

    ros::spin();

    return(0);
}

