#include "Astar.h"
#include <stack>



Astar::Astar() {}

// A Utility Function to calculate the 'h' heuristics.
double Astar::calculateHValue(int row, int col, pair<int, int> dest) {
	// Return using the distance formula
	return ((double)sqrt ((row-dest.first) * (row-dest.first) + (col-dest.second) * (col-dest.second)));
}

// A Utility Function to trace the path from the source
// to destination
string Astar::tracePath(vector<vector<ANode>> nodeDetails, pair<int, int> dest) {
	int row = dest.first;
	int col = dest.second;
	list<pair<int, int>> Path;
	while (!(nodeDetails[row][col].parent_i == row && nodeDetails[row][col].parent_j == col)) {
		Path.push_front(make_pair(row, col));
		int temp_row = nodeDetails[row][col].parent_i;
		int temp_col = nodeDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}
	Path.push_front(make_pair(row, col));
	string path = "";
	int parentRow = Path.front().first;
	int parentCol = Path.front().second;
	list<pair<int, int>>::iterator it = Path.begin();
	it++;
	for (; it != Path.end(); ++it) {
        row = it->first;
        col = it->second;
        if (row < parentRow) {
            path += "Up, ";
        } else if (row > parentRow) {
            path += "Down, ";
        } else if (col < parentCol) {
            path += "Left, ";
        } else if (col > parentCol) {
            path += "Right, ";
        }
        parentRow = it->first;
        parentCol = it->second;
    }
    path.erase(path.end() - 2, path.end());
    return path;
}

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
string Astar::search(Searchable* area, pair<int, int> source, pair<int, int> destination) {
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
	vector<vector<ANode>> nodeDetails;
	for (int i = 0; i < rows; i++) {
        vector<ANode> v = {};
		for (int j = 0; j < cols; j++) {
            v.push_back({FLT_MAX, INT_MAX, FLT_MAX, INT_MAX, -1, -1});
		}
		nodeDetails.push_back(v);
	}
	// Initialising the parameters of the starting node
	int i = source.first, j = source.second;
	nodeDetails[i][j] = {0.0, 0, 0.0, 0, i, j};
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
            // If the destination cell is the same as the
            // current successor
            if (i == destination.first && j == destination.second) {
                // Set the Parent of the destination cell
                nodeDetails[i][j].parent_i = p.second.first;
                nodeDetails[i][j].parent_j = p.second.second;
                return tracePath(nodeDetails, destination);
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            // Only process this cell if this is a valid one
            if ((!closedList[i][j]) && (area->isValid(i, j)) && (area->isUnBlocked(i, j))) {
                gNew = nodeDetails[p.second.first][p.second.second].g + matrix[i][j];
                hNew = calculateHValue (i, j, destination);
                fNew = gNew + hNew;
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //			 OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (nodeDetails[i][j].f == FLT_MAX || nodeDetails[i][j].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i, j)));
                    // Update the details of this cell
                    nodeDetails[i][j].f = fNew;
                    nodeDetails[i][j].g = gNew;
                    nodeDetails[i][j].h = hNew;
                    nodeDetails[i][j].dist = nodeDetails[p.second.first][p.second.second].dist + matrix[i][j];
                    nodeDetails[i][j].parent_i = p.second.first;
                    nodeDetails[i][j].parent_j = p.second.second;
                }
            }
		}
	}
    return "No possible path found";
}


