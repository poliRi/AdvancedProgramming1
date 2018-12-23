#ifndef UTILS_H
#define UTILS_H
#include "interface.h"

class Utils {

    public:
        Utils();
        static vector<string> Split(string str, string delimeter);
        static vector<string> Split(ifstream  &file, string delimeter);
};

#endif // UTILS_H
