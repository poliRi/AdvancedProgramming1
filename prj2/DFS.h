#ifndef _DFS_H
#define _DFS_H
#include "interface.h"

class DFS : public Searcher {

    public:
        DFS();
        int search(Searchable* area, pair<int, int> source, pair<int, int> destination);
};

#endif // _DFS_H

