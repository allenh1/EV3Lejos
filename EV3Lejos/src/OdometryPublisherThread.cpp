#include "OdometryPublisherThread.h"

namespace ev3_server {

//tf::TransformBroadcaster odom_broadcaster;

Ev3OdomPublisher::Ev3OdomPublisher(int argc, char **pArgv)
    : m_Init_argc(argc),
      m_pInit_argv(pArgv)
{/** Constructor for the thread **/}

Ev3OdomPublisher::~Ev3OdomPublisher()
{
    if (ros::isStarted())
    {
        ros::shutdown();
        ros::waitForShutdown();
    }//end if

    wait();
}//shut down ROS

bool Ev3OdomPublisher::init()
{
    ros::init(m_Init_argc, m_pInit_argv, "ev3_driver");

    if (!ros::master::check())
        return false; //do not start unless roscore is up!

    ros::start();
    ros::Time::init();
    ros::NodeHandle nh;

    odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 50);
}//initialize the Odometry publisher.

void Ev3OdomPublisher::run()
{
    ros::Rate loop_rate(1);

    m_currentTime = ros::Time::now();
    m_lastTime = ros::Time::now();

    while (ros::ok())
    {
        /** This function controls the messages
         *  that the odometry is emmitting **/
        m_currentTime = ros::Time::now();

        /** Project state forward **/
        m_mutex.lock();
        double dt = (m_currentTime - m_lastTime).toSec();
        double delta_x = (m_xVel * cos(m_thPose) - m_yVel * sin(m_thPose)) * dt;
        double delta_y = (m_xVel * sin(m_thPose) + m_yVel * cos(m_thPose)) * dt;
        double delta_th = m_thVel * dt;
        m_mutex.unlock();

        m_xPose  += delta_x;
        m_yPose  += delta_y;
        m_thPose += delta_th;

        //All odometry is 6DOF - thus we need a quaternion
        geometry_msgs::Quaternion odom_quat = tf::createQuaternionFromYaw(m_thPose);

        //publish the transform over tf
        // geometry_msgs::TransformStamped odom_trans;
        // odom_trans.header.stamp = current_time;
        // odom_trans.header.frame_id = "odom";
        // odom_trans.child_frame_id = "base_link";

        // odom_trans.transform.translation.x = m_xPose;
        // odom_trans.transform.translation.y = m_yPose;
        // odom_trans.transform.translation.z = 0.0;
        // odom_trans.transform.rotation = odom_quat;

        // //publish the transform
        // odom_broadcaster.sendTransform(odom_trans);

        //publish the odometry message
        nav_msgs::Odometry odom_msg;
        odom_msg.header.stamp = current_time;
        odom_msg.header.fram_id = "odom";

        //set the position of the state
        odom_msg.child_frame_id = "base_link";
        odom_msg.pose.pose.position.x = m_xPose;
        odom_msg.pose.pose.position.y = m_yPose;
        odom_msg.pose.pose.position.z = 0.0;
        odom_msg.pose.pose.orientation = odom_quat;

        //set the velocity of the state
        m_mutex.lock();
        odom_msg.twist.twist.linear.x = m_xVel;
        odom_msg.twist.twist.linear.y = m_yVel;
        odom_msg.twist.twist.angular.z = m_thVel;
        m_mutex.unlock();

        m_odom_pub.publish(odom_msg);

        m_last_time = current_time;

        ros::spinOnce();
        loop_rate.sleep();
    }//end while
}//thread's run loop.

void Ev3OdomPublisher::setXVel(double xVel){ m_mutex.lock(); m_xVel = xVel; m_mutex.unlock(); }
void Ev3OdomPublisher::setYVel(double yVel){ m_mutex.lock(); m_yVel = yVel; m_mutex.unlock(); }
void Ev3OdomPublisher::setThVel(double thVel){ m_mutex.lock(); m_thVel = thVel; m_mutex.unlock(); }
}//end namespace
