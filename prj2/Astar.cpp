#include "Astar.h"

Astar::Astar() {}

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool Astar::isValid(int row, int col) {
	// Returns true if row number and column number
	// is in range
	return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool Astar::isUnBlocked(int grid[][COL], int row, int col) {
	// Returns true if the cell is not blocked else false
	return (grid[row][col] != 0);
}

// A Utility Function to check whether destination cell has
// been reached or not
bool Astar::isDestination(int row, int col, Pair dest) {
	return (row == dest.first && col == dest.second);
}

// A Utility Function to calculate the 'h' heuristics.
double Astar::calculateHValue(int row, int col, Pair dest) {
	// Return using the distance formula
	return ((double)sqrt ((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
}

// A Utility Function to trace the path from the source
// to destination
void Astar::tracePath(cell cellDetails[][COL], Pair dest) {
	cout << "The Path is ";
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col )) {
		Path.push (make_pair (row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push (make_pair (row, col));
	while (!Path.empty()) {
		pair<int,int> p = Path.top();
		Path.pop();
		cout << "-> (" << p.first << "," << p.second << ")";
	}
	cout << endl;
}

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
void Astar::aStarSearch(int grid[][COL], Pair src, Pair dest) {
	// If the source is out of range
	if (isValid (src.first, src.second) == false){
		cout << "Source is invalid" << endl;
		return;
	}

	// If the destination is out of range
	if (isValid (dest.first, dest.second) == false) {
		cout << "Destination is invalid" << endl;
		return;
	}

	// Either the source or the destination is blocked
	if (isUnBlocked(grid, src.first, src.second) == false ||
			isUnBlocked(grid, dest.first, dest.second) == false) {
		cout << "Source or the destination is blocked" << endl;
		return;
	}

	// If the destination cell is the same as source cell
	if (isDestination(src.first, src.second, dest) == true) {
		cout << "We are already at the destination" << endl;
		return;
	}

	// Create a closed list and initialise it to false which means
	// that no cell has been included yet
	// This closed list is implemented as a boolean 2D array
	bool closedList[ROW][COL];
	memset(closedList, false, sizeof (closedList));

	// Declare a 2D array of structure to hold the details
	//of that cell
	cell cellDetails[ROW][COL];

	int i, j;

	for (i=0; i<ROW; i++) {
		for (j=0; j<COL; j++) {
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	/*
	Create an open list having information as-
	<f, <i, j>>
	where f = g + h,
	and i, j are the row and column index of that cell
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	This open list is implenented as a set of pair of pair.*/
	set<pPair> openList;

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.insert(make_pair (0.0, make_pair (i, j)));

	// We set this boolean value as false as initially
	// the destination is not reached.
	bool foundDest = false;

	while (!openList.empty()) {
		pPair p = *openList.begin();

		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the closed list
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

        /*
		Generating all the 4 successor of this cell

		Cell-->Popped Cell  (i, j)
		N --> North	        (i-1, j)
		S --> South	        (i+1, j)
		E --> East	        (i, j+1)
		W --> West		    (i, j-1)
        */

		// To store the 'g', 'h' and 'f' of the 4 successors
		double gNew, hNew, fNew;
		for (int k = -1; k <= 1; k++) {
            for (int w = -1; w <= 1; w++) {
                if ((!((i + k == i - 1)&&(j + w == j - 1)))&&(!((i + k == i - 1)&&(j + w == j + 1)))&&
                (!((i + k == i + 1)&&(j + w == j + 1)))&&(!((i + k == i + 1)&&(j + w == j - 1)))) {
                    // Only process this cell if this is a valid one
                    if (isValid(i + k, j + w) == true) {
                        // If the destination cell is the same as the
                        // current successor
                        if (isDestination(i + k, j + w, dest) == true) {
                            // Set the Parent of the destination cell
                            cellDetails[i + k][j + w].parent_i = i;
                            cellDetails[i + k][j + w].parent_j = j;
                            cout << "The destination cell is found" << endl;
                            tracePath (cellDetails, dest);
                            foundDest = true;
                            return;
                        }
                        // If the successor is already on the closed
                        // list or if it is blocked, then ignore it.
                        // Else do the following
                        else if (closedList[i + k][j + w] == false &&
                                isUnBlocked(grid, i + k, j + w) == true) {
                            gNew = cellDetails[i][j].g + 1.0;
                            hNew = calculateHValue (i + k, j + w, dest);
                            fNew = gNew + hNew;

                            // If it isn’t on the open list, add it to
                            // the open list. Make the current square
                            // the parent of this square. Record the
                            // f, g, and h costs of the square cell
                            //			 OR
                            // If it is on the open list already, check
                            // to see if this path to that square is better,
                            // using 'f' cost as the measure.
                            if (cellDetails[i + k][j + w].f == FLT_MAX ||
                                    cellDetails[i + k][j + w].f > fNew) {
                                openList.insert( make_pair(fNew, make_pair(i + k, j + w)));

                                // Update the details of this cell
                                cellDetails[i + k][j + w].f = fNew;
                                cellDetails[i + k][j + w].g = gNew;
                                cellDetails[i + k][j + w].h = hNew;
                                cellDetails[i + k][j + w].parent_i = i;
                                cellDetails[i + k][j + w].parent_j = j;
                            }
                        }
                    }
                }
            }
		}
	}

	// When the destination cell is not found and the open
	// list is empty, then we conclude that we failed to
	// reach the destiantion cell. This may happen when the
	// there is no way to destination cell (due to blockages)
	if (foundDest == false)
		cout << "Failed to find the Destination Cell" << endl;

	return;
}


