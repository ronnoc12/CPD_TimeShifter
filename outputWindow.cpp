#include "outputWindow.hpp"

using namespace std;

OutputWindow::OutputWindow(QWidget* parent) : QWidget(parent)
{
    string stdTextHolder = "Please Enter Desired Filepath: "; 
    string outFilePromptText = "Please Enter Title For Saved Edited File: ";
    string minutesPrompt = "Please Enter Number of Minutes Shifted: "; 
    string secondsPrompt = "Please Enter Number of Seconds Shifted: ";
    string framesPrompt = "Please Enter Number of Frames Shifted: ";
    string hoursPrompt = "Please Enter Number of Hours Shifted: ";
    string errorOut = "(Error Messages)"; 

    outWindow = new QPlainTextEdit;
    TopBox = new QLineEdit; 
    BottomBox = new QLineEdit; 

    inputFilePrompt = new QLabel; 
    outputFilePrompt = new QLabel; 
    inputHours = new QLabel;
    inputMinutes = new QLabel; 
    inputSeconds = new QLabel; 
    inputFrames = new QLabel;
    errorLabel = new QLabel;

    sysOutput = new QLineEdit; 

    sysOutput->setReadOnly(true);

    palette = new QPalette();
    palette->setColor(QPalette::Text,Qt::black);
    sysOutput->setPalette(*palette);

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
    QString errorpromptLabel = QString::fromStdString(errorOut);

    inputFilePrompt->setText(labelTextHolder); 
    outputFilePrompt->setText(outFileLabelText); 
    inputHours->setText(hoursPromptLabel); 
    inputMinutes->setText(minutesPromptLabel); 
    inputSeconds->setText(secondsPromptLabel); 
    inputFrames->setText(framesPromptLabel); 
    errorLabel->setText(errorpromptLabel); 

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

    layout->addWidget(errorLabel, 10, 2); 
    layout->addWidget(sysOutput, 10, 1); 

    setLayout(layout); //set the layout so it can be printed

    QPushButton::connect(enterButton, SIGNAL(clicked()), this, SLOT(ReceiveFile()));
}

void OutputWindow::ReceiveFile()
{
    //initialize variables for later
    QString ErrorMsg; 
    string inputErrorMessage = "ERROR: Too many inputs collected from file, all value holders are already filled!"; 
    string processCompleteMsg = "Finished with time shifting! \nOutput written to: ";
    string input = "";
    
    int size = 0; 
    bool ok = false; 
    bool validSecondTimeStamp = false; 
    bool validFirstTimeStamp = false; 
    bool printText = false; 

    int shiftAmountHours   = 0;
    int shiftAmountMinutes = 0;
    int shiftAmountSeconds = 0;
    int shiftAmountFrames  = 0;

    string hoursHolder = "";
    string minutesHolder = ""; 
    string secondsHolder = ""; 
    string framesHolder = ""; 
    string tempValue = ""; 
    string timeStampFirstHalf = "";
    string timeStampSecondHalf = ""; 
    string timeStampOutput = "";

    //get input file path and output file name from gui user input
    QString inputFilePath = TopBox->text(); 
    QString outputFileName = BottomBox->text();
    QString QshiftedHours   = hoursBox->text(); 
    QString QshiftedMinutes = minutesBox->text(); 
    QString QshiftedSeconds = secondsBox->text(); 
    QString QshiftedFrames  = framesBox->text();  

    //convert Qstrings with ints to integers
    shiftAmountHours = QStringTOInt(QshiftedHours);
    shiftAmountMinutes = QStringTOInt(QshiftedMinutes);
    shiftAmountSeconds = QStringTOInt(QshiftedSeconds);
    shiftAmountFrames = QStringTOInt(QshiftedFrames);

    //adjust frames from frames to millis value
    shiftAmountFrames = (shiftAmountFrames * 40); 

    //convert collected values from QString to stdString for use later 
    string StdInPath = inputFilePath.toStdString(); 
    string StdOutFile = outputFileName.toStdString(); 

    processCompleteMsg += StdOutFile; 

    //attempt to open the specified file 
    ifstream ifs(StdInPath);
    ofstream ofs; 

    //open the file and clear it's contents before we try to write to it later on
    clearFile(StdOutFile);

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
                            ErrorMsg = QString::fromStdString(inputErrorMessage);
                            palette->setColor(QPalette::Text,Qt::red);
                            sysOutput->setPalette(*palette);
                            sysOutput->setText(ErrorMsg); 
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

                    i += 2; //should be comma or end of line character
                    //cout << "i value after frames aquired: " << input[i] << endl;
                }
                else if (input[i] == ',') //if we hit a comma that means we have all the values needed to adjust the first set of times
                {
                    if ((framesHolder != "") && (hoursHolder != "") && (minutesHolder != "") && (secondsHolder != ""))
                    {
                        //check if the time stamp is less than the amount of time shift
                        validFirstTimeStamp = checkTimeStamp(shiftAmountHours, shiftAmountMinutes, shiftAmountSeconds, shiftAmountFrames, hoursHolder, minutesHolder, secondsHolder, framesHolder);
                        
                        //adjust time stamps and print to file
                        if (validFirstTimeStamp == true) //only calculate shifted time if the current time stamp is larger than the amount of shift needed
                        {
                            timeStampFirstHalf = editTimeStampValues(shiftAmountHours, shiftAmountMinutes, shiftAmountSeconds, shiftAmountFrames, hoursHolder, minutesHolder, secondsHolder, framesHolder);
                        }
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
                //check if the time stamp is less than the amount of time shift
                validSecondTimeStamp = checkTimeStamp(shiftAmountHours, shiftAmountMinutes, shiftAmountSeconds, shiftAmountFrames, hoursHolder, minutesHolder, secondsHolder, framesHolder);
               
                if (validSecondTimeStamp == true) //only calculate shifted time if the current time stamp is larger than the amount of shift needed
                {
                    timeStampSecondHalf = editTimeStampValues(shiftAmountHours, shiftAmountMinutes, shiftAmountSeconds, shiftAmountFrames, hoursHolder, minutesHolder, secondsHolder, framesHolder);
                }
               
                //if the previous time stamp was printed then add a new line befor printing the next time stamp
                if (printText == true)
                {
                    ofs.open (StdOutFile, std::ofstream::out | std::ofstream::app);
                    ofs << "" << endl; 
                    ofs.close(); 
                }

                //print the output based on the values of the timeStampCheck function 
                printText = getOutputTimeStamp(StdOutFile, validSecondTimeStamp, validFirstTimeStamp, timeStampFirstHalf, timeStampSecondHalf);

                //reset values for the next batch of inputs
                hoursHolder = "";
                minutesHolder = ""; 
                secondsHolder = ""; 
                framesHolder = ""; 
                tempValue = "";
            }
        }
        else //the input was a string which can be directly appended to the output file 
        {
            if (printText == true) //means the timestamp shift was valid so we can print the text
            {
                ofs.open (StdOutFile, std::ofstream::out | std::ofstream::app);
                ofs << input << endl; 
                ofs.close(); 
            } 
        }  
    }

    //print message to gui that lets user know the process was completed sucessfully
    ErrorMsg = QString::fromStdString(processCompleteMsg);
    palette->setColor(QPalette::Text,Qt::black);
    sysOutput->setPalette(*palette);
    sysOutput->setText(ErrorMsg); 
}

