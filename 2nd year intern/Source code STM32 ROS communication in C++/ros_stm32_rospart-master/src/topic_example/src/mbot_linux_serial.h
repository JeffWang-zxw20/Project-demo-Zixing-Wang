#ifndef MBOT_LINUX_SERIAL_H
#define MBOT_LINUX_SERIAL_H

#include <ros/ros.h>
#include <ros/time.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <boost/asio.hpp>
#include <geometry_msgs/Twist.h>

extern void serialInit();
extern void writeSpeed(double Left_v, double Right_v,unsigned char ctrlFlag);
extern bool readSpeed(double &Left_v,double &Right_v,double &Angle,unsigned char &ctrlFlag);
extern bool read_imu(double &Left_v,double &Right_v,double &Angle,
                     double &accx, double &accy, double &accz,
                      unsigned char &ctrlFlag);
extern bool read_imu_float(float &ggx,float &ggy,float &ggz,
                        float &aax, float &aay, float &aaz,
                        unsigned char &ctrlFlag);
unsigned char getCrc8(unsigned char *ptr, unsigned short len);

#endif
