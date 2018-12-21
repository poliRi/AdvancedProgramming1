#include "interface.h"

class OpenServerCommand : public Command {
    typedef struct {
        int port;
        int rate;
    } MyParams;

private:
    pthread_t thread;
    int result;

public:
    OpenServerCommand();

    void doCommand(vector<string> args);

    static void *doServer(void *);

};