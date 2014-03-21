#include "EV3Listener.h"//class file

namespace ev3_server {

const QString myAddress = QString("192.168.20.2");//set up the IP for this computer

Ev3Listener::Ev3Listener(int argc, char** argv, QObject* pParent)
    :	QObject(pParent)
{

    connect(this, SIGNAL(emitXVel(double), m_pPubThread, SLOT(setXVel(double));
    connect(this, SIGNAL(emitYVel(double), m_pPubThread, SLOT(setYVel(double));
    connect(this, SIGNAL(emitThVel(double), m_pPubThread, SLOT(setThVel(double));

    m_pTcpServer = new QTcpServer(this); //create the TcpServer

    if (!m_pTcpServer->listen(QHostAddress(myAddress), 5512)) 
    {
        std::cerr << tr("TCP Server").toStdString(),
                tr("Unable to start the server: %1.\n")
                .arg(m_pTcpServer->errorString()).toStdString();
        exit(-1);
        return;
    }//verify that the server was constructed properly.

    QString ipAddress = QHostAddress(myAddress).toString(); //Read this server's IP.

    std::cout << tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                    "Run the Client now.")
                 .arg(ipAddress).arg(m_pTcpServer->serverPort()).toStdString() << std::endl;

    /* At this point, the server is up and running. We will now connect the Q_SLOTS **/

    connect(m_pTcpServer, SIGNAL(newConnection()), SLOT(NewClientConnection()));
    /** TODO: Start the ROS state publishing **/

    // m_RobotThread.init();
    // m_RobotThread.start();
}//end constructor

void Ev3Listener::NewClientConnection() 
{
	QTcpSocket * pClientSocket = m_pTcpServer->nextPendingConnection(); //connect the new request.
	if(pClientSocket)
    {
		connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()));
		connect(pClientSocket, SIGNAL(readyRead()), SLOT(NewClientCommand()));

        /** readyRead() fires when a new message is published to the server.
            we have connected readyRead() to the Q_SLOT NewClientCommand **/
	}//verify that a connection has been established.

    else{ std::cout<<"Request has been rejected by the server.\n"; }
}//this slot is triggered upon receiving a connection request.

void Ev3Listener::writeData()
{
    //QTcpSocket *pClientSocket = qobject_cast<QTcpSocket*>(sender());
    //Q_UNUSED(pClientSocket);
    //const QRegExp rxlen("^(\\w+)\\s+(-*\\d*\\.?\\d*)\\s+(-*\\d*\\.?\\d*)$");
    //QString text(pClientSocket->read(length));
	
    //pClientSocket->write(m_RobotThread.getForwardSpeed());
}

void Ev3Listener::NewClientCommand() 
{
    int length;
    QString line = "";
    QTcpSocket * pClientSocket = qobject_cast<QTcpSocket *>(sender());
    pClientSocket->waitForBytesWritten(1000);
    line = pClientSocket->readAll();

        std::cout<<"New message received: " + line.toStdString() + "\n";

        /** Ok. At this point, the client has sent a message. 
            Now we must determine the contents of said message. **/
    //}//this runs while the server has a message.   
}//controls the new message.

}//end namespace ev3_listener
