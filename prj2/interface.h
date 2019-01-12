#ifndef _INTERFACE_H
#define _INTERFACE_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include<map>
#include <fstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include<list>
#include <queue>
#include <climits>
#include<bits/stdc++.h>

using namespace std;

/*
ClientHandler interface. has the handleClient method
*/
class ClientHandler {

    public:
        virtual void handleClient(int sock) = 0;
};

/*
Solver interface. has the solve method
*/
class Solver {

    public:
        virtual string solve(string problem) = 0;
};

/*
CacheManager interface. in charge of saving new solutions for different problems,
or loading solutions for problems that are already exist
*/
class CacheManager {

    public:
        virtual bool contains(string problem) = 0;
        virtual string getSolution(string problem) = 0;
        virtual void saveSolution(string problem, string solution) = 0;
};

class Searchable {

    public:
        virtual bool isValid(int row, int col) = 0;
        virtual bool isUnBlocked(int row, int col) = 0;
        virtual vector<vector<int>> getArea() = 0;
        virtual pair<int, int> getSize() = 0;
};

/*
Searcher interface. has the search method
*/
class Searcher {

    public:
        virtual int search(Searchable* area, pair<int, int> source, pair<int, int> destination) = 0;
};

/*
node for current location and distance from source location
*/
struct Node {
	int row;
	int col;
	int dist;
};

#define X -1

#define ROW 10
#define COL 10

#endif // _INTERFACE_H
