#ifndef OPENSERVERCOMMAND_H
#define OPENSERVERCOMMAND_H
#include "interface.h"

/*
class OpenServerCommand is in charge of creating a connection to the simulator as a server,
that receives values of variables from the simulator
*/
class OpenServerCommand : public Command {

    private:
        map<string, double> *symbolTable;
        map<string, string> *pathTable;

    public:
        OpenServerCommand(map<string, double> &symbolTable, map<string, string> &pathTable);
        void doCommand(vector<string> args);
        static void* createSocket(void *arg);
};

/*
this is a struct in which the doCommand() transmits arguments to the thread it opens
*/
struct serverParams {
    int port;
    int rate;
    map<string, double> *symbolT;
    map<string, string> *pathT;
};

#endif // OPENSERVERCOMMAND_H
