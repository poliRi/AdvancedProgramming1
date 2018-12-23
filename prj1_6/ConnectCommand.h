#ifndef CONNECTCOMMAND_H
#define CONNECTCOMMAND_H
#include "interface.h"

class ConnectCommand : public Command {

    public:
        ConnectCommand();
        void doCommand(vector<string> args);
};

#endif // CONNECTCOMMAND_H
