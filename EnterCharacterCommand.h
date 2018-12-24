#ifndef ENTERCHARACTERCOMMAND_H
#define ENTERCHARACTERCOMMAND_H
#include "interface.h"

/*
class EnterCharacterCommand is in charge of getting a char input from the user
for the purpose of pausing the program
*/
class EnterCharacterCommand : public Command {

    public:
        EnterCharacterCommand();
        void doCommand(vector<string> args);
};

#endif // ENTERCHARACTERCOMMAND_H

