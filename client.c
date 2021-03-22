#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <pthread.h>

#define MAX 80
#define PORT 9000

int nameFlag = 0; //0 -> name not set

void * recieveMsg(void * socket) {
    int sockfd, ret;
    char buffer[MAX];
    sockfd = (int) socket;
    for (;;)
    {
        memset(buffer, 0, MAX);
        ret = recv(sockfd , buffer, MAX,0);
        if(ret == 0)
        { //ret = 0
            printf("Server not available! Please Ctrl-D");
            pthread_exit(NULL);
            exit(0);
        }
        else if (ret < 0)
        {
           printf("Error receiving data!\n");
        }
        else
        {
           fputs(buffer, stdout);
        }
    }
}

int main(int argc, char const *argv[])
{
    int clientSocket;
    struct sockaddr_in serverAddress;
    char const* serverAddr;
    char username[MAX];
    char buff[MAX];
    pthread_t rThread;

    if (argc <2) { //checks that user input server ip address
      printf("Missing server IP address");
      exit(EXIT_FAILURE);
    }

    serverAddr = argv[1]; //to get server ip address from command line

    // socket create and varification

    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Socket Creation Failed\n");
        exit(EXIT_FAILURE);
    }
    // else
    //     printf("Socket successfully created!\n");

    memset(&serverAddress, '0', sizeof(serverAddress));

    // assign IP, PORT
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr(serverAddr);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, serverAddr, &serverAddress.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }

    // connect the client socket to server socket
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) != 0)
    {
        printf("Connection to Server Failed\n");
        exit(EXIT_FAILURE);
    }

    //creating a new thread for receiving messages from the server
    int ret = pthread_create(&rThread, NULL, recieveMsg, (void *) clientSocket);
    if (ret)
    {
     printf("ERROR: Return Code from pthread_create() is %d\n", ret);
     exit(1);
    }

    printf("Connected to Chess Server!\n");



    while(fgets(buff, MAX, stdin) != NULL)
    {
        printf("LOOP");
        char msg_buff[MAX] = {0};
        if (!nameFlag)
        {
          strncpy(username, buff, MAX-1);
          username[MAX+1] = '\0';
          sprintf(msg_buff,"%s\n", username);
          nameFlag = 1;
            printf("NAME");
        }
        else
        {
          printf("PLAY");
          sprintf(msg_buff, "%s", buff);
        }
        //inserts username at start of message
        ret = send(clientSocket , msg_buff , MAX , 0);
        if(ret < 0) {
          printf("Error sending data");
          exit(1);
        }
        memset(buff, '0', MAX);
    }
    puts("DONE!");

    // close the socket
    close(clientSocket);
}
//
//
//
// void communicationFunction(int clientSocket)
// {
//     int n;
//
//     if(!nameFlag)
//     {
//       printf("TerminalChess v1.0\n");
//     }
//     for(;;)
//     {
//         if (!nameFlag)
//         {
//           // clear buffer
//           bzero(buff, MAX);
//           // read buffer from server
//           read(clientSocket, buff, MAX);
//           printf("Please enter your name: ");
//           bzero(buff, MAX);
//           n = 0;
//           // loop through chars to get input
//           while ((buff[n++] = getchar()) != '\n');
//           write(clientSocket, buff, MAX);
//           printf("\nGreat! Lets start the game %s!", buff);
//         }
//         // clear buffer
//         bzero(buff, MAX);
//         // read buffer from server
//         read(clientSocket, buff, MAX);
//         // print board
//         printf("%s", buff);
//
//         if ((strncmp("Checkmate", buff, 9)) == 0)
//         {
//             printf("%s\n", buff);
//             break;
//         }
//         // clear buffer and prompt user for input
//
//         bzero(buff, MAX);
//         printf("Enter your move : ");
//         n = 0;
//         // loop through chars to get input
//         while ((buff[n++] = getchar()) != '\n');
//         send(clientSocket, buff, MAX, 0);
//     }
// }
