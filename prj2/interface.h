#ifndef INTERFACE_H
#define INTERFACE_H
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

#endif
