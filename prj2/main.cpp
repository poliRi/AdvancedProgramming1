#include "interface.h"
#include "ServerSide.h"

using namespace boot;

int main(int argc, char *argv[]) {
    int port = stoi(argv[1]);
    (new Main())->main(port);

    return 0;
}
