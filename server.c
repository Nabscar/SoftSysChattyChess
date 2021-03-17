#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>

#define TRUE 1
#define FALSE 0
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
int communicationFunction(int masterSocket, int clientConnect);
// Driver function
int main()
{
    int masterSocket, clientConnect, serverAddressLen;
    struct sockaddr_in serverAddress, clientAddress;

    // socket create and verification
    if ( (masterSocket  = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        printf("socket creation failed...\n");
        exit(EXIT_FAILURE);
    }
    else
      printf("Socket successfully created..\n");

    memset((char*)&serverAddress, 0, sizeof(serverAddress));

    // assign IP, PORT
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(masterSocket, (SA*)&serverAddress, sizeof(serverAddress))) != 0)
    {
        printf("socket bind failed...\n");
        exit(EXIT_FAILURE);
    }
    else
      printf("Socket successfully binded: <%u>\n", masterSocket);

    for(;;)
    {
      // Now server is ready to listen and verification
      if ((listen(masterSocket, 2)) != 0)
      {
          printf("Listen failed...\n");
          exit(EXIT_FAILURE);
      }
      else
          printf("Server listening..\n");

      serverAddressLen = sizeof(serverAddress);

      // Accept the data packet from client and verification
      clientConnect = accept(masterSocket, (SA*)&serverAddress,
        &serverAddressLen);
      if (clientConnect < 0)
      {
          printf("server accept failed...\n");
          exit(EXIT_FAILURE);
      }
      else
          printf("server accept the client...\n");

      // Function for chatting between client and server
      if (communicationFunction(clientConnect, clientConnect) == 0)
      {
        // if server closed then close completely
        close(masterSocket, clientConnect);
        return 0;
      }
      // if client closed go back to listening
    }
}


int communicationFunction(int masterSocket, int clientConnect)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;)
    {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(clientConnect, buff, MAX);
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Client exited...\n");
            return 1;
        }
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n');

        // and send that buffer to client
        write(clientConnect, buff, MAX);

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
            return 0;
        }
    }
}
