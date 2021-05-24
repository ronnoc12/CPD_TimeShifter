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

	char continueChar = ' '; 
	string output = ""; 

	int Minutes_PreShift = 0; 
	int seconds_PreShift = 0;
	int milis_PreShift = 0;
	
	int minutesOfTimeShift = 0; 
	int secondsOfTimeShift = 0;
	int millisOfTimeShift = 0;

	int shiftedMinutes = 0; 
	int shiftedSeconds = 0; 
	int shiftedMillis = 0; 

	cout << "First enter the amount of minutes the value needs to be shifted by" << endl; 
	cin >> minutesOfTimeShift;
	cout << "Enter the seconds value" << endl;
	cin >> secondsOfTimeShift;
	cout << "Enter the frames value" << endl;
	cin >> millisOfTimeShift;

	


	while (continueChar != 'e')
	{
		cout << "Enter the minutes value" << endl;
		cin >> Minutes_PreShift;
		cout << "Enter the seconds value" << endl;
		cin >> seconds_PreShift;
		cout << "Enter the frames value" << endl;
		cin >> milis_PreShift;

		shiftedMinutes = Minutes_PreShift - minutesOfTimeShift; 
		
		if (seconds_PreShift < secondsOfTimeShift)
		{
			shiftedMinutes--; //subtract one minute
			seconds_PreShift += 60; //distribute the 60 seconds
		}

		shiftedSeconds = seconds_PreShift - secondsOfTimeShift; 
		
		if (milis_PreShift < millisOfTimeShift)
		{
			if (shiftedSeconds != 0)
			{
				shiftedSeconds--; //subtract one second 
			}
			else
			{
				shiftedMinutes--;
				shiftedSeconds = 59; 
			}
			
			milis_PreShift += 25; //distribute the one second you subtracted to the millis value
		}
		 
		shiftedMillis = milis_PreShift - millisOfTimeShift;

		output = output + "Shifted Value is ";
		
		if (shiftedMinutes < 10)
		{
			output = output + "0";
		}

		output = output + to_string(shiftedMinutes);
		output = output + ":";

		if (shiftedSeconds < 10)
		{
			output = output + "0";
		}

		output = output + to_string(shiftedSeconds);
		output = output + ":";

		if (shiftedMillis < 10)
		{
			output = output + "0";
		}

		output = output + to_string(shiftedMillis);
		cout << output << endl; 
		output = ""; 

		cout << endl;
		//cout << "Press 'e' to exit otherwise any other key to continue: "; 
		//cin >> continueChar; 
	}
}