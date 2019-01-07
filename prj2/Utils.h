#ifndef UTILS_H
#define UTILS_H
#include "interface.h"

/*
class Utils is used as an assistant for splitting words into vector of strings
*/
class Utils {

    public:
        Utils();
        static vector<string> Split(string str, string delimeter);
        static vector<string> Split(ifstream  &file, string delimeter);
};

#endif // UTILS_H
