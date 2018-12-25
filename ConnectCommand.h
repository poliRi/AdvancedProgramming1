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

    public:
        ConnectCommand(map<string, double> &symbolTable, map<string, string> &pathTable);
        void doCommand(vector<string> args);
        static void* createSocket(void *arg);
};

/*
this is a struct in which the program transmits arguments to the thread it opens
*/
struct ClientParams {
    string ip;
    int port;
    map<string, double> *symbolT;
    map<string, string> *pathT;
};

#endif // CONNECTCOMMAND_H
