#ifndef PRINTCOMMAND_H
#define PRINTCOMMAND_H
#include "interface.h"

/*
class PrintCommand is in charge of printing a given content to the screen
*/
class PrintCommand : public Command {

    private:
        map<string, double> *symbolTable;

    public:
        PrintCommand(map<string, double> &symbolTable);
        void doCommand(vector<string> args);
};

#endif // PRINTCOMMAND_H
