#include <stack>
#include "Astar.h"

Astar::Astar() {}

// A Utility Function to calculate the 'h' heuristics.
double Astar::calculateHValue(int row, int col, pair<int, int> dest) {
	// Return using the distance formula
	return ((double)sqrt ((row-dest.first) * (row-dest.first) + (col-dest.second) * (col-dest.second)));
}

// A Utility Function to trace the path from the source
// to destination
void Astar::tracePath(vector<vector<cell>> cellDetails, pair<int, int> dest) {
	cout << "The Path is ";
	int row = dest.first;
	int col = dest.second;

	stack<pair<int, int>> Path;

	while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
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
int Astar::search(Searchable* area, pair<int, int> source, pair<int, int> destination) {
	// If the source is out of range
	if (!area->isValid(source.first, source.second)){
		cout << "Source is invalid" << endl;
		return -1;
	}

	// If the destination is out of range
	if (!area->isValid(destination.first, destination.second)) {
		cout << "Destination is invalid" << endl;
		return -1;
	}

	// Either the source or the destination is blocked
	if (!area->isUnBlocked(source.first, source.second) ||
			!area->isUnBlocked(destination.first, destination.second)) {
		cout << "Source or the destination is blocked" << endl;
		return -1;
	}

	// If the destination cell is the same as source cell
	if (source.first == destination.first && source.second == destination.second) {
		cout << "We are already at the destination" << endl;
		return 0;
	}

	vector<vector<int>> matrix = area->getArea();

	// Create a closed list and initialise it to false which means
	// that no cell has been included yet
	// This closed list is implemented as a boolean 2D array
	int rows = area->getSize().first;
    int cols = area->getSize().second;
	bool closedList[rows][cols];
	memset(closedList, false, sizeof(closedList));

	// Declare a 2D array of structure to hold the details
	//of that cell
	vector<vector<cell>> cellDetails;

    int i , j;

	for (i = 0; i < rows; i++) {
        vector<cell> v = {};
		for (j = 0; j < cols; j++) {
            cell c;
            c.f = FLT_MAX;
            c.g = INT_MAX;
            c.h = FLT_MAX;
            c.dist = INT_MAX;
            c.parent_i = -1;
            c.parent_j = -1;
            v.push_back(c);
		}
		cellDetails.push_back(v);
	}

	// Initialising the parameters of the starting node
	i = source.first, j = source.second;
	cellDetails[i][j] = {0.0, 0, 0.0, 0, i, j};

	// Creating a shortcut for pair<int, pair<int, int>> type
    typedef pair<double, pair<int, int>> pPair;

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
	openList.insert(make_pair(0.0, make_pair(i, j)));

	// We set this boolean value as false as initially
	// the destination is not reached.
	bool foundDest = false;

	while (!openList.empty()) {
		pPair p = *openList.begin();

		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the closed list
		closedList[p.second.first][p.second.second] = true;

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

        int rowDirection[] = {0, 1, 0, -1};
        int colDirection[] = {1, 0, -1, 0};

		for (int k = 0; k < 4; k++) {
            int i = p.second.first + rowDirection[k];
            int j = p.second.second + colDirection[k];
            // Only process this cell if this is a valid one
            if (area->isValid(i, j)) {
                // If the destination cell is the same as the
                // current successor
                if (i == destination.first && j == destination.second) {
                    // Set the Parent of the destination cell
                    cellDetails[i][j].parent_i = p.second.first;
                    cellDetails[i][j].parent_j = p.second.second;
                    tracePath (cellDetails, destination);
                    foundDest = true;
                    return cellDetails[p.second.first][p.second.second].dist + matrix[i][j];
                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                else if ((!closedList[i][j])&&(area->isUnBlocked(i, j))) {
                    gNew = cellDetails[p.second.first][p.second.second].g + matrix[i][j];
                    hNew = 0;
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //			 OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i][j].f == FLT_MAX || cellDetails[i][j].f > fNew) {
                        openList.insert(make_pair(fNew, make_pair(i, j)));

                        // Update the details of this cell
                        cellDetails[i][j].f = fNew;
                        cellDetails[i][j].g = gNew;
                        cellDetails[i][j].h = hNew;
                        cellDetails[i][j].dist = cellDetails[p.second.first][p.second.second].dist + matrix[i][j];
                        cellDetails[i][j].parent_i = p.second.first;
                        cellDetails[i][j].parent_j = p.second.second;
                    }
                }
            }
		}
	}

	// When the destination cell is not found and the open
	// list is empty, then we conclude that we failed to
	// reach the destiantion cell. This may happen when the
	// there is no way to destination cell (due to blockages)
	if (!foundDest) {
		cout << "Failed to find the Destination Cell" << endl;
        return -1;
	}
}


