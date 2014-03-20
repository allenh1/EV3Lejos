#include "EV3Listener.h"
#include <QCoreApplication>

using namespace ev3_server;

int main(int argc, char** argv){
	
	QCoreApplication app(argc, argv);

    Ev3Listener s(argc, argv);//construct the server

	//for(;;)
	//	;
	//system("pause");
	return app.exec();//execute the application. Quit when server exits.
}//end main.
