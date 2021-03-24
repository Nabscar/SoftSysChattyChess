/* Source file for client implementation
.
Created by Oscar De La Garza & Nabih Estefan
*/
#include "server.h"
#include "chess.h"

int nameFlag = 0; //0 -> name not set

void * recieveMsg(void * socket) {
  int sockfd, ret;
  char buff[MAX];
  memset(buff, '0', MAX);
  sockfd = (int) socket;

  for (;;){
    memset(buff, 0, MAX);
    ret = recv(sockfd , buff, MAX,0);
    if(ret == 0){
      printf("Server not available! Please Ctrl-D");
      pthread_exit(NULL);
      exit(0);
    }
    else if (ret < 0){
      printf("Error receiving data!\n");
    }
    else{
      if (nameFlag == 1){
        int chessBoard[8][8];
      	for(int i = 0; i < 8; i++){
      		for(int j = 0; j < 8; j++){
      			chessBoard[i][j] = ctoi(buff[i*8 + j]) - 6;
      		}
      	}
      	printBoard(chessBoard);
      }
      else{
        printf("%s\n", buff);
      }
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

  if (argc <2){ //checks that user input server ip address
    printf("Missing server IP address");
    exit(EXIT_FAILURE);
  }

  serverAddr = argv[1]; //to get server ip address from command line

  // socket create and varification

  if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
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
  if(inet_pton(AF_INET, serverAddr, &serverAddress.sin_addr)<=0){
    printf("\nInvalid address/ Address not supported \n");
    exit(EXIT_FAILURE);
  }

  // connect the client socket to server socket
  if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) != 0){
    printf("Connection to Server Failed\n");
    exit(EXIT_FAILURE);
  }

  //creating a new thread for receiving messages from the server
  int ret = pthread_create(&rThread, NULL, recieveMsg, (void *) clientSocket);
  if (ret){
    printf("ERROR: Return Code from pthread_create() is %d\n", ret);
    exit(1);
  }

  printf("Connected to Chess Server!\n");



  while(fgets(buff, MAX, stdin) != NULL)
  {
    //printf("LOOP");
    char msg_buff[MAX] = {0};
    if (!nameFlag){
      strncpy(username, buff, MAX-1);
      username[MAX+1] = '\0';
      sprintf(msg_buff,"%s", username);
      nameFlag = 1;
      printf("Great, lets play ");
    }
    else{
      sprintf(msg_buff, "%s", buff);
    }

    ret = send(clientSocket , msg_buff , MAX , 0);

    if(ret < 0) {
      printf("Error sending data");
      exit(1);
    }
    printf("%s\n", msg_buff);
    memset(buff, '0', MAX);
    memset(msg_buff, '0', MAX);
  }
  puts("DONE!");

  // close the socket
  close(clientSocket);
}
