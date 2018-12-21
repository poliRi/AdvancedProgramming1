#ifndef REVERSI_CLIENT_H
#define REVERSI_CLIENT_H

#include <string>

using namespace std;

class Client {
private:


    // The IP of the server.
    string serverIP_;

    // The port of the server.
    int serverPort_;

    // The client's socket.
    int clientSocket_;


public:

    // Constructor for the client.
    Client(string serverIP, int serverPort);


    // Destructor for the client.
    ~Client();


    // Establishes a connection with the server.
    void connectToServer();


    int getClientSocket_() const;


};

#endif //REVERSI_CLIENT_H