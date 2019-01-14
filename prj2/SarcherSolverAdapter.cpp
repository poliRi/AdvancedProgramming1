//
// Created by Polina Rabinovich on 14/01/2019.
//

#include "SarcherSolverAdapter.h"

SarcherSolverAdapter::SarcherSolverAdapter(Searcher *searcher) {
    this->s = searcher;
}

string SarcherSolverAdapter::solve(vector<string> problem) {
    vector<vector<int>> matrix;
    for (int i = 0; i < problem.size() - 2; i++) {
        //vector of rows in matrix
        vector<string> row = Utils::Split(problem[i], ",");
        for (int j = 0; j < row.size(); j++){
            matrix[i].push_back(atoi("2"));

        }

    }
    return s->search();
}

