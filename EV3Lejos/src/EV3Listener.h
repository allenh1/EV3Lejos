#ifndef EV3_LISTENER_H
#define EV3_LISTENER_H

#include <QtNetwork/QtNetwork> //provides TCP stuffs
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtWidgets>
#include <QObject>
#include <QString>
#include <iostream>

QT_BEGIN_NAMESPACE
class QTcpServer;
QT_END_NAMESPACE

namespace ev3_server {

#define PI 3.1415926535898

class Ev3Listener : public QObject {
    Q_OBJECT

public:
    Ev3Listener(int argc, char** argv, QObject* pParent = NULL);
    //~Server();

    void writeData();
private Q_SLOTS:
	void NewClientConnection();
	void NewClientCommand();

private:
    QTcpServer* m_pTcpServer;
};//end class Ev3Listener

}//end namespace ev3_server
#endif
