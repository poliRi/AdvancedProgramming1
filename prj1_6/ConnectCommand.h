#ifndef CONNECTCOMMAND_H
#define CONNECTCOMMAND_H
#include "interface.h"

/*
class ConnectCommand is in charge of creating a connection to the simulator as a client,
and send it the instructions that were given
*/
class ConnectCommand : public Command {

    private:
        map<string, double> *symbolTable;
        map<string, string> *pathTable;
        map<string, bool> *isAssigned;

    public:
        ConnectCommand(map<string, double> &symbolTable, map<string, string> &pathTable,
        map<string, bool> &isAssigned);
        void doCommand(vector<string> args);
        static void* createSocket(void *arg);
};

/*
this is a struct in which the doCommand() transmits arguments to the thread it opens
*/
struct ClientParams {
    string ip;
    int port;
    map<string, double> *symbolT;
    map<string, string> *pathT;
    map<string, bool> *assigned;
};

#endif // CONNECTCOMMAND_H
