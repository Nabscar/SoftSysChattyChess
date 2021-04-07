/* Source file for chess game functions
.
Created by Oscar De La Garza & Nabih Estefan
*/
#include "chess.h"
int compute(char *pc, char *mv, int chess[8][8], const char *index[8][8], int count) {
  int origRow, newRow;    // row variables
  int origCol, newCol;    // column variables
  int wKingRow, wKingCol;
  int bKingRow, bKingCol;
  int inCheckW = 0;
  int inCheckB = 0;

  for(int i = 0; i < 8; i++) {      // find index of piece to be moved
    for(int j = 0; j < 8; j++) {
      if (strcmp(index[i][j],pc) == 0) {  // check for piece(origianl location)
        origRow = i;
        origCol = j;
        //printf("piece found, %d %d\n", (i), (j));
        //printf("index is: %d\n", chess[origRow][origCol]);
      }
      if (strcmp(index[i][j],mv) == 0) { // check for move(desired location)
        newRow = i;
        newCol = j;
        //printf("new spot, %d %d\n", (i), (j));
        //printf("index is: %d\n", chess[newRow][newCol]);
      }
      if (chess[i][j] == 4) { // check for white kings location
        wKingRow = i;
        wKingCol = j;
      }
      if (chess[i][j] == 4) { // check for black kings location
        bKingRow = i;
        bKingCol = j;
      }
    }
  }

  /******** WHITE'S TURN ********/
  if (count%2 != 0) {                   // odd = white's turn
    switch (chess[origRow][origCol]) {  // check original piece for rulecheck

        /******** ROOK RULECHECK ********/
      case 1:
        if (chess[newRow][newCol] > 0) {  // is your piecce blocking you
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == newRow && origCol != newCol) { // lateral mvmt.
          if (newCol > origCol) {
            for (int i = origCol+1; i < newCol; i++) { // left -> right
              if (chess[origRow][i] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          } else {
            for (int i = origCol-1; i > newCol; i--) { // right -> left
              if (chess[origRow][i] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
            break;
          }
        } else if (origCol == newCol && origRow != newRow) { // vertical mvmt.
          if (newRow > origRow) {
            for (int i = origRow+1; i < newRow; i++) {  // downwards
              if (chess[i][origCol] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count --;
                return count;
              }
            }
          } else {
            for (int i = origRow-1; i > newRow; i--) { // upwards
              if (chess[i][origCol] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
            break;
          }
        } else {
          printf("Invalid move try again.\n"); // Invalid for some reason
          count --;
          return count;
        }

        /******** KNIGHT RULECHECK ********/
      case 2:
        if (chess[newRow][newCol] > 0) {  // is your piecce blocking you
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (newRow == origRow-2 && (newCol == origCol+1 || newCol == origCol-1)) {
            break;
        } else if (newRow == origRow+2 && (newCol == origCol+1 || newCol == origCol-1)) {
            break;
        } else if (newCol == origCol+2 && (newRow == origRow+1 || newRow == origRow-1)) {
            break;
        } else if (newCol == origCol-2 && (newRow == origRow+1 || newRow == origRow-1)) {
            break;
        } else {
          printf("Invalid move try again.\n"); // Invalid for some reason
          count --;
          return count;
        }

        /******** BISHOP RULECHECK ********/
      case 3:
        if (chess[newRow][newCol] > 0) {  // is your piecce blocking you
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
          break;
        } else {
          printf("Invalid move try again.\n"); // Invalid for some reason
          count --;
          return count;
        }

        /******** KING RULECHECK ********/
      case 4:
        if (chess[newRow][newCol] > 0) {  // is your piecce blocking you
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == 7 && newRow < 7) {
          if (origRow == newRow && (newCol == origCol+1 || newCol == origCol-1)) {
            break;
          } else if (origCol == newCol && newRow == origRow-1) {
              break;
          } else if ((newCol == origCol + 1 || newCol == origCol -1) && newRow == origRow-1) {
              break;
          }
        } else {
            if (origRow == newRow && (newCol == origCol+1 || newCol == origCol-1)) {
              break;
          } else if (origCol == newCol && (newRow == origRow+1 || newRow == origRow-1)) {
              break;
          } else if ((newCol == origCol + 1 || newCol == origCol -1) && (newRow == origRow+1 || newRow == origRow-1)) {
              break;
          } else {
            printf("Invalid move try again.\n"); // Invalid for some reason
            count --;
            return count;
          }
        }

        /******** QUEEN RULECHECK ********/
      case 5:
        if (chess[newRow][newCol] > 0) {  // is your piecce blocking you
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == newRow && origCol != newCol) { // lateral mvmt.
          if (newCol > origCol) {
            for (int i = origCol+1; i < newCol; i++) { // left -> right
              if (chess[origRow][i] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          } else {
            for (int i = origCol-1; i > newCol; i--) { // right -> left
              if (chess[origRow][i] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
            break;
          }
        } else if (origCol == newCol && origRow != newRow) { // vertical mvmt.
          if (newRow > origRow) {
            for (int i = origRow+1; i < newRow; i++) {  // downwards
              if (chess[i][origCol] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count --;
                return count;
              }
            }
          } else {
            for (int i = origRow-1; i > newRow; i--) { // upwards
              if (chess[i][origCol] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
            break;
          }
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
          break;
        } else {
          printf("Invalid move try again.\n"); // Invalid for some reason
          count --;
          return count;
        }

        /******** PAWN RULECHECK ********/
      case 6:
        if (chess[newRow][newCol] > 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if ((newCol == origCol+1 || newCol == origCol-1) && newRow == origRow-1 && chess[newRow][newCol] < 0) { // capturing
            break;
        } else if (origRow == 6 && newCol == origCol && (newRow == origRow-1 || newRow == origRow-2)) { // initial move
            break;
        } else if (newRow == origRow-1 && newCol == origCol) { // move foward 1
            break;
        } else {
          printf("Invalid move try again.\n"); // Invalid for some reason
          count --;
          return count;
        }

    default:
      printf("WHITE: make a valid move\n");  // No valid move detected
      count--;
      // printf("Count after WHITE: %d\n", count);
      return count;
    }
/*    inCheckW = 0;           // right of the King
    for(int i = wKingRow+1; i < 7; i++) {
      if (chess[i][wKingCol] < 0) {
        for(int j = wKingRow; j < i; j++) {
          if (chess[j][wKingCol] != 0) {
            inCheckW++;
            break;
          }
        }
      }
    } if (inCheckW == 0) {
      printf("WHITE: make a valid move, you are in check\n");  // No valid move detected
      count--;
      return count;
    }
    inCheckW = 0;           // left of king
    for(int i = wKingRow-1; i > 0; i--) {
      if (chess[i][wKingCol] < 0) {
        for(int j = wKingRow; j > i; j--) {
          if (chess[j][wKingCol] != 0) {
            inCheckW++;
            break;
          }
        }
      }
    } if (inCheckW == 0) {
      printf("WHITE: make a valid move, you are in check\n");  // No valid move detected
      count--;
      return count;
*/
    chess[newRow][newCol] = chess[origRow][origCol];  // update piece
    chess[origRow][origCol] = 0;      // empty original position
    return count;
  }

  /******** BLACK'S TURN ********/
  if (count%2 == 0) {
    switch (chess[origRow][origCol]) {

        /******** ROOK RULECHECK ********/
      case -1:
        if (chess[newRow][newCol] > 0) {  // is your piecce blocking you
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == newRow && origCol != newCol) { // lateral mvmt.
          if (newCol > origCol) {
            for (int i = origCol+1; i < newCol; i++) { // left -> right
              if (chess[origRow][i] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          } else {
            for (int i = origCol-1; i > newCol; i--) { // right -> left
              if (chess[origRow][i] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
            break;
          }
        } else if (origCol == newCol && origRow != newRow) { // vertical mvmt.
          if (newRow > origRow) {
            for (int i = origRow+1; i < newRow; i++) {  // downwards
              if (chess[i][origCol] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count --;
                return count;
              }
            }
          } else {
            for (int i = origRow-1; i > newRow; i--) { // upwards
              if (chess[i][origCol] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
            break;
          }
        } else {
          printf("Invalid move try again.\n"); // Invalid for some reason
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
            break;
        } else if (newRow == origRow+2 && (newCol == origCol+1 || newCol == origCol-1)) {
            break;
        } else if (newCol == origCol+2 && (newRow == origRow+1 || newRow == origRow-1)) {
            break;
        } else if (newCol == origCol-2 && (newRow == origRow+1 || newRow == origRow-1)) {
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
        break;
      } else {
        printf("Invalid move try again.\n");
        count --;
        return count;
      }

        /******** KING RULECHECK ********/
      case -4:
        if (chess[newRow][newCol] > 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == 0 && newRow > 0) {
          if (origRow == newRow && (newCol == origCol+1 || newCol == origCol-1)) {
            break;
          } else if (origCol == newCol && newRow == origRow+1) {
              break;
          } else if ((newCol == origCol + 1 || newCol == origCol -1) && newRow == origRow+1) {
              break;
          } else {
            printf("Invalid move try again.\n");
            count --;
            return count;
          }
        } else {
          if (origRow == newRow && (newCol == origCol+1 || newCol == origCol-1)) {
            break;
        } else if (origCol == newCol && (newRow == origRow+1 || newRow == origRow-1)) {
            break;
        } else if ((newCol == origCol + 1 || newCol == origCol -1) && (newRow == origRow+1 || newRow == origRow-1)) {
            break;
        } else {
          printf("Invalid move try again.\n");
          count --;
          return count;
        }
      }

        /******** QUEEN RULECHECK ********/
      case -5:
        if (chess[newRow][newCol] < 0) {
          printf("Your piece occupies that spot.\n\n");
          count --;
          return count;
        } else if (origRow == newRow && origCol != newCol) { // lateral mvmt.
          if (newCol > origCol) {
            for (int i = origCol+1; i < newCol; i++) { // left -> right
              if (chess[origRow][i] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
          } else {
            for (int i = origCol-1; i > newCol; i--) { // right -> left
              if (chess[origRow][i] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
            break;
          }
        } else if (origCol == newCol && origRow != newRow) { // vertical mvmt.
          if (newRow > origRow) {
            for (int i = origRow+1; i < newRow; i++) {  // downwards
              if (chess[i][origCol] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count --;
                return count;
              }
            }
          } else {
            for (int i = origRow-1; i > newRow; i--) { // upwards
              if (chess[i][origCol] != 0) { // does a piece block you
                printf("A piece blocks your way.\n");
                count--;
                return count;
              }
            }
            break;
          }
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
          break;
        } else {
          printf("Invalid move try again.\n");
          count --;
          return count;
        }

        /******** PAWN RULECHECK ********/
      case -6:
      if (chess[newRow][newCol] > 0) {
        printf("Your piece occupies that spot.\n\n");
        count --;
        return count;
      } else if ((newCol == origCol+1 || newCol == origCol-1) && newRow == origRow+1 && chess[newRow][newCol] > 0) {
          break;
      } else if (origRow == 1 && newCol == origCol && (newRow == origRow+1 || newRow == origRow+2)) {
          break;
      } else if (newRow == origRow+1 && newCol == origCol) {
          break;
      } else {
        printf("Invalid move try again.\n");
        count --;
        return count;
      }

      default:
        printf("BLACK: make a valid move\n");
        count--;
        //printf("Count after BLACK: %d\n", count);
        return count;
      }
    }
    chess[newRow][newCol] = chess[origRow][origCol];  // update piece
    chess[origRow][origCol] = 0;      // empty original position
    return count;
  }

int gameover(int chess[8][8]) {
  int whiteCheck = 0;
  int blackCheck = 0;
  printf("gameover check\n");
  for(int i = 0; i < 8; i++) {      // find index of piece to be moved
    for(int j = 0; j < 8; j++) {
      if (chess[i][j] == 4) {  // check for piece(origianl location)
        whiteCheck++;
      } else if (chess[i][j] == -4) {
        blackCheck++;
      }
    }
  }
  if (whiteCheck == 0) {
    return 0;
  } else if (blackCheck == 0) {
    return 1;
  }
  return 2;
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
     for(brd; brd>0; brd--) {
         a = 8 - brd;
         i = 3;
         if(i==3) {
             len = buffer;
             int hor =0;

             printf("       |");
             for(len; len>0; len--) {
                 if( (hor+vert)%2 == 0 ) {
                   printf("       ");
                 } else if( (hor+vert)%2 != 0 ) {
                   printf("\u2588\u2588\u2588\u2588\u2588\u2588\u2588");     /* the characters inside the print statement*/
                 }                                          ;                 /* are unicodes used for printing the chess grid*/
                 hor++;
             }
             printf("|");
             printf("\n");
             i--;
         }
       if(i==2) {
             len = buffer;
             int hor =0;
             printf("     %c |",alpha);

             for(len; len>0; len--) {
                 b = 8 - len;
                 if( (hor+vert)%2 == 0 ) {
                     if(chess[a][b] < 0) {
                      printf("   \x1b[32m%d\x1b[0m   ", (chess[a][b])*-1);
                     }
                     if(chess[a][b] == 0) {
                      printf("       ");
                     }
                     if(chess[a][b] > 0) {
                      printf("   \x1b[37m%d\x1b[0m   ", chess[a][b]);
                     }
                 } else if( (hor+vert)%2 != 0 ) {
                     if(chess[a][b] < 0) {
                      printf("\u2588\u2588\u258C\x1b[32m%d\x1b[0m\u2590\u2588\u2588", (chess[a][b])*-1);
                     }
                     if(chess[a][b] > 0) {
                      printf("\u2588\u2588\u258C\x1b[37m%d\x1b[0m\u2590\u2588\u2588", chess[a][b]);
                     }
                     if(chess[a][b] == 0) {
                      printf("\u2588\u2588\u2588\u2588\u2588\u2588\u2588", chess[a][b]);
                     }
                 }
                 hor++;
            }
             printf("| %c", alpha);
             printf("\n");
             i--;
        }
        if(i==1) {
             len = buffer;
             printf("       |");
             int hor =0;

              for(len; len>0; len--) {
                 if( (hor+vert)%2 == 0 ) {
                   printf("       ");
                 } else if( (hor+vert)%2 != 0 ) {
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

     for(len; len>0; len--) {
      printf("-------");
     }
            printf("\n");

    printf("           1      2      3      4      5      6      7      8    \n");
    printf("                             Player 1                            \n\n");
    printf("       '1'=>ROOK        '2'=>KNIGHT          '3'=>BISHOP\n       '4'=>KING        '5'=>QUEEN           '6'=>PAWN");
    printf("\n\n");
}
