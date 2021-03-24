/* Source file for server implementation
.
Created by Oscar De La Garza & Nabih Estefan
*/
#include "server.h"
#include "chess.h"

// Driver function
int main(){
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
  if ((masterSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0){
    printf("Socket Creation Failed\n");
    exit(EXIT_FAILURE);
  }
  // else
  //   printf("Socket successfully created!\n");

  // Set master socket for multiple connections
  if(setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
      sizeof(opt)) < 0){
    perror("Set Sock Opt");
    exit(EXIT_FAILURE);
  }

  // assign IP, PORT
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(PORT);

  // Binding newly created socket to given IP and verification
  if (bind(masterSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
    printf("Socket Bind Failed\n");
    exit(EXIT_FAILURE);
  }
  // else
  // {
  //   printf("Socket successfully binded: <%u>\n", masterSocket);
  printf("Listening on Port %d\n", PORT);
  // }

  if (listen(masterSocket, 2) < 0){
    perror("Listening...");
    exit(EXIT_FAILURE);
  }

  addrLen = sizeof(serverAddress);
  puts("Server Started!");
  // PLayer Setup Loop
  for(int i = 0; i < PLAYERS; i++){
    FD_ZERO(&readfds);
    FD_SET(masterSocket, &readfds);
    masterSocketDesc = masterSocket;

    for (int i = 0; i < PLAYERS; i++){
      socketDesc = playerSockets[1];
      if (socketDesc > 0){
        FD_SET(socketDesc, &readfds);
      }
      if (socketDesc > masterSocketDesc){
        masterSocketDesc = socketDesc;
      }
    }

    activity = select(masterSocketDesc+1 , &readfds , NULL , NULL , NULL);

    if ((activity < 0) && (errno!=EINTR)){
      printf("Select Error");
    }

    // New connection
    if (FD_ISSET(masterSocket, &readfds)){
      if ((newSocket = accept(masterSocket, (struct sockaddr*)&serverAddress, \
          (socklen_t*)&addrLen)) < 0){
        perror("Error connecting to user");
        exit(EXIT_FAILURE);
      }

      //inform user of socket number - used in send and receive commands
      printf("New connection! Socket fd: %d, IP: %s , Port: %d\n" , \
        newSocket , inet_ntoa(serverAddress.sin_addr) , \
        ntohs(serverAddress.sin_port));

      //send new connection greeting message
      char* msg1 = "Hello! Please enter your name: \r\n";
      if(send(newSocket, msg1, strlen(msg1), 0) != strlen(msg1)){
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
  puts("Players connected! Lets Play!");

  // Setting up specific game variables
  int chess[8][8] = {
    {-1,-2,-3,-4,-5,-3,-2,-1},
    {-6,-6,-6,-6,-6,-6,-6,-6},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 6, 6, 6, 6, 6, 6, 6, 6},
    { 1, 2, 3, 5, 4, 3, 2, 1}
  };

  const char *ind[8][8] = {
    {"h1","h2","h3","h4","h5","h6","h7","h8"},
    {"g1","g2","g3","g4","g5","g6","g7","g8"},
    {"f1","f2","f3","f4","f5","f6","f7","f8"},
    {"e1","e2","e3","e4","e5","e6","e7","e8"},
    {"d1","d2","d3","d4","d5","d6","d7","d8"},
    {"c1","c2","c3","c4","c5","c6","c7","c8"},
    {"b1","b2","b3","b4","b5","b6","b7","b8"},
    {"a1","a2","a3","a4","a5","a6","a7","a8"},
  };

  char pc[3], mv[3];
  int run = 1;
  int currentPlayer = 1;
  while (run > 0){
    printBoard(chess);
    memset(pc, '0', sizeof(pc));
    memset(mv, '0', sizeof(mv));
    memset(buff, '0', sizeof(buff));
    socketDesc = playerSockets[(currentPlayer+1)%2];

    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        buff[i*8 + j] = itoc(chess[i][j] + 6);
      }
    }

    send(socketDesc, buff, strlen(buff), 0);
    if ((valread = read(socketDesc , buff, MAX))!= NULL){
      printf("Playing: %s\n", usernames[(currentPlayer+1)%2]);
      //Check if it was for closing , and also read the
      //incoming message
      if (valread == 0){
        //Somebody disconnected , get his details and print
        getpeername(socketDesc , (struct sockaddr*)&serverAddress, (socklen_t*)&addrLen);
        printf("Host Disconnected. IP: %s. Port %d \n" , \
        inet_ntoa(serverAddress.sin_addr),
        ntohs(serverAddress.sin_port));

        char* message_quit = "User Disconnected. You Win!\n";

        socketDesc = playerSockets[(currentPlayer)%2];
        send(socketDesc,message_quit,strlen(message_quit),0);
        exit(0);
      }
      else{
        printf("%s\n", buff);
        buff[valread] = '\0';
        for(int i = 0; i < 2; i++) {
          pc[i] = buff[i];
        }
        pc[2] = '\0';
        for(int i = 2; i < 4; i++) {
          mv[i-2] = buff[i];
        }
        mv[2] = '\0';
        printf("AAAAA Move: %s     %s", pc, mv);
        currentPlayer = compute(pc, mv, chess, ind, currentPlayer);
        currentPlayer++;
        socketDesc = playerSockets[(currentPlayer)%2];

        for(int i = 0; i < 8; i++){
      		for(int j = 0; j < 8; j++){
      			buff[i*8 + j] = itoc(chess[i][j] + 6);
      		}
      	}

        send(socketDesc, buff, strlen(buff), 0);
      }
    }
  }
  return 0;
}
