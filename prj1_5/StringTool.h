

#ifndef __ApaMath__StringTools__
#define __ApaMath__StringTools__

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//template <class T>
string toString(float inputNumber);
string trim(string inputText);
string getReplaceInstances(string inputText, string existingText, string replacementText);
//checat enigen
void replaceInstances(string &inputText, string existingText, string replacementText);
void split(vector<string>& outputArray, const char* inputText, char* delimeter);


bool isAlpha(char testingChar);
bool isDigit(char testingChar);


#endif /* defined(__ApaMath__StringTools__) */
