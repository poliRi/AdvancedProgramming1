#include "OpenServerCommand.h"
#include "Utils.h"

/*
OpenServerCommand: constructor
*/
OpenServerCommand::OpenServerCommand(map<string, double> &symbolTable,  map<string, string> &pathTable,
map<string, bool> &isAssigned) {
    //hold a reference to the main symbol tables of the program
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
    this->isAssigned = &isAssigned;

}

/*
receives port address and rate of data sending,
then opens a thread with a server socket that communicates with the simulator
*/
void OpenServerCommand::doCommand(vector<string> args) {
    //if the number of arguments is invalid throw exeception
    if (args.size() != 2) {
        throw invalid_argument("invalid number of arguments");
    }
    //get port and rate
    int port = stoi(args[0]);
    int rate = (stoi(args[1]))*10000;
    //check for a valid range of the port
    if ((port < 2000)||(port > 65535)) {
       throw invalid_argument("invalid port number");
    }
    //check if the rate is valid
    if (rate <= 0) {
        throw invalid_argument("invalid rate");
    }
    //create a struct in which the program transmits the portno, rate and symbol table to the thread it opens
    struct serverParams* sp = new serverParams();
    sp->port = port;
    sp->rate = rate;
    sp->symbolT = symbolTable;
    sp->pathT = pathTable;
    sp->assigned = isAssigned;
    //open a thread with the createSocket function
    pthread_t sock;
    pthread_create(&sock, nullptr, createSocket, (void *)sp);
}

/*
creates a server socket whose purpose is to get variables values from the simulator.
holds reference to the symbol table in order to update the variable values in real time
*/
void *OpenServerCommand::createSocket(void *arg) {
    struct serverParams* sp = (struct serverParams*) arg;
    //socket details declaration
    int sockfd, newsockfd, portno, clilen, rate;
    //messages will be holded in the buffer
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    int  n;

    //get the symbol tables and rate
    map<string, double> *symbolT = sp->symbolT;
    map<string, string> *pathT = sp->pathT;
    map<string, bool> *assigned = sp->assigned;
    rate = sp->rate;

    //first call to socket() function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout <<"ERROR opening socket";
        exit(1);
    }

    //initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = sp->port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //now bind the host address using bind() call
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        cout << "ERROR on binding";
        exit(1);
    }

    //start listening for clients
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    //accept actual connection from the client
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
    if (newsockfd < 0) {
        cout << "ERROR on accept";
        exit(1);
    }
    //if connection is established then start communicating
    while (true) {
        //read the message
        bzero(buffer,1024);
        n = read(newsockfd,buffer,1023);

        //if there is no message
        if (n < 0) {
            close(newsockfd);
            close(sockfd);
            cout << "socket closed";
            exit(1);
        }

        //split the values in the message
        vector<string> v = Utils::Split(buffer, ",");
        //create a map between all the possible variables paths and their current values
        map<string,double> values = {};
        values.insert(pair<string,double>("/instrumentation/airspeed-indicator/indicated-speed-kt", stod(v[0])));
        values.insert(pair<string,double>("/instrumentation/altimeter/indicated-altitude-ft", stod(v[1])));
        values.insert(pair<string,double>("/instrumentation/altimeter/pressure-alt-ft", stod(v[2])));
        values.insert(pair<string,double>("/instrumentation/attitude-indicator/indicated-pitch-deg", stod(v[3])));
        values.insert(pair<string,double>("/instrumentation/attitude-indicator/indicated-roll-deg", stod(v[4])));
        values.insert(pair<string,double>("/instrumentation/attitude-indicator/internal-pitch-deg", stod(v[5])));
        values.insert(pair<string,double>("/instrumentation/attitude-indicator/internal-roll-deg", stod(v[6])));
        values.insert(pair<string,double>("/instrumentation/encoder/indicated-altitude-ft", stod(v[7])));
        values.insert(pair<string,double>("/instrumentation/encoder/pressure-alt-ft", stod(v[8])));
        values.insert(pair<string,double>("/instrumentation/gps/indicated-altitude-ft", stod(v[9])));
        values.insert(pair<string,double>("/instrumentation/gps/indicated-ground-speed-kt", stod(v[10])));
        values.insert(pair<string,double>("/instrumentation/gps/indicated-vertical-speed", stod(v[11])));
        values.insert(pair<string,double>("/instrumentation/heading-indicator/indicated-heading-deg", stod(v[12])));
        values.insert(pair<string,double>("/instrumentation/magnetic-compass/indicated-heading-deg", stod(v[13])));
        values.insert(pair<string,double>("/instrumentation/slip-skid-ball/indicated-slip-skid", stod(v[14])));
        values.insert(pair<string,double>("/instrumentation/turn-indicator/indicated-turn-rate", stod(v[15])));
        values.insert(pair<string,double>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
        stod(v[16])));
        values.insert(pair<string,double>("/controls/flight/aileron", stod(v[17])));
        values.insert(pair<string,double>("/controls/flight/elevator", stod(v[18])));
        values.insert(pair<string,double>("/controls/flight/rudder", stod(v[19])));
        values.insert(pair<string,double>("/controls/flight/flaps", stod(v[20])));
        values.insert(pair<string,double>("/controls/engines/current-engine/throttle", stod(v[21])));
        values.insert(pair<string,double>("/engines/engine/rpm", stod(v[22])));
        //now updated the current existed variables values
        map<string, string>::iterator iter;
        string varName = "";
        string pathName = "";
        double value;
        //for each variable in the path table, that was declared in the program
        for (iter = pathT->begin(); iter != pathT->end(); ++iter) {
            varName = iter->first;
            pathName = iter->second;
            /*
            check whether the variable is available to be modified,
            or is currently in process of being assigned to a new value
            */
            bool varIsAssigned = assigned->find(varName)->second;
            //if it is available
            if (varIsAssigned == false) {
                //get it's new value from the values map
                value = values.find(pathName)->second;
                //update it's value in the symbol table
                (symbolT->find(varName)->second) = value;
            }
        }

        //write a response to the client
        n = write(newsockfd,"I got your message",18);
        if (n < 0) {
            cout << "ERROR writing to socket";
            exit(1);
        }
        //sleep for a while
        usleep(rate);
    }
    //clear allocated memory and exit the thread
    delete sp;
    pthread_exit(nullptr);
}
