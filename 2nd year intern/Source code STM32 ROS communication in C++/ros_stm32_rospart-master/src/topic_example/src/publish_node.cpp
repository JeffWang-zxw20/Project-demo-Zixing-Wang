
#include "ros/ros.h"
#include "std_msgs/String.h" //use data struct of std_msgs/String  
#include "mbot_linux_serial.h"
#include <sensor_msgs/Imu.h>  //Must have if want to send imu data

#include <sstream>


//-----------------------------ADD timestamp-----------------------------//


//-----------------------------ADD timestamp-----------------------------//



//test send value
double testSend1=1700.0;
double testSend2=1400.0;
unsigned char testSend3=0x07;

//test receive value
double testRece1=0.0;
double testRece2=0.0;
double testRece3=0.0;
double ax_=0.0;
double ay_=0.0;
double az_=0.0;
unsigned char testRece4=0x00;

//store float imu data
float gyrox = 0.0;
float gyroy = 0.0;
float gyroz = 0.0;
float accelmetorx = 0.0;
float accelmetory = 0.0;
float accelmetorz = 0.0;
unsigned char temperature=0x00;

int main(int agrc,char **argv)
{



    ros::init(agrc,argv,"public_node");
    ros::NodeHandle nh;

    ros::Rate loop_rate(200);
    ros::Publisher imu_pub = nh.advertise<sensor_msgs::Imu> ("imu_raw",3000); //(topic name, queue_size)
    //ros::Publisher chat_pub = nh.advertise<std_msgs::String>("chatter",1000);
    


    //串口初始化
    serialInit();

    ROS_INFO("Start publishing to ekf");
    int count = 0;
    while(ros::ok())
    {   

        //--------------------------TEST_PUBLISHER----------------------//
        // std_msgs::String msg;
        // std::stringstream ss;
        // ss<<"ei"<<count;
        // msg.data = ss.str();
        // chat_pub.publish(msg);
        // ++count;
        //--------------------------TEST_PUBLISHER----------------------//
        sensor_msgs::Imu imu;
        ros::spinOnce();
        // //向STM32端发送数据，前两个为double类型，最后一个为unsigned char类型
	    writeSpeed(testSend1,testSend2,testSend3);
        // //从STM32接收数据，输入参数依次转化为小车的线速度、角速度、航向角（角度）、预留控制位
	    // //readSpeed(testRece1,testRece2,testRece3,testRece4);
        // //read_imu(testRece1,testRece2,testRece3,ax_,ay_,az_,testRece4);
        read_imu_float(gyrox,gyroy,gyroz,accelmetorx,accelmetory,accelmetorz,temperature);
        // //打印数据
	    // //ROS_INFO("%f,%f,%f,%d\n",testRece1,testRece2,testRece3,ax,ay,az,testRece4);
        // //ROS_INFO("%f,%f,%f,%f,%f,%f,%d\n",testRece1,testRece2,testRece3,ax,ay,az,testRece4);
        // ROS_INFO("%f,%f,%f,%f,%f,%f,%d\n",gyrox,gyroy,gyroz,accelmetorx,accelmetory,accelmetorz,temperature);

        imu.header.stamp = ros::Time::now();
        imu.header.seq = 0; //consecutively increasing id???---- useless?deprecated?---will remove in ros2
        imu.header.frame_id = "frame_id";
        imu.orientation_covariance[0]=0;  //doesn't matter but possible bugs here.
        imu.angular_velocity.x = gyrox;
        imu.angular_velocity.y = gyroy;
        imu.angular_velocity.z = gyroz;
        imu.linear_acceleration.x = accelmetorx;
        imu.linear_acceleration.y = accelmetory;
        imu.linear_acceleration.z = accelmetorz;
        imu_pub.publish(imu);
        loop_rate.sleep();
    }
    return 0;
}
 



