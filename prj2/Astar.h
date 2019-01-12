#ifndef _ASTAR_H
#define _ASTAR_H
#include "interface.h"
#include <float.h>
#include <cmath>
#include <set>


// a cell structure used in Astar
struct cell {
	// f = g + h
	double f;
	int g;
	double h;
	int dist;
	// Row and Column index of its parent
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	int parent_i, parent_j;
};

class Astar : public Searcher {

    public:
        Astar();
        double calculateHValue(int row, int col, pair<int, int> dest);
        void tracePath(vector<vector<cell>>, pair<int, int> dest);
        int search(Searchable* area, pair<int, int> source, pair<int, int> destination);
};

#endif // _ASTAR_H
