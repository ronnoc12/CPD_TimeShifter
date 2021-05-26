#include "outputWindow.hpp"

using namespace std;

//Function Declarations
bool isInt(string inputString);
bool isTimeStamp(string inputString); 
int QStringTOInt(QString input); 

OutputWindow::OutputWindow(QWidget* parent) : QWidget(parent)
{
    string stdTextHolder = "Please Enter Desired Filepath: "; 
    string outFilePromptText = "Please Enter Title For Saved Edited File: ";
    string minutesPrompt = "Please Enter Number of Minutes Shifted: "; 
    string secondsPrompt = "Please Enter Number of Seconds Shifted: ";
    string framesPrompt = "Please Enter Number of Frames Shifted: ";
    string hoursPrompt = "Please Enter Number of Hours Shifted: ";

    outWindow = new QPlainTextEdit;
    TopBox = new QLineEdit; 
    BottomBox = new QLineEdit; 

    inputFilePrompt = new QLabel; 
    outputFilePrompt = new QLabel; 
    inputHours = new QLabel;
    inputMinutes = new QLabel; 
    inputSeconds = new QLabel; 
    inputFrames = new QLabel;

    hoursBox = new QLineEdit; 
    minutesBox = new QLineEdit;
    secondsBox = new QLineEdit; 
    framesBox = new QLineEdit;  

    QString labelTextHolder = QString::fromStdString(stdTextHolder); 
    QString outFileLabelText = QString::fromStdString(outFilePromptText); 
    QString hoursPromptLabel = QString::fromStdString(hoursPrompt); 
    QString minutesPromptLabel = QString::fromStdString(minutesPrompt);
    QString secondsPromptLabel = QString::fromStdString(secondsPrompt); 
    QString framesPromptLabel = QString::fromStdString(framesPrompt);  

    inputFilePrompt->setText(labelTextHolder); 
    outputFilePrompt->setText(outFileLabelText); 
    inputHours->setText(hoursPromptLabel); 
    inputMinutes->setText(minutesPromptLabel); 
    inputSeconds->setText(secondsPromptLabel); 
    inputFrames->setText(framesPromptLabel); 

    QGridLayout* layout = new QGridLayout(this);

    auto enterButton = new QPushButton("Enter"); 
    enterButton->setMinimumSize(QSize(150, 1));

    TopBox->setMinimumSize(QSize(150, 1));
    BottomBox->setMinimumSize(QSize(150, 1));
    hoursBox->setMinimumSize(QSize(50, 1));
    minutesBox->setMinimumSize(QSize(50, 1));
    secondsBox->setMinimumSize(QSize(50, 1));
    framesBox->setMinimumSize(QSize(50, 1));

    //place each object in the window to be displayed
    layout->addWidget(inputFilePrompt, 1, 1);
    layout->addWidget(TopBox, 2, 1);
    layout->addWidget(outputFilePrompt, 3, 1);
    layout->addWidget(BottomBox, 4, 1); 
    
    layout->addWidget(inputHours, 5, 1); 
    layout->addWidget(hoursBox, 5, 2);

    layout->addWidget(inputMinutes, 6, 1);
    layout->addWidget(minutesBox, 6, 2); 

    layout->addWidget(inputSeconds, 7, 1);
    layout->addWidget(secondsBox, 7, 2); 

    layout->addWidget(inputFrames, 8, 1);
    layout->addWidget(framesBox, 8, 2); 

    layout->addWidget(enterButton, 9, 2); 

    setLayout(layout); //set the layout so it can be printed

    QPushButton::connect(enterButton, SIGNAL(clicked()), this, SLOT(ReceiveFile()));
}

