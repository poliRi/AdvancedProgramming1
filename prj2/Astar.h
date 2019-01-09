#ifndef _ASTAR_H
#define _ASTAR_H
#include "interface.h"

#define ROW 10
#define COL 10

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int>> pPair;

// a cell structure used in Astar
struct cell {
	// Row and Column index of its parent
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	int parent_i, parent_j;
	// f = g + h
	double f, g, h;
};

class Astar {

    public:
        Astar();
        bool isValid(int row, int col);
        bool isUnBlocked(int grid[][COL], int row, int col);
        bool isDestination(int row, int col, Pair dest);
        double calculateHValue(int row, int col, Pair dest);
        void tracePath(cell cellDetails[][COL], Pair dest);
        void aStarSearch(int grid[][COL], Pair src, Pair dest);
};

#endif // _ASTAR_H
