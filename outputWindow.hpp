#ifndef OUTPUT_WINDOW_HPP
#define OUTPUT_WINDOW_HPP

#include <string>

#include <QWidget>
#include <QtWidgets>

#include "qt_interpreter.hpp"

class OutputWindow : public QWidget {
    Q_OBJECT

public:

    OutputWindow(QWidget* parent = nullptr);
    OutputWindow(std::string filename, QWidget* parent = nullptr);
    QWidget* outWindow;

signals:

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

    void ReceiveFile(QString* fileName);

private:
    QLineEdit* TopBox; 
};


#endif#pragma once
