#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

using namespace std;

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    if (argc < 3) {
        cout << "usage " << argv[0] << "hostname port" << endl;
        exit(0);
    }

    portno = atoi(argv[2]);

    //Create a socket point
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout <<"ERROR opening socket";
        exit(1);
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        cout << "ERROR, no such host" << endl;
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    //Now connect to the server
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "ERROR connecting";
        exit(1);
    }

    string message = "";

    while (true) {
        message = "";
        //Now ask for a message from the user, this message will be read by server
        cout << "Please enter the message: ";
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        strcat(buffer, "\r\n");

        //Send message to the server
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            cout << "ERROR writing to socket";
            exit(1);
        }

        for (int i = 0; buffer[i] != '\n'; i++) {
            message += buffer[i];
        }

	if (message == "end") {
		break;
	}

        //Now read server response
        bzero(buffer,256);
        n = read(sockfd, buffer, 255);
        if (n < 0) {
            cout << "ERROR reading from socket";
            exit(1);
        }
        //print server response
        cout << buffer << endl;
    }
    return 0;
}