void OutputWindow::ReceiveFile()
{
    //initialize variables for later
    string input = "";
    int size = 0; 
    bool ok = false; 
    int shiftedHours   = 0;  
    int shiftedMinutes = 0;  
    int shiftedSeconds = 0;  
    int shiftedFrames  = 0; 

    string hoursHolder = "";
    string minutesHolder = ""; 
    string secondsHolder = ""; 
    string framesHolder = ""; 
    string tempValue = ""; 

    //get input file path and output file name from gui user input
    QString inputFilePath = TopBox->text(); 
    QString outputFileName = BottomBox->text();
    QString QshiftedHours   = hoursBox->text(); 
    QString QshiftedMinutes = minutesBox->text(); 
    QString QshiftedSeconds = secondsBox->text(); 
    QString QshiftedFrames  = framesBox->text();  

    //convert Qstrings with ints to integers
    shiftedHours = QStringTOInt(QshiftedHours); 
    shiftedMinutes = QStringTOInt(QshiftedMinutes);
    shiftedSeconds = QStringTOInt(QshiftedSeconds);
    shiftedFrames = QStringTOInt(QshiftedFrames); 

    //convert collected values from QString to stdString for use later 
    string StdInPath = inputFilePath.toStdString(); 
    string StdOutFile = outputFileName.toStdString(); 

    //attempt to open the specified file 
    ifstream ifs(StdInPath);
    ofstream ofs;
    ofs.open (StdOutFile, std::ofstream::out | std::ofstream::app);

    //so long as we are able to read from the file
    while(ifs.good())
    {
        //get line of text from the file
        getline(ifs, input);

        //For debugging 
        //cout << "Input recieved from file: " << input << endl; 

        //TODO if and of the charcters are a letter then we can just copy it to the new file becayse it is not a line containing a time stamp 
        //otherwise it contains a time stamp and will need to be adjusted before appending to the output file
        ok = isTimeStamp(input); 

        if (ok) //if all of the characters in the input string are of the time stamp format then process it like a time stamp 
        {
            //cout << "Input: " << input << " passed isTimeStamp() check!" << endl; //for Debugging
            size = input.size(); 
            //for each character from the input line we pulled in 
            for (int i = 0; i < size; i++)
            {
                if (input[i] == ':')
                {
                    if (isInt(tempValue)) //if the number collected by tempValue is a valid integer
                    {
                        if (hoursHolder == "")
                        {
                            hoursHolder = tempValue; 
                        }
                        else if (minutesHolder == "")
                        {
                            minutesHolder = tempValue; 
                        }
                        else 
                        {
                            cout << "ERROR: Too many inputs collected from file, all value holders are already filled!" << endl;
                        }
                        tempValue = ""; 
                    }
                }
                else if (input[i] == '.')
                {
                    if ((isInt(tempValue)) && (secondsHolder == ""))
                    {
                        secondsHolder = tempValue; 
                        tempValue = ""; 
                    }

                    i++; 
                    tempValue = input.substr(i,3);
                    if (isInt(tempValue) && (framesHolder == ""))
                    {
                        framesHolder = tempValue; 
                    }
                    else 
                    {
                        cout << "Failed to get frames value, insted got vlaue:" << tempValue << endl; // For Debugging
                    }

                    i += 2; //should be comma or end of line character
                    cout << "i value after frames aquired: " << input[i] << endl;
                }
                else if (input[i] == ',') //if we hit a comma that means we have all the values needed to adjust the first set of times
                {
                    if ((framesHolder != "") && (hoursHolder != "") && (minutesHolder != "") && (secondsHolder != ""))
                    {
                        //TODO adjust time stamps and print to file
                        //TODO run values and then append output to outputfile
                        cout << "Ready to process new time stamp value:" << endl; //For Debugging
                        cout << "Hours Value: " << hoursHolder << endl; //For Debugging
                        cout << "Minutes Value: " << minutesHolder << endl; //For Debugging
                        cout << "Seconds Value: " << secondsHolder << endl; //For Debugging
                        cout << "Frames Value: " << framesHolder << endl; //For Debugging
                    }

                    //reset values for the next batch of inputs
                    hoursHolder = "";
                    minutesHolder = ""; 
                    secondsHolder = ""; 
                    framesHolder = ""; 
                    tempValue = ""; 
                }
                else //input is not a : or , (should be numberical value OR string of words for the actual captions)
                {
                    tempValue = tempValue + input[i]; 
                }
            }  

            if ((framesHolder != "") && (hoursHolder != "") && (minutesHolder != "") && (secondsHolder != ""))
            {
                //TODO adjust time stamps and print to file
                //TODO run values and then append output to outputfile
                cout << "Ready to process new time stamp value:" << endl; //For Debugging
                cout << "Hours Value: " << hoursHolder << endl; //For Debugging
                cout << "Minutes Value: " << minutesHolder << endl; //For Debugging
                cout << "Seconds Value: " << secondsHolder << endl; //For Debugging
                cout << "Frames Value: " << framesHolder << endl; //For Debugging
            }
        }
        else //the input was a string which can be directly appended to the output file 
        {
            ofs << input << endl; 
             
            //cout << "Input: " << input << ", is not a timestamp so it gets appended directly to output file!" << endl; //For Debugging
        }

        //reset values for the next batch of inputs
        hoursHolder = "";
        minutesHolder = ""; 
        secondsHolder = ""; 
        framesHolder = ""; 
        tempValue = "";    
    }
}

bool isInt(string inputString)
{
   for (int i =0; i< inputString.size(); i++)
   {
        if (inputString[i] == 13)
        {
            continue; 
        }
        else if ((inputString[i] < '0') || (inputString[i] > '9')) //if the chatacter is not a numerical one
        {
           return false; 
        }
   }
   return true; 
}

//returns true if all the characters in the string follow the time stamp syntax otherwise it returns false
bool isTimeStamp(string inputString)
{
   for (int i =0; i< inputString.size(); i++)
   {
       if  ((inputString[i] == '0') || (inputString[i] == '1') || (inputString[i] == '2') || (inputString[i] == '3') || (inputString[i] == '4') || (inputString[i] == '5') || (inputString[i] == '6') || (inputString[i] == '7') || (inputString[i] == '8') || (inputString[i] == '9') || (inputString[i] == ' ') || (inputString[i] == ',') || (inputString[i] == ':') || (inputString[i] == '.'))//if the chatacter is not a numerical one
       {
            //do nothing
       }
       else if (inputString[i] == 13)
       {
           //new line character 
           //cout << "carraige return character hit!" << endl; //for debugging 
       }
       else
       {
            //std::cout << "numerical value of failed character: " << static_cast<unsigned>(inputString[i]) << endl; 
            //cout << "failed on character: " << inputString[i] << " at position: " << i << endl; //for debugging 
            //cout << "String: " << inputString << "Failed isTimeStamp Check" << endl; //for Debugging 
            return false;
       }
   }
   return true;     
}

int QStringTOInt(QString input)
{
    int output = 0; 
    string StdInput = input.toStdString(); 

    if (isInt(StdInput))
    {
        output = stoi(StdInput); 
    }

    return output; 
}