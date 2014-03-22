#include "EV3Listener.h"
#include <QCoreApplication>

int main(int argc, char** argv){
	
	QCoreApplication app(argc, argv);

    Ev3Listener s(argc, argv);//construct the server

	return app.exec();//execute the application. Quit when server exits.
}//end main.
