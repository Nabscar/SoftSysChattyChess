
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void communicationFunction(int clientSocket);

int main(int argc, char const *argv[])
{
    int clientSocket, connfd;
    struct sockaddr_in serverAddress;
    struct hostent* serverAddr;

    if (argc <2) { //checks that user input server ip address
      printf("Missing server ip address");
      exit(1);
    }

    serverAddr = gethostbyname(argv[1]); //to get server ip address from command line

    // socket create and varification
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    memset((char*)&serverAddress, 0, sizeof(serverAddress));

    // assign IP, PORT
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    memcpy(&serverAddress.sin_addr,serverAddr->h_addr,serverAddr->h_length);

    // connect the client socket to server socket
    if (connect(clientSocket, (SA*)&serverAddress, sizeof(serverAddress)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    communicationFunction(clientSocket);

    // close the socket
    close(clientSocket);
}



void communicationFunction(int clientSocket)
{
    char buff[MAX];
    int n;
    for (;;) {
        // clear buffer and prompt user for input
        bzero(buff, MAX);
        printf("Enter the string : ");
        n = 0;
        // loop through chars to get input
        while ((buff[n++] = getchar()) != '\n');
        // write input to clientSocket so server can read
        write(clientSocket, buff, MAX);
        // if input is exit then clint leaves
        if ((strncmp("exit", buff, 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
        // clear buffer
        bzero(buff, MAX);
        // read buffer from server
        read(clientSocket, buff, MAX);
        //print server buffer
        printf("From Server : %s", buff);
        // if server exits then client also exits
        if ((strncmp("exit", buff, 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}
