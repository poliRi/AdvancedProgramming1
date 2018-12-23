#ifndef OPENSERVERCOMMAND_H
#define OPENSERVERCOMMAND_H
#include "interface.h"

class OpenServerCommand : public Command {
typedef struct{
    int port;
    int rate;
}MyParams;

private:
    int result;
    map<string, double> *symbolTable;
    map<string, string> *pathTable;

public:
    OpenServerCommand(map<string, double> &symbolTable, map<string, string> &pathTable);
    void doCommand(vector<string> args);
    static void* doServer(void* arg);
};

#endif // OPENSERVERCOMMAND_H
