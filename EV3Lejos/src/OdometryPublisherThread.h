#ifndef ODOM_PUB_H
#define ODOM_PUB_H

namespace ev3_server {

/** Include Qt Dependencies **/
#include <QThread>
#include <QObject>
#include <QString>
#include <QMutex>

/** Include ROS Headers **/
#include <ros/ros.h>
#include <ros/network.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

class Ev3OdomPublisher : public QThread
{
    Q_OBJECT //Q_Object Macro

public:
    Ev3OdomPublisher(int argc, char ** pArgv);
    virtual ~Ev3OdomPublisher();

    bool init();//initialize ros connections

    void run(); //run loop for the thread

    Q_SLOT void setXVel(double xVel);
    Q_SLOT void setYVel(double yVel);
    Q_SLOT void setThVel(double thVel);

private:
    int m_Init_argc;
    char** m_pInit_argv;

    double m_xVel;
    double m_yVel;
    double m_thVel;

    double m_xPose;
    double m_yPose;
    double m_thPose;

    QMutex m_mutex;

    ros::Publisher m_odom_pub;
    ros::Time m_currentTime;
    ros::Time m_lastTime;
};

}

#endif
