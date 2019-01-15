#ifndef _BFS_H
#define _BFS_H
#include "interface.h"

class BFS : public Searcher {

    public:
        BFS();
        string tracePath(vector<vector<pair<int, int>>> parentIndex, pair<int, int> dest);
        string search(Searchable* area, pair<int, int> source, pair<int, int> destination);
};

#endif // _BFS_H
