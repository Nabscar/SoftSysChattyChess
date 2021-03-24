/* Header file for chess game and implementation
.
Created by Oscar De La Garza & Nabih Estefan
*/
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int compute(char *pc, char *mv, int chess[8][8], const char *index[8][8], int count);
void printBoard(int chess[8][8]);
