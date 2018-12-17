#include "interface.h"

class ConnectCommand : public Command {

    private:


    public:
        ConnectCommand();
        void doCommand(vector<string> args);
};