bool OutputWindow::getOutputTimeStamp(std::string StdOutFile, bool validSecondTimeStamp, bool validFirstTimeStamp, std::string timeStampFirstHalf, std::string timeStampSecondHalf)
{
    ofstream out;
    string zeroTimeStamp = "0:00:00.000";
    string timeStampOutput = ""; 

    if ((validFirstTimeStamp == true) && (validSecondTimeStamp == true)) //if both time stamps are valid and less than the shift amount
    {
        timeStampOutput = timeStampFirstHalf; 
        timeStampOutput = timeStampOutput + ","; 
        timeStampOutput = timeStampOutput + timeStampSecondHalf;

        out.open (StdOutFile, std::ofstream::out | std::ofstream::app);
        out << timeStampOutput << endl;
        out.close();

        return true; 
    }
    else if ((validFirstTimeStamp == false) && (validSecondTimeStamp == true)) //the first time stamp is not valid but the second is 
    {
        timeStampOutput = zeroTimeStamp; //set the time stamp to begin at zero 
        timeStampOutput = timeStampOutput + ","; 
        timeStampOutput = timeStampOutput + timeStampSecondHalf;

        out.open (StdOutFile, std::ofstream::out | std::ofstream::app);
        out << timeStampOutput << endl;
        out.close();

        return true; 
    }
    return false; 
}

bool OutputWindow::isInt(string inputString)
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
bool OutputWindow::isTimeStamp(string inputString)
{
   for (int i =0; i< inputString.size(); i++)
   {
       if  ((inputString[i] == '0') || (inputString[i] == '1') || (inputString[i] == '2') || (inputString[i] == '3') || (inputString[i] == '4') || (inputString[i] == '5') || (inputString[i] == '6') || (inputString[i] == '7') || (inputString[i] == '8') || (inputString[i] == '9') || (inputString[i] == ' ') || (inputString[i] == ',') || (inputString[i] == ':') || (inputString[i] == '.'))//if the chatacter is not a numerical one
       {
            continue; 
       }
       else if (inputString[i] == 13)
       {
           continue; 
       }
       else
       {
            return false;
       }
   }
   return true;     
}

//function to convert a QString to an integer
int OutputWindow::QStringTOInt(QString input)
{
    int output = 0; 
    string StdInput = input.toStdString(); 

    if (isInt(StdInput))
    {
        output = stoi(StdInput); 
    }

    return output; 
}

