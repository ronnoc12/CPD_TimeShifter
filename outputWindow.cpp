#include "outputWindow.hpp"

#include <iostream>

#include <QLayout>

using namespace std;

OutputWindow::OutputWindow(QWidget* parent) : OutputWindow("", parent)
{
    mainWindow = new QWidget(this);
    TopBox = new QLineEdit(this); 

    QGridLayout* layout = new QGridLayout(this);

    auto enterButton = new QPushButton(); 

    //QString TopText = TopBox->getText();

    //object->setText(TopText); 
    //object->setPalette(palette);

    TopBox->setMaximumHeight(30);

    //place each object in the window to be displayed
    layout->addWidget(TopBox);

    setLayout(layout); //set the layout so it can be printed

    QObject::connect(enterButton, SIGNAL(clicked()), this, &MainWindow::ReceiveFile);
}

MainWindow::MainWindow(std::string filename, QWidget* parent) : QWidget(parent) {
    // TODO: your code here...
}