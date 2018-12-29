#include "ConnectCommand.h"
#include "Utils.h"

/*
ConnectCommand: constructor
*/
ConnectCommand::ConnectCommand(map<string, double> &symbolTable, map<string, string> &pathTable,
map<string, bool> &isAssigned) {
    //hold a reference to the main symbol tables of the program
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
    this->isAssigned = &isAssigned;
}

/*
receives ip address and destination port,
then opens a thread with a client socket that communicates with the simulator
*/
void ConnectCommand::doCommand(vector<string> args) {
    //if the number of arguments is invalid throw exeception
    if (args.size() != 2) {
        throw invalid_argument("invalid number of arguments");
    }
    //get ip and port
    string ip = args[0];
    int port =  stoi(args[1]);
    //check for validity of the given ip. split the number in between the "." characters
    vector<string> numbers = Utils::Split(args[0], ".");
    //throw execption if wrong amount of numbers was given
    if (numbers.size()!=4) {
       throw invalid_argument("invalid ip address");
    } else {
        //for each number, check if it is in the right range
        for (int i = 0; i < 4; i++) {
            int num = stoi(numbers[i]);
            if ((num < 0)||(num > 255)) {
               throw invalid_argument("invalid ip address");
            }
        }
    }
    //check for a valid range of the port
    if ((port < 2000)||(port > 65535)) {
       throw invalid_argument("invalid port number");
    }
    //create a struct in which the program transmits the ip, portno, and symbol tables to the thread it opens
    struct ClientParams* cp = new ClientParams();
    cp->ip = ip;
    cp->port = port;
    cp->symbolT = symbolTable;
    cp->pathT = pathTable;
    cp->assigned = isAssigned;
    //open a thread with the createSocket function
    pthread_t sock;
    pthread_create(&sock, nullptr, createSocket, (void *)cp);
}

/*
creates a client socket whose purpose is to send commands to the simulator. holds reference to the symbol
tables in order to get the variable values in real time
*/
void *ConnectCommand::createSocket(void *arg) {
    struct ClientParams* cp = (struct ClientParams*) arg;
    //socket details declaration
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    //messages will be holded in the buffer
    char buffer[256];
    //get the symbol tables and destination port number
    map<string, double> *symbolT = cp->symbolT;
    map<string, string> *pathT = cp->pathT;
    map<string, bool> *assigned = cp->assigned;
    portno = cp->port;

    //create a socket point
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout <<"ERROR opening socket";
        exit(1);
    }
    //get the destination ip address
    server = gethostbyname(cp->ip.c_str());
    if (server == NULL) {
        cout << "ERROR, no such host" << endl;
        exit(0);
    }
    //get the server details
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    //now connect to the server
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "ERROR connecting";
        exit(1);
    }
    //start communicating by sending and receiving regulary
    while (true) {
        map<string, string>::iterator iter;
        string varName = "";
        string message = "";
        //for each variable
        for (iter = pathT->begin(); iter != pathT->end(); ++iter) {
            //clear buffer
            bzero(buffer,256);
            //get the variable name
            varName = iter->first;
            //if the variable has been assigned to a new value, set it in the simulator
            if (assigned->find(varName)->second == true) {
                //get the variable path and value from the symbol tables, then construct a message
                message = "set " + iter->second + " " + to_string(symbolT->find(varName)->second);
                strcpy(buffer, message.c_str());
                strcat(buffer, "\r\n");

                //send message to the server
                n = write(sockfd, buffer, strlen(buffer));
                if (n < 0) {
                    cout << "ERROR writing to socket";
                    exit(1);
                }

                //read server response
                bzero(buffer,256);
                n = read(sockfd, buffer, 255);
                if (n < 0) {
                    cout << "ERROR reading from socket";
                    exit(1);
                }
            }
            //finish the assignment proccess by setting the assignment flag to false
            assigned->find(varName)->second = false;
        }
    }
    //clear allocated memory and exit the thread
    delete cp;
    pthread_exit(nullptr);
}
