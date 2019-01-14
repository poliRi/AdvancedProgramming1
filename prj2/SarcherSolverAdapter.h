//
// Created by Polina Rabinovich on 14/01/2019.
//

#ifndef PRJ2_SARCHERSOLVERADAPTER_H
#define PRJ2_SARCHERSOLVERADAPTER_H

#include "interface.h"
#include "Utils.h"
#include <vector>
#include <iostream>


class SarcherSolverAdapter : public Solver{

    Searcher* s;
public:
    SarcherSolverAdapter(Searcher *searcher);
    virtual string solve(vector<string> problem);
};


#endif //PRJ2_SARCHERSOLVERADAPTER_H
