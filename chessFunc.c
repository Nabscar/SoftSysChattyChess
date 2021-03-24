/* Source file for chess game functions
.
Created by Oscar De La Garza & Nabih Estefan
*/
#include "chess.h"
int compute(char *pc, char *mv, int chess[8][8], const char *index[8][8], int count) {
  int origRow, newRow;
  int origCol, newCol;

  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if (strcmp(index[i][j],pc) == 0) {
        origRow = i;
        origCol = j;
        //printf("piece found, %d %d\n", (i), (j));
        //printf("index is: %d\n", chess[origRow][origCol]);
      }
      if (strcmp(index[i][j],mv) == 0) {
        newRow = i;
        newCol = j;
        //printf("new spot, %d %d\n", (i), (j));
        //printf("index is: %d\n", chess[newRow][newCol]);
      }
    }
  }

  /******** WHITE'S TURN ********/
  if (count%2 != 0) {
    switch (chess[origRow][origCol]) {

        /******** ROOK RULECHECK ********/
      case 1:
        if (chess[newRow][newCol] > 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == newRow && origCol != newCol) {
          if (newCol > origCol) {
            for (int i = origCol; i < newCol; i++) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          } else {
            for (int i = origCol; i > newCol; i--) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          }
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (origCol == newCol && origRow != newRow) {
          if (newRow > origRow) {
            for (int i = origRow; i < newRow; i++) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count --;
                return count;
              }
            }
          } else {
            for (int i = origRow; i > newRow; i--) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          }
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else {
          printf("Invalid move try again.\n");
          count --;
          return count;
        }

        /******** KNIGHT RULECHECK ********/
      case 2:
        if (chess[newRow][newCol] > 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (newRow == origRow-2 && (newCol == origCol+1 || newCol == origCol-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (newRow == origRow+2 && (newCol == origCol+1 || newCol == origCol-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (newCol == origCol+2 && (newRow == origRow+1 || newRow == origRow-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (newCol == origCol-2 && (newRow == origRow+1 || newRow == origRow-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else {
          printf("Invalid move try again.\n");
          count --;
          return count;
        }

        /******** BISHOP RULECHECK ********/
      case 3:
        if (chess[newRow][newCol] > 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (newCol == origCol + (newRow-origRow) || newCol == origCol - (newRow-origRow)) {
          if (origRow > newRow) {
            if (origCol > newCol) {
              for (int i = 1; i < (origCol - newCol); i++) {    /*** UP LEFT DIAG ***/
                if (chess[origRow-i][origCol-i] !=0) {
                  printf("A piece blocks your way.\n");
                  count--;
                  return count;
                }
              }
            } else {
              for (int i = 1; i < (newCol - origCol); i++) {    /*** UP RIGHT DIAG ***/
                if (chess[origRow-i][origCol+i] !=0) {
                  printf("A piece blocks your way.\n");
                  count--;
                  return count;
                }
              }
            }
          } else {
            if (origCol > newCol) {
              for (int i = 1; i < (origCol - newCol); i++) {    /*** DOWN LEFT DIAG ***/
                if (chess[origRow+i][origCol-i] !=0) {
                  printf("A piece blocks your way.\n");
                  count--;
                  return count;
                }
              }
            } else {
              for (int i = 1; i < (newCol - origCol); i++) {    /*** DOWN RIGHT DIAG ***/
                if (chess[origRow+i][origCol+i] !=0) {
                  printf("A piece blocks your way.\n");
                  count--;
                  return count;
                }
              }
            }
          }
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else {
          printf("Invalid move try again.\n");
          count --;
          return count;
        }

        /******** KING RULECHECK ********/
      case 4:
        if (chess[newRow][newCol] > 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == newRow && (newCol = origCol+1 || newCol == origCol-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (origCol == newCol && (newRow = origRow+1 || newRow == origRow-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if ((newCol == origCol + 1 || newCol == origCol -1) && (newRow == origRow+1 || newRow == origRow-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else {
          printf("Invalid move try again.\n");
          count --;
          return count;
        }

        /******** QUEEN RULECHECK ********/
      case 5:
        if (chess[newRow][newCol] > 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == newRow && origCol != newCol) {
          if (newCol > origCol) {
            for (int i = origCol; i < newCol; i++) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          } else {
            for (int i = origCol; i > newCol; i--) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          }
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (origCol == newCol && origRow != newRow) {
          if (newRow > origRow) {
            for (int i = origRow; i < newRow; i++) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count --;
                return count;
              }
            }
          } else {
            for (int i = origRow; i > newRow; i--) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          }
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (newCol == origCol + (newRow-origRow) || newCol == origCol - (newRow-origRow)) {
          if (origRow > newRow) {
            if (origCol > newCol) {
              for (int i = 1; i < (origCol - newCol); i++) {    /*** UP LEFT DIAG ***/
                if (chess[origRow-i][origCol-i] !=0) {
                  printf("A piece blocks your way.\n");
                  count--;
                  return count;
                }
              }
            } else {
              for (int i = 1; i < (newCol - origCol); i++) {    /*** UP RIGHT DIAG ***/
                if (chess[origRow-i][origCol+i] !=0) {
                  printf("A piece blocks your way.\n");
                  count--;
                  return count;
                }
              }
            }
          } else {
            if (origCol > newCol) {
              for (int i = 1; i < (origCol - newCol); i++) {    /*** DOWN LEFT DIAG ***/
                if (chess[origRow+i][origCol-i] !=0) {
                  printf("A piece blocks your way.\n");
                  count--;
                  return count;
                }
              }
            } else {
              for (int i = 1; i < (newCol - origCol); i++) {    /*** DOWN RIGHT DIAG ***/
                if (chess[origRow+i][origCol+i] !=0) {
                  printf("A piece blocks your way.\n");
                  count--;
                  return count;
                }
              }
            }
          }
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else {
          printf("Invalid move try again.\n");
          count --;
          return count;
        }

        /******** PAWN RULECHECK ********/
      case 6:
        if (chess[newRow][newCol] > 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if ((newCol == origCol+1 || newCol == origCol-1) && newRow == origRow-1) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (origRow-1 == newRow || origRow-2 == newRow) {
          if (chess[origRow-1][origCol] != 0 && newRow == origRow-1) {
            printf("Invalid move, piece in front.\n");
            count --;
            return count;
          } else if (chess[origRow-2][origCol] != 0 && newRow == origRow-2) {
            printf("Invalid move, piece already there.\n");
            count --;
            return count;
          } else if (origCol != newCol) {
            printf("Invalid move try again.\n");
            count --;
            return count;
          } else {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
          }
        }

    default:
      printf("WHITE: make a valid move\n");
      count--;
      printf("Count after WHITE: %d\n", count);
      return count;
    }
  }

  /******** BLACK'S TURN ********/
  if (count%2 == 0) {
    switch (chess[origRow][origCol]) {

        /******** ROOK RULECHECK ********/
      case -1:
        if (chess[newRow][newCol] > 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == newRow && origCol != newCol) {
          if (newCol > origCol) {
            for (int i = origCol; i < newCol; i++) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          } else {
            for (int i = origCol; i > newCol; i--) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          }
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (origCol == newCol && origRow != newRow) {
          if (newRow > origRow) {
            for (int i = origRow; i < newRow; i++) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          } else {
            for (int i = origRow; i > newRow; i--) {
              if (chess[origRow][origCol] != 0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          }
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else {
          printf("Invalid move try again.\n");
          count --;
          return count;
        }

        /******** KNIGHT RULECHECK ********/
      case -2:
        if (chess[newRow][newCol] < 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (newRow == origRow-2 && (newCol == origCol+1 || newCol == origCol-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (newRow == origRow+2 && (newCol == origCol+1 || newCol == origCol-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (newCol == origCol+2 && (newRow == origRow+1 || newRow == origRow-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (newCol == origCol-2 && (newRow == origRow+1 || newRow == origRow-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else {
          printf("Invalid move try again.\n");
          count --;
          return count;
        }

        /******** BISHOP RULECHECK ********/
      case -3:
      if (chess[newRow][newCol] < 0) {
        printf("Your piece occupies that spot.\n\n");
        count --;
        return count;
      } else if (newCol == origCol + (newRow-origRow) || newCol == origCol - (newRow-origRow)) {
        if (origRow > newRow) {
          if (origCol > newCol) {
            for (int i = 1; i < (origCol - newCol); i++) {    /*** UP LEFT DIAG ***/
              if (chess[origRow-i][origCol-i] !=0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          } else {
            for (int i = 1; i < (newCol - origCol); i++) {    /*** UP RIGHT DIAG ***/
              if (chess[origRow-i][origCol+i] !=0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          }
        } else {
          if (origCol > newCol) {
            for (int i = 1; i < (origCol - newCol); i++) {    /*** DOWN LEFT DIAG ***/
              if (chess[origRow+i][origCol-i] !=0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          } else {
            for (int i = 1; i < (newCol - origCol); i++) {    /*** DOWN RIGHT DIAG ***/
              if (chess[origRow+i][origCol+i] !=0) {
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          }
        }
        chess[newRow][newCol] = chess[origRow][origCol];
        chess[origRow][origCol] = 0;
        break;
      } else {
        printf("Invalid move try again.\n");
        count --;
        return count;
      }

        /******** KING RULECHECK ********/
      case -4:
        if (chess[newRow][newCol] < 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == newRow && (newCol = origCol+1 || newCol == origCol-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (origCol == newCol && (newRow = origRow+1 || newRow == origRow-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if ((newCol == origCol + 1 || newCol == origCol -1) && (newRow == origRow+1 || newRow == origRow-1)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else {
          printf("Invalid move try again.\n");
          count --;
          return count;
        }

        /******** QUEEN RULECHECK ********/
      case -5:
        if (chess[newRow][newCol] < 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == newRow && origCol != newCol) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (origCol == newCol && origRow != newRow) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (newCol == origCol + (newRow-origRow) || newCol == origCol - (newRow-origRow)) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else {
          printf("Invalid move try again.\n");
          count --;
          return count;
        }

        /******** PAWN RULECHECK ********/
      case -6:
        if (chess[newRow][newCol] < 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if ((newCol == origCol+1 || newCol == origCol-1) && newRow == origRow+1) {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
        } else if (origRow+1 == newRow || origRow+2 == newRow) {
          if (chess[origRow+1][origCol] != 0 && newRow == origRow+1) {
            printf("Invalid move, piece 1 away.\n");
            count --;
            return count;
          } else if (chess[origRow+2][origCol] != 0 && newRow == origRow+2) {
            printf("Invalid move, piece 2 away.\n");
            count --;
            return count;
          } else if (origCol != newCol) {
              printf("Invalid move try again.\n");
              count --;
              return count;
          } else {
          chess[newRow][newCol] = chess[origRow][origCol];
          chess[origRow][origCol] = 0;
          break;
          }
        }
      default:
        printf("BLACK: make a valid move\n");
        count--;
        printf("Count after BLACK: %d\n", count);
        return count;
    }
  }
  return count;
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

  int i;
     char alpha = 'H';
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
                 }                                          ;                 /* are unicodes used for printing the chess grid*/
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
                      printf("   \x1b[32m%d\x1b[0m   ", (chess[a][b])*-1);
                     }

                     if(chess[a][b] == 0)
                     {
                      printf("       ");
                     }

                     if(chess[a][b] > 0)
                     {
                      printf("   \x1b[37m%d\x1b[0m   ", chess[a][b]);
                     }
                 }

                 else if( (hor+vert)%2 != 0 )
                 {
                     if(chess[a][b] < 0)
                     {
                      printf("\u2588\u2588\u258C\x1b[32m%d\x1b[0m\u2590\u2588\u2588", (chess[a][b])*-1);
                     }

                     {
                       if(chess[a][b] > 0)
                      printf("\u2588\u2588\u258C\x1b[37m%d\x1b[0m\u2590\u2588\u2588", chess[a][b]);
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

         alpha--;
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
