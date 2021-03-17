/* Source file for chess game and implementation
.
Created by Oscar De La Garza & Nabih Estefan
*/
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* 1 = Pawn
   2 = Rook
   3 = Knight
   4 = Bishop
   5 = Queen
   6 = King */

void printBoard(int chess[8][8]);

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
    {"a1","a2","a3","a4","a5","a6","a7","a8"},
    {"b1","b2","b3","b4","b5","b6","b7","b8"},
    {"c1","c2","c3","c4","c5","c6","c7","c8"},
    {"d1","d2","d3","d4","d5","d6","d7","d8"},
    {"e1","e2","e3","e4","e5","e6","e7","e8"},
    {"f1","f2","f3","f4","f5","f6","f7","f8"},
    {"g1","g2","g3","g4","g5","g6","g7","g8"},
    {"h1","h2","h3","h4","h5","h6","h7","h8"},
  };

  char move[4], free[4];

  printBoard(chess);
  printf("Input move: ");
  if (scanf("%s", move) == EOF) {
    printf("Invalid move");
    move = free;
  };

  printf("%s\n", move);

  return 0;
}

void printBoard(int chess[8][8]) {
  int a,b;
  a = b = 0;
  int len, brd, buffer;   /*len = length & brd = breadth*/
  brd = len = 8;
  printf("\n\n\n");

  printf("                             Player 2                            \n\n");
  printf("           1      2      3      4      5      6      7      8    \n");
  buffer = len;
  printf("       --");

  for(len; len>0; len--){
    printf("-------");
  }

  printf("\n");
  len = buffer;
  //printf("\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\n");

  int i;
     char alpha = 'A';
     int vert = 0;
     for(brd; brd>0; brd--)
     {
         a = 8 - brd;
         i = 3;
         if(i==3)
         {
             len = buffer;
             int hor =0;

             printf("       |");
             for(len; len>0; len--)
             {
                 if( (hor+vert)%2 == 0 )
                 {
                   printf("       ");
                 }

                 else if( (hor+vert)%2 != 0 )
                 {
                   printf("\u2588\u2588\u2588\u2588\u2588\u2588\u2588");     /* the characters inside the print statement*/
                 }                                                           /* are unicodes used for printing the chess grid*/
                 hor++;
             }

             printf("|");
             printf("\n");
             i--;
         }
       if(i==2)
        {
             len = buffer;
             int hor =0;
             printf("     %c |",alpha);

             for(len; len>0; len--)
             {
                 b = 8 - len;
                 if( (hor+vert)%2 == 0 )
                 {
                     if(chess[a][b] < 0)
                     //printf("\u2588\u2588\u258C\x1b[37m%d\x1b[0m\u2590\u2588\u2588\n", chess[0][2]);
                     //printf("\u2588\u2588\u258C\x1b[42m\x1b[30m%d\x1b[0m\u2590\u2588\u2588\n", chess[0][2]);
                     {
                      printf("   \x1b[37m%d\x1b[0m   ", (chess[a][b])*-1);
                     }

                     if(chess[a][b] == 0)
                     {
                      printf("       ");
                     }

                     if(chess[a][b] > 0)
                     {
                      printf("   \x1b[32m%d\x1b[0m   ", chess[a][b]);
                     }
                 }

                 else if( (hor+vert)%2 != 0 )
                 {
                     if(chess[a][b] < 0)
                     {
                      printf("\u2588\u2588\u258C\x1b[37m%d\x1b[0m\u2590\u2588\u2588", (chess[a][b])*-1);
                     }

                     {
                       if(chess[a][b] > 0)
                      printf("\u2588\u2588\u258C\x1b[32m%d\x1b[0m\u2590\u2588\u2588", chess[a][b]);
                     }

                     if(chess[a][b] == 0)
                     {
                      printf("\u2588\u2588\u2588\u2588\u2588\u2588\u2588", chess[a][b]);
                     }

                 }
                 hor++;

            }

             printf("| %c", alpha);
             printf("\n");
             i--;
        }

        if(i==1)
        {
             len = buffer;
             printf("       |");
             int hor =0;

              for(len; len>0; len--)
              {
                 if( (hor+vert)%2 == 0 )
                 {
                   printf("       ");
                 }

                 else if( (hor+vert)%2 != 0 )
                 {
                   printf("\u2588\u2588\u2588\u2588\u2588\u2588\u2588");
                 }
                 hor++;

              }

            printf("|");
            printf("\n");
            i--;
        }

         alpha++;
         vert++;
    }

    len = buffer;
    printf("       --");

     for(len; len>0; len--){
      printf("-------");
     }
            printf("\n");

    printf("           1      2      3      4      5      6      7      8    \n");
    printf("                             Player 1                            \n\n");
    printf("       '1'=>ROOK        '2'=>KNIGHT          '3'=>BISHOP\n       '4'=>KING        '5'=>QUEEN           '6'=>PAWN");
    printf("\n\n");
}
