#include "tictactoe.h"

/*---------------------------------------------------------------
  Function Name : initializeBoard
  Purpose       : To fill all cells of the board with empty spaces.
  Inputs        :
      n     -> size of the board
      board -> 2D array for storing symbols
  Output        : None
  Logic         :
      - Go through each row and column of the board.
      - Set every cell to a space (' ') before starting the game.
----------------------------------------------------------------*/

void initializeBoard(int n,char **board){ //Fill the game board with emply spaces
	for(int i = 0; i < n; i++){   //To iterate over each row of the board
		for(int j = 0; j < n; j++){  //To iterate over each column of the board
			board[i][j] = ' ';  //Initialize each character in the array to space ' '
		}
	}
}

/*---------------------------------------------------------------
  Function Name : printBoard
  Purpose       : To show the game board with row and column numbers.
  Inputs        :
      n     -> board size
      board -> 2D array that stores symbols (X, O, Z)
  Output        : None
  Logic         :
      - Print row and column numbers for guidance.
      - Print X, O, or Z for each filled cell.
      - Print lines (| and ---) to make the grid visible.

  Board Design :
      The board is printed like a real tic-tac-toe grid.
      Example (3x3):

            1   2   3
        1   X | O | Z
           ---+---+---
        2   O | X | O
           ---+---+---
        3   Z | O | X
----------------------------------------------------------------*/

void printBoard(int n, char **board){
	printf("\n"); //For space before the board
        printf("   "); //Print space before 1st column number(1)

	for(int j = 0; j < n; j++){ //To print column number 1 to n
		printf(" %d ", j + 1);
		if(j < n - 1)  //To make gap between the numbers, except last
			printf(" "); //Print a spaces
	}
	printf("\n"); //For next line

	for(int i = 0; i < n; i++){  //To print raw numbers 1 to n
		printf(" %d ", i + 1);

		for(int j = 0; j < n; j++){  //To loop through each column in the current row
			printf(" %c ", board[i][j]); //Print X or O or Z in the cell " X "

			if(j < n - 1)  //Print | to split  column between characters except last
				printf("|");
		}
		printf("\n"); //For the next line

		if(i < n - 1){
			printf("   "); //for allign with row
			for(int j = 0; j < n; j++){
				printf("---"); //Horizontal line to match with cell " X "
				if(j < n - 1)
					printf("+"); //Connecting vertical with horizantal
			}
			printf("\n"); //Move to next line after print horizantal lines
		}
	}
	printf("\n"); //Additional line after completing board
}

/*---------------------------------------------------------------
  Function Name : getMove
  Purpose       : To get the move from the player.
  Inputs        :
      n          -> board size
      board      -> 2D board
      *r, *c     -> pointers to store row and column
      sym        -> player's symbol
      playerNum  -> current player's number
  Output        : 0 if move is valid, 1 if invalid
  Logic         :
      - Ask player to enter row and column numbers.
      - Convert input to 0-based index.
      - Use validateMove() to check if move is valid.
      - If valid, store the indexes in *r and *c.
----------------------------------------------------------------*/

int getMove(int n, char **board, int *r, int *c, char sym, int playerNum){
	int row;    //Declare row & column
	int column;

	printf("Player %d (%c), enter your move (row column Eg. 1 2): ", playerNum, sym); //Get row column number from player
	scanf("%d %d", &row , &column);

	int row_index = row -1;  //Convert 1 based row to 0 based array index
	int col_index = column -1;  //Convert 1 based column to 0 based array index

	if(validateMove(n, board, row_index, col_index)){  //If valid, then store 0 based row and column indexes to row and column
		*r = row_index;
		*c = col_index;
		return 0;  //Success
	}
	else
		return 1;  //Move invalid
}

/*---------------------------------------------------------------
  Function Name : validateMove
  Purpose       : To check if the entered move is valid or not.
  Inputs        :
      n        -> size of the board
      board    -> 2D board
      row, col -> chosen position by player
  Output        : 1 if valid, 0 if invalid
  Logic         :
      - Make sure row and column are inside board limits.
      - Check if the chosen cell is empty.
      - Return 1 if both checks are true, else 0.
----------------------------------------------------------------*/

int validateMove(int n, char **board, int row, int column){
	if(row < 0 || row >= n || column < 0 || column >= n){   //Check if row or column size outside the board
		printf("Invalid move. row and column must been 1 and %d.\n",n);
		return 0; //Invalid move
	}
	if(board[row][column] != ' '){  //Check is that cell already chosen
		printf("Invalid move. Cell is already occupied.\n");  
		return 0; //Invalid move
	}
	return 1; //Valid move user can use it
}

/*---------------------------------------------------------------
  Function Name : computerMove
  Purpose       : To let the computer choose a random valid move.
  Inputs        :
      n      -> board size
      board  -> 2D board
      sym    -> computer's symbol
      *r, *c -> pointers to store chosen row and column
  Output        : 0 (after placing move)
  Logic         :
      - Generate random row and column using rand().
      - Repeat until an empty cell is found.
      - Place the symbol and return the chosen row and column.
----------------------------------------------------------------*/

