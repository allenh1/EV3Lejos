#include "EV3Listener.h"//class file

namespace ev3_server {

const QString myAddress = QString("10.0.0.30");//set up the IP for this computer

Ev3Listener::Ev3Listener(int argc, char** argv, QObject* pParent)
    :	QObject(pParent)
{

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
    // while (!line.contains(QString('@')))
    // {
    //     line += pClientSocket->readLine();
    //     std::cout<<"\t waiting for bytes written...\n";
    //     waitForBytesWritten();
    // }

    // while(pClientSocket->bytesAvailable() > 0) 
    // {
    //     //length = static_cast<int>(pClientSocket->read(1).at(0));	// Read the command size.
    //     QString line = "";

    //     bool endOfLine = false;
    //     bool endOfStream = false;
    //     int bytesAvail = pClientSocket->bytesAvailable();

    //     while ((!endOfLine) && (!endOfStream)) 
    //     {
    //         char ch;
    //         int bytesRead = pClientSocket->read(&ch, sizeof(ch));
    //         if (bytesRead == sizeof(ch)) {
    //             if (ch != '@')
    //                 line.append(ch);

    //             if (ch == '@')
    //                 endOfLine = true;
    //         }//end if
    //         else { endOfStream = true; }//done reading
    //     }//end while


        std::cout<<"New message received: " + line.toStdString() + "\n";

        /** Ok. At this point, the client has sent a message. 
            Now we must determine the contents of said message. **/
    //}//this runs while the server has a message.   
}//controls the new message.

}//end namespace ev3_listener
