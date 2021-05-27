#ifndef OUTPUT_WINDOW_HPP
#define OUTPUT_WINDOW_HPP

#include <string>

#include <QWidget>
#include <QtWidgets>
#include <fstream>
#include <iostream>
#include <QLayout>
#include <cmath>

class OutputWindow : public QWidget {
    Q_OBJECT

public:

    OutputWindow(QWidget* parent = nullptr);
    QWidget* outWindow;
    

//signals:

    /*void notify(QString entry);

    void sendErrorMessage(QString entry);

    void sendInfo(QString entry);

    void notifyCanvas(QGraphicsItem* item);

    void sendPoint(QGraphicsEllipseItem* item);

    void sendLine(QGraphicsLineItem* item);*/

public slots:

    /*void ReceiveLine(QString entry);
    //TODO pick up draw graphic function to be handed off to canvas widget
    void ReceiveInterpreterInfo(QString info);

    void ReceiveInterpreterError(QString error);

    void ReceivePoint(QGraphicsEllipseItem* item);

    void getLine(QGraphicsLineItem* item);*/

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
    QLineEdit* hoursBox; 
    QLineEdit* minutesBox;
    QLineEdit* secondsBox; 
    QLineEdit* framesBox;  
};


#endif