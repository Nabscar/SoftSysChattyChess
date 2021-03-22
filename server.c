#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>    //close
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>

#define TRUE 1
#define FALSE 0
#define MAX 80
#define PORT 9000
#define PLAYERS 2

// Driver function
int main()
{
    int opt = TRUE; //for multiple connections
    int masterSocket, playerSockets[PLAYERS], socketDesc, masterSocketDesc,
      activity, newSocket, valread, addrLen;
    struct sockaddr_in serverAddress;
    char usernames[PLAYERS][MAX];
    int userSet[PLAYERS] = {0};
    char buff[MAX];

    //set of socket descriptors
    fd_set readfds;

    playerSockets[0] = 0;
    playerSockets[1] = 0;

    // socket create and verification
    if ((masterSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        printf("Socket Creation Failed\n");
        exit(EXIT_FAILURE);
    }
    // else
    //   printf("Socket successfully created!\n");

    // Set master socket for multiple connections
    if(setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
          sizeof(opt)) < 0)
    {
        perror("Set Sock Opt");
        exit(EXIT_FAILURE);
    }

    // assign IP, PORT
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if (bind(masterSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        printf("Socket Bind Failed\n");
        exit(EXIT_FAILURE);
    }
    // else
    // {
    //   printf("Socket successfully binded: <%u>\n", masterSocket);
    printf("Listening on Port %d\n", PORT);
    // }

    if (listen(masterSocket, 2) < 0)
    {
        perror("Listening...");
        exit(EXIT_FAILURE);
    }

    addrLen = sizeof(serverAddress);
    puts("Server Started!");
    // PLayer Setup Loop
    for(int i = 0; i < PLAYERS; i++)
    {
        FD_ZERO(&readfds);
        FD_SET(masterSocket, &readfds);
        masterSocketDesc = masterSocket;

        for (int i = 0; i < PLAYERS; i++)
        {
            socketDesc = playerSockets[1];
            if (socketDesc > 0)
            {
                FD_SET(socketDesc, &readfds);
            }
            if (socketDesc > masterSocketDesc)
            {
                masterSocketDesc = socketDesc;
            }
        }

        activity = select(masterSocketDesc+1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("Select Error");
        }

        // New connection
        if (FD_ISSET(masterSocket, &readfds))
        {
            if ((newSocket = accept(masterSocket, (struct sockaddr*)&serverAddress, \
            (socklen_t*)&addrLen)) < 0)
            {
                perror("Error connecting to user");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection! Socket fd: %d, IP: %s , Port: %d\n" , \
              newSocket , inet_ntoa(serverAddress.sin_addr) , \
              ntohs(serverAddress.sin_port));

            //send new connection greeting message
            char* msg1 = "Hello! Please enter your name: \r\n";
            if(send(newSocket, msg1, strlen(msg1), 0) != strlen(msg1))
            {
                printf("Error sending Message");
            }

            puts("Welcome message sent successfully");

            playerSockets[i] = newSocket;

            read(newSocket , buff, MAX);
            strcpy(usernames[i], buff);
            usernames[i][strlen(usernames[i])-1] = '\0';
            userSet[i] = 1;
            printf("%s", usernames[i]);
        }
    }

    // infinite game loop
    int currentPlayer = 0;
    puts("Players connected! Lets Play!");
    for (;;)
    {
        socketDesc = playerSockets[currentPlayer];
        if ((valread = read(socketDesc , buff, MAX))!= NULL)
        {
            printf("Playing: %d\n", currentPlayer);
            //Check if it was for closing , and also read the
            //incoming message
            if (valread == 0)
            {
                //Somebody disconnected , get his details and print
                getpeername(socketDesc , (struct sockaddr*)&serverAddress, (socklen_t*)&addrLen);
                printf("Host Disconnected. IP: %s. Port %d \n" , \
                inet_ntoa(serverAddress.sin_addr),
                ntohs(serverAddress.sin_port));

                char* message_quit = "User Disconnected. You Win!\n";

                socketDesc = playerSockets[(currentPlayer+1)%2];
                send(socketDesc,message_quit,strlen(message_quit),0);
                exit(0);
            }
            else
            {
                printf("%s\n", buff);
                buff[valread] = '\0';
                if (userSet[currentPlayer]==0)
                { //assumes first message from client is username
                    char *nameStart = strchr(buff, ':'); //records username
                    strcpy(usernames[currentPlayer], nameStart + 2);
                    usernames[currentPlayer][strlen(usernames[currentPlayer])-1] = '\0';
                    userSet[currentPlayer] = 1;
                    char *msg2 = "Great! Now we can start the game!\r\n";
                    send(playerSockets[currentPlayer], msg2, strlen(msg2), 0);
                }
                else if(userSet[currentPlayer]==1)
                { // Now we can play
                    socketDesc = playerSockets[(currentPlayer+1)%2];
                    // Read buffer message and do the chess shit here
                    //gonna have just sending message to the other user for Now
                    send(socketDesc, buff, strlen(buff), 0);
                }
                currentPlayer = (currentPlayer + 1) % 2;
            }
        }
    }
    return 0;
}