//function for ensuring that a given time stamp is less than the amount of shift to make sure that we don't end up with negative numbers 
bool OutputWindow::checkTimeStamp(int shiftAmountHours, int shiftAmountMinutes, int shiftAmountSeconds, int shiftAmountFrames, std::string hoursHolder, std::string minutesHolder, std::string secondsHolder, std::string framesHolder)
{
    int inputHours = stoi(hoursHolder); 
    int inputMinutes = stoi(minutesHolder);
    int inputSeconds = stoi(secondsHolder);
    int inputFrames = stoi(framesHolder);
    double inSecFrames = (inputFrames/1000);
    double shiftSecFrames = (shiftAmountFrames/1000);

    double totalCurrentSeconds = ((inputHours * 60 * 60) + (inputMinutes * 60) + inputSeconds + inSecFrames); 
    double totalShiftSeconds = ((shiftAmountHours * 60 * 60) + (shiftAmountMinutes * 60) + shiftAmountSeconds + shiftSecFrames); 

    //if our current time stamp is less than our shift then we will get a negative number when we shift it 
    if (totalShiftSeconds > totalCurrentSeconds)
    {
        return false; //this means that the current time stamp is less than the shift amount so it should be deleted! 
    }
    return true; //otherwise return true    
}

//function for manipulating the time stamp values from the file
std::string OutputWindow::editTimeStampValues(int shiftAmountHours, int shiftAmountMinutes, int shiftAmountSeconds, int shiftAmountFrames, std::string hoursHolder, std::string minutesHolder, std::string secondsHolder, std::string framesHolder)
{
    string output = ""; 

    int inputHours = stoi(hoursHolder); 
    int inputMinutes = stoi(minutesHolder);
    int inputSeconds = stoi(secondsHolder);
    int inputFrames = stoi(framesHolder);

    int HoursOutput = inputHours;
    int MinutesOutput = inputMinutes; 
    int SecondsOutput = inputSeconds;
    int FramesOutput = inputFrames;

    if (FramesOutput < shiftAmountFrames) //if we need to subtract more frames than we have 
    {
        if (inputSeconds != 0)
        {
            SecondsOutput--; //subtract one from our ourput seconds
        }
        else
        {
            MinutesOutput--; //subtract one from minutes 
            SecondsOutput = 59; //redistribute the remaining seconds
        }

        FramesOutput += 1000; 
    }
    
    FramesOutput = (FramesOutput - shiftAmountFrames); 

    if (SecondsOutput < shiftAmountSeconds) //if we need to subtract more frames than we have 
    {
        if (MinutesOutput != 0) 
        {
            MinutesOutput--; //subtract one from our ourput minutes
        }
        else
        {
            HoursOutput--; //subtract one from hours 
            MinutesOutput = 59; //redistribute the remaining minutes
        }

        SecondsOutput += 60; 
    }

    SecondsOutput = (SecondsOutput - shiftAmountSeconds);

    if (MinutesOutput < shiftAmountMinutes) //if we need to subtract more frames than we have 
    {
        if (HoursOutput != 0)
        {
            HoursOutput--; //subtract one from our ourput minutes
        }
        else //if hours is zero and we subtract more minutes than we have we need to error because there is no larger time stamp
        {
            string error = "attempt to subtract more minutes than is possible, check time shift value and try again!";
            QString outError = QString::fromStdString(error);
            palette->setColor(QPalette::Text,Qt::red);
            sysOutput->setPalette(*palette);
            sysOutput->setText(ErrorMsg); 
        }

        MinutesOutput += 60; 
    }

    MinutesOutput = (MinutesOutput - shiftAmountMinutes);

    if (HoursOutput < shiftAmountHours)
    {
        string error = "attempt to subtract more hours than is possible, check time shift value and try again!";
        QString outError = QString::fromStdString(error);
        palette->setColor(QPalette::Text,Qt::red);
        sysOutput->setPalette(*palette);
        sysOutput->setText(ErrorMsg); 
    }
    else
    {
        HoursOutput = (HoursOutput - shiftAmountHours);
    }

    output = output + to_string(HoursOutput); 
    output = output + ":";

    if (MinutesOutput < 10)
    {
        output = output + "0";
    }

    output = output + to_string(MinutesOutput);
    output = output + ":";

    if (SecondsOutput < 10)
    {
        output = output + "0";
    }

    output = output + to_string(SecondsOutput);
    output = output + ".";

    if (FramesOutput < 10)
    {
        output = output + "00";
    }
    else if (FramesOutput < 100)
    {
        output = output + "0";
    }

    output = output + to_string(FramesOutput);

    return output; 
}

void OutputWindow::clearFile(std::string StdOutFile)
{   
    //open the file in truncate mode so that way if there is anything in the file when we start it gets overwritten
    ofstream ofs; 
    ofs.open(StdOutFile, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}