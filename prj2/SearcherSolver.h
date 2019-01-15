#ifndef _SEARCHERSOLVER_H
#define _SEARCHERSOLVER_H
#include "interface.h"

class SearcherSolver : public Solver {

    Searcher* searcher;

    public:
        SearcherSolver(Searcher* searcher);
        string solve(vector<string> problem);
};

#endif // _SEARCHERSOLVER_H
