#include "interface.h"

class DataReaderServer {

    private:
        int port;
        int rate;

    public:
        DataReaderServer(int port, int rate);
        int doServer();
};
