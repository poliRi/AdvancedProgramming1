#ifndef _STRINGREVERSER_H
#define _STRINGREVERSER_H
#include "interface.h"

class StringReverser : public Solver {

    public:
        StringReverser();
        string solve(vector<string> problem);
};

#endif // _STRINGREVERSER_H
