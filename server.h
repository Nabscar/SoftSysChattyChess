/* header file for server and client implementation
.
Created by Oscar De La Garza & Nabih Estefan
*/
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>    //close
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <pthread.h>
#include <assert.h>

#define MAX 1024
#define PORT 9000
#define TRUE 1
#define FALSE 0
#define PLAYERS 2

int ctoi(char c) {
    return c - '0';
}

char itoc(int i) {
  char c = i +'0';
  return c;
}
