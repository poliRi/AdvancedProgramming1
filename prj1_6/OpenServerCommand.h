#include "interface.h"

class OpenServerCommand : public Command {

private:
    pthread_t thread;
    int result;

public:
    OpenServerCommand();
    void doCommand(vector<string> args);
    int doServer(int port, int rate);
    int pthread_create(pthread_t *THREAD_ID, void *ATTR, void *(*THREAD_FUNC)(void *), void *ARG);
};
