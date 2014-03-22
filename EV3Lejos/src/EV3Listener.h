#ifndef EV3_LISTENER_H
#define EV3_LISTENER_H

#include "OdometryPublisherThread.h" //thread for publishing the odometry

#define PI 3.1415926535898

class Ev3Listener : public QObject {
    Q_OBJECT

public:
    Ev3Listener(int argc, char** argv, QObject* pParent = NULL);

    void writeData();

    Q_SIGNAL void emitXVel(double);
    Q_SIGNAL void emitYVel(double);
    Q_SIGNAL void emitThVel(double);

private Q_SLOTS:
	void NewClientConnection();
	void NewClientCommand();

private:
    QTcpServer* m_pTcpServer;
    Ev3OdomPublisher m_PubThread;
};//end class Ev3Listener

#include <QtNetwork/QtNetwork> //provides TCP stuffs
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <iostream>

#endif
