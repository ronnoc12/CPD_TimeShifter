#include <string>
#include <iostream>
#include <iomanip>

#include "outputWindow.hpp"
#include <QApplication> 

using namespace std; 

int main(int argc, char* argv[])
{
	QApplication app(argc, argv); 

	OutputWindow gui; 
	gui.show(); 
	return app.exec(); 

	return EXIT_SUCCESS;
}