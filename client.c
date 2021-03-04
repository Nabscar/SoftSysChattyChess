
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        // clear buffer and prompt user for input
        bzero(buff, MAX);
        printf("Enter the string : ");
        n = 0;
        // loop through chars to get input
        while ((buff[n++] = getchar()) != '\n')
            ;
        // write input to sockfd so server can read
        write(sockfd, buff, MAX);
        // if input is exit then clint leaves
        if ((strncmp("exit", buff, 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
        // clear buffer
        bzero(buff, MAX);
        // read buffer from server
        read(sockfd, buff, MAX);
        //print server buffer
        printf("From Server : %s", buff);
        // if server exits then client also exits
        if ((strncmp("exit", buff, 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    char * serverAddr;

    if (argc <2) { //checks that user input server ip address
      printf("Missing server ip address");
      exit(1);
    }

    serverAddr = argv[1]; //to get server ip address from command line

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(serverAddr);
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}
