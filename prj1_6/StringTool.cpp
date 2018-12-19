

#include "StringTool.h"

//template <class T>
string toString(float inputNumber)
{
    ostringstream oss;

    oss << inputNumber;

    return oss.str();
}

string trim(string inputText)
{
    string::iterator end_position = std::remove(inputText.begin(), inputText.end(), ' ');
    inputText.erase(end_position, inputText.end());

    return inputText;
}

string getReplaceInstances(string inputText, string existingText, string replacementText)
{
    int index;
    index = 0;

    while(inputText.find(existingText) != string::npos)
    {
        cout << inputText << endl;
        int charIndex = inputText.find(existingText, index);
        inputText.insert(charIndex, replacementText);
        //.size vs .length
        index = charIndex + replacementText.length();
    }

    return inputText;
}
//clipbaord anagz
void replaceInstances(string &inputText, string existingText, string replacementText)
{
    int index;
    index = 0;

    while(inputText.find(existingText) != string::npos)
    {
        int charIndex = inputText.find(existingText, index);
        cout << "df " << charIndex << endl;

        if(charIndex != -1)
        {
            inputText.insert(charIndex, replacementText);
        //.size vs .length
            index = charIndex + replacementText.length() + 1;

            inputText.erase(charIndex + replacementText.length(), 1);
        }
        else
        {
            break;
        }
    }
}

void split(vector<string>& outputArray, const char* inputText, char* delimeter)
{
    const int strLength = strlen(inputText);

    char textArr[strLength];

    strcpy(textArr, inputText);

    char* tokChar = strtok(textArr, delimeter);

    while(tokChar)
    {
        outputArray.push_back(tokChar);

        tokChar = strtok(NULL, delimeter);
    }
}//9650696923
//breakpoitns extend stirng or make vstring

bool isAlpha(char testingChar)
{
    return (((int)testingChar > 64 && (int)testingChar < 91) || ((int)testingChar > 96 && (int)testingChar < 123))? true: false;
}

bool isDigit(char testingChar)
{
    return ((int)testingChar >= 48 && (int)testingChar <= 57)? true: false;
}