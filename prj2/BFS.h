#ifndef _BFS_H
#define _BFS_H
#include "interface.h"

class BFS : public Searcher {

    public:
        BFS();
        int search(Searchable* area, pair<int, int> source, pair<int, int> destination);
};

#endif // _BFS_H
