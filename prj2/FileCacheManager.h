#ifndef _FILECACHEMANAGER_H
#define _FILECACHEMANAGER_H
#include "interface.h"

class FileCacheManager : public CacheManager {

    map<string, string> solutions;

    public:
        FileCacheManager();
        bool contains(string problem);
        string getSolution(string problem);
        void saveSolution(string problem, string solution);
};

#endif // _FILECACHEMANAGER_H

