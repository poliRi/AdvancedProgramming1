#include "interface.h"

class OpenServerCommand : public Command {

    private:


    public:
        OpenServerCommand();
        void doCommand(vector<string> args);
};
