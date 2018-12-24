#ifndef BINDCOMMAND_H
#define BINDCOMMAND_H
#include "interface.h"

/*
class BindCommand is in charge of binding a given variable's value to a given path
*/
class BindCommand : public Command {

    private:
        map<string, string> *pathTable;

    public:
        BindCommand(map<string, string> &pathTable);
        void doCommand(vector<string> args);
};

#endif // BINDCOMMAND_H

