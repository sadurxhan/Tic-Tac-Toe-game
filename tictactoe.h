/* 
============================================================================
                            TIC-TAC-TOE GAME

I started as a simple two-player tic-tac-toe and was expanded step-by-step:
     - Support for variable board sizes (3x3 up to 10x10).
     - Win detection across rows, columns, and both diagonals.
     - Multiple game modes:
          1) Two Player
          2) Player vs Computer (computer selects random valid moves)
          3) Multiplayer (supports 3 players: User, computer1, computer2)
     - Dynamic memory allocation.
     - Game log file (gamelog.txt) to record move history.

 Game Logic:
     - The board is represented by a 2D array of characters.
     - Each move is validated before placing a symbol.  
     - After each move, the program checks:
          • Row match
          • Column match
          • Diagonal and Anti-Diagonal matches
          • Full board (for draw)
	 - The game ends when a player wins or the board is full. 

   Student Name- Sadurshan S
   Student ID- IT25102967
   Module - Programming Methodology - SE1012
   Date- 05th October 2025
   Assignment- Tic-Tac-Toe Game

   ============================================================================
*/

#ifndef TICTACTOE_H
#define TICTACTOE_H

//Header files
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Define player symbols
#define Player1 'X'
#define Player2 'O'
#define Player3 'Z'

//Function prototypes
void initializeBoard(int n, char **board);
void printBoard(int n, char **board);
int getMove(int n, char **board, int *r, int *c, char sym, int numPlayer);
int computerMove(int n, char **board, char sym, int *r, int *c);
int validateMove(int n, char **board, int row, int column);
void makeMove(int n, char **board, int row, int column, char sym);
int checkWin(int n, char **board, char sym);
int checkDraw(int n, char **board);
int gameOver(int n, char **board, int currentPlayer, char currentSym);

#endif
