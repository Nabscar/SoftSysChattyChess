/* Source file for chess game and implementation
.
Created by Oscar De La Garza & Nabih Estefan
*/
#include "chess.h"

int main() {

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

  char piece[4], move[4];
  char pc[3], mv[3];
  int checker = 1;
  int run = 108;

  while(run > 0) {
    printBoard(chess);

    printf("Input piece you would like to move: ");
    fgets(piece, sizeof piece, stdin);
    for(int i = 0; i < 2; i++) {
      pc[i] = piece[i];\
      pc[2] = '\0';
    }
    printf("Where would you like to move it: ");
    fgets(move, sizeof move, stdin);
    for(int i = 0; i < 2; i++) {
      mv[i] = move[i];
    }
  /*
    for(int cnt = 0; cnt < 3; cnt++) {
      printf("pc: %c\n", pc[cnt]);
      printf("mv: %c\n", mv[cnt]);
    }
  */
    checker = compute(pc, mv, chess, ind, checker);
    checker++;
    printf("Current Count is: %d\n", checker);
  }
  return 0;
}