int computerMove(int n, char **board, char sym, int *r, int *c){
	int row_index;  //0 based row index
	int col_index;  //0 based column index

	do{                             //Loop until get a valid move
		row_index = rand() % n;
		col_index = rand() % n;
	} while((!validateMove(n, board, row_index, col_index)));

	*r = row_index;  //Store the valid row and column index
	*c = col_index;

	makeMove(n, board, row_index, col_index, sym);  //Place the computer's symbol
	return 0;  //Success
}

/*---------------------------------------------------------------
  Function Name : makeMove
  Purpose       : To place a player's symbol on the board.
  Inputs        :
      n        -> board size
      board    -> 2D board
      row, col -> chosen position
      sym      -> player's symbol
  Output        : None
  Logic         :
      - Assign the player's symbol (X, O, or Z) to the selected cell.
----------------------------------------------------------------*/

void makeMove(int n, char **board, int row, int column, char sym){
	board[row][column] = sym; //Place the user's symbol in that cell
}

/*---------------------------------------------------------------
  Function Name : checkWin
  Purpose       : To find out if the current player has won.
  Inputs        :
      n     -> board size
      board -> 2D board with symbols
      sym   -> player's symbol (X, O, or Z)
  Output        : 1 if player wins, 0 otherwise
  Logic         :
      - Check each row: all cells must match the player's symbol.
      - Check each column: all cells must match the symbol.
      - Check main diagonal and anti-diagonal.
      - If any of these are fully matched, return 1.
----------------------------------------------------------------*/

int checkWin(int n, char **board, char sym){

	//Check rows
	for(int i = 0; i < n; i++){ //Loop through each row
		int win = 1;   //Assume this row is a winning row
		for(int j = 0; j < n; j++){  //Loop through each column in thsat row
			if(board[i][j] != sym){  //If any cell doesn't gave same symbol
				win = 0; //This isn't a winning raw
				break; //stop checking this row
			}
		}
		if(win) //if all cells in same row have same symbol. That is a winning row
			return 1; //Winner
	}

	//Check columns
	for(int j = 0; j < n; j++){ //Loop through each column
		int win = 1;  //Assuming this column is a winning column
		for(int i = 0; i < n; i++){ //Loop through each rows
			if(board[i][j] != sym){ //If any cell doesn't have same symbol
				win = 0; //This isn't winning column
				break; //Stop checking this column
			}
		}
		if(win) //If all cells in the same column have same symbol. That is a winning column
			return 1;
	}

	//Check diagonals
	int win = 1; //Assuming main diagonal is a winning diagonal
	for(int i = 0; i < n; i++){ //Loop through each cell in the main diagonal
	        if(board[i][i] != sym){ //If any cell doesn't have same symbol
			win = 0; //This isn't winning main diagonal
		        break; //Stop checking
			}
		}

		if(win)
			return 1; //If all cells in the main diagonal have same symbol. That is a winning diagonal


	//Check anti diagonals
	win = 1; //Assuming main diagonal is a winning diagonal
	for(int i = 0; i < n; i++){ //Loop through each cell in the anti diagonal
		if(board[i][n - i - 1] != sym){ //If any cell doesn't have same symbol
			win = 0; //This isn't winning anti diagonal
			break; //Stop checking
		    }
	    }

		if(win)
			return 1; //If all cells in the anti diagonal have same symbol. That is winning diagonal
	return 0;
}

/*---------------------------------------------------------------
  Function Name : checkDraw
  Purpose       : To check if the game has ended in a draw.
  Inputs        :
      n     -> board size
      board -> 2D board
  Output        : 1 if draw, 0 otherwise
  Logic         :
      - Go through every cell on the board.
      - If all cells are filled and no one has won, it is a draw.
----------------------------------------------------------------*/

int checkDraw(int n, char **board){
	for(int i = 0; i < n; i++){   //Loop through each row
		for(int j = 0; j< n; j++){   //Loop through each column
			if(board[i][j] == ' '){   //If any cell is empty
				return 0;  //Not a draw, there are still moves left
			}
		}
	}
	return 1;  //If all cells are filled and no winner, then it's a draw
}


/*---------------------------------------------------------------
  Function Name : gameOver
  Purpose       : To check if the game is over (win or draw).
  Inputs        :
      n             -> board size
      board         -> 2D board
      currentPlayer -> number of player playing
      currentSym    -> symbol of current player
  Output        : 1 if game over, 0 if game continues
  Logic         :
      - Use checkWin() to see if player has won.
      - If not, use checkDraw() to check if board is full.
      - Print message based on result and return 1 if over.
----------------------------------------------------------------*/

int gameOver(int n, char **board, int currentPlayer, char currentSym){
	if(checkWin(n, board, currentSym)){   //Check if current player is won
		printf("Player %d (%c) wins!\n", currentPlayer, currentSym);  //Print winning message
		return 1;  //Game over
	}
	if(checkDraw(n, board)){  //Check if the game is draw
		printf("It's a draw! No more moves left.\n");  //Print draw message
		return 1;  //Game over
	}
	return 0; //Game continues
}

