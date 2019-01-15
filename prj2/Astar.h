#ifndef _ASTAR_H
#define _ASTAR_H
#include "interface.h"

class Astar : public Searcher {

    public:
        Astar();
        double calculateHValue(int row, int col, pair<int, int> dest);
        string tracePath(vector<vector<ANode>>, pair<int, int> dest);
        string search(Searchable* area, pair<int, int> source, pair<int, int> destination);
};

#endif // _ASTAR_H
