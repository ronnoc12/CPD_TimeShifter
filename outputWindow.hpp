#ifndef OUTPUT_WINDOW_HPP
#define OUTPUT_WINDOW_HPP

#include <string>

#include <QWidget>
#include <QtWidgets>
#include <fstream>
#include <iostream>
#include <QLayout>

using namespace std;

class OutputWindow : public QWidget {
    Q_OBJECT

public:

    OutputWindow(QWidget* parent = nullptr);
    QWidget* outWindow;

    //Function Declarations
    bool isInt(string inputString);
    bool isTimeStamp(string inputString); 
    int QStringTOInt(QString input); 
    std::string editTimeStampValues(int shiftAmountHours, int shiftAmountMinutes, int shiftAmountSeconds, int shiftAmountFrames, std::string hoursHolder, std::string minutesHolder, std::string secondsHolder, std::string framesHolder);
    bool checkTimeStamp(int shiftAmountHours, int shiftAmountMinutes, int shiftAmountSeconds, int shiftAmountFrames, std::string hoursHolder, std::string minutesHolder, std::string secondsHolder, std::string framesHolder);
    bool getOutputTimeStamp(std::string StdOutFile, bool validSecondTimeStamp, bool validFirstTimeStamp, std::string timeStampFirstHalf, std::string timeStampSecondHalf);
    void clearFile(std::string StdOutFile);

public slots:

    void ReceiveFile();

private:
    QLineEdit* TopBox; 
    QLineEdit* BottomBox; 
    QLabel* inputFilePrompt; 
    QLabel* outputFilePrompt; 

    QLabel* inputHours;
    QLabel* inputMinutes; 
    QLabel* inputSeconds; 
    QLabel* inputFrames;  
    QLabel* errorLabel;
    QLineEdit* hoursBox; 
    QLineEdit* minutesBox;
    QLineEdit* secondsBox; 
    QLineEdit* framesBox;  

    QLineEdit* sysOutput; 
    QPalette *palette;
};


#endif