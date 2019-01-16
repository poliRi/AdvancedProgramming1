#include "SearcherSolver.h"
#include "Utils.h"
#include "Matrix.h"

SearcherSolver::SearcherSolver(Searcher* searcher) {
    this->searcher = searcher;
}

//calls the search method of the class member searcher and returns answer
string SearcherSolver::solve(vector<string> problem) {
    vector<vector<int>> matrix = {};
    for (int i = 0; i < problem.size() - 2; i++) {
        vector<string> s = Utils::Split(problem[i], ",");
        vector<int> row = {};
        for (int j = 0; j < s.size(); j++) {
            row.push_back(stoi(s[j]));
        }
        matrix.push_back(row);
    }
    Searchable* searchable = new Matrix(matrix);
    vector<string> s = Utils::Split(problem[problem.size() - 2], ",");
    pair<int, int> source = {stoi(s[0]), stoi(s[1])};
    s = Utils::Split(problem[problem.size() - 1], ",");
    pair<int, int> destination = {stoi(s[0]), stoi(s[1])};
    //if the source is out of range
	if (!searchable->isValid(source.first, source.second) ||
	!searchable->isValid(destination.first, destination.second)){
		return "source or the destination is invalid";
	}
	//either the source or the destination is blocked
	if (!searchable->isUnBlocked(source.first, source.second) ||
			!searchable->isUnBlocked(destination.first, destination.second)) {
		return "source or the destination is blocked";
	}
	//if the destination cell is the same as source cell
	if (source.first == destination.first && source.second == destination.second) {
		return "We are already at the destination";
	}
    return searcher->search(searchable, source, destination);
}
