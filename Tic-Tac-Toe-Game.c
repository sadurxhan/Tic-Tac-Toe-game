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

//Main function
int main(void){

	srand(time(NULL));  //To generate computer moves

	int size; //Size of the board
	int Game_Mode; //Game mode selection
	int playerNum; //Number of players
	int currentPlayer; //To track current player
	char currentSym; //To track current player's symbol

	printf("=================================\n");
	printf("             Welcome             \n");
	printf("               to                \n");
    printf("       Tic-Tac-Toe Game ^_'      \n");
	printf("==================================\n \n");
	
	printf("Enter the size of the board: ");  //Get board size from user
	scanf("%d", &size);

	if(size < 3 || size > 10){ //Check whether size between 3 to 10
		printf("Invalid board size. Select between 3 to 10.");  
		return 1; //Exit the program
	}

	char **board = malloc(size * sizeof(char *)); //allocate rows
    for (int i = 0; i < size; i++) {
    board[i] = malloc(size * sizeof(char));   //allocate columns
    }
    
	initializeBoard(size, board); //declare 2D array for board
	       
    printf("1. Two Player\n"); 
    printf("2. Player vs Computer\n");
    printf("3. Multi Player\n");
    
	printf("Select Game Mode : "); //Get game mode from user
    scanf("%d", &Game_Mode);; 

	if (Game_Mode == 1) {  //Check game mode
        printf("Starting Two Player Mode....\n"); 
        playerNum = 2;  //Set number of players to 2
    } 
    else if (Game_Mode == 2){  //Check game mode
        printf("Starting Player vs Computer Mode....\n");
        playerNum = 2;  //Set number of players to 2
    } 
    else if(Game_Mode == 3){  //Check game mode
        printf("Enter the number of Players: ");
        scanf("%d", &playerNum);  //Get number of players from user for multiplayer mode
        if(playerNum == 3)  //Check number of players
            printf("Starting Multi-Player Mode....\n");
        else{
            printf("Currently 3 Player Mode only available\n");
            return 1; //Exit the program
        }
    } 
    else{
        printf("Invalid game mode. Select a valid mode\n");  //Check game mode
        return 1; //Exit the program
    }

    currentPlayer = 1; //Player 1 starts the game

	// Clear log file for new game
    FILE *log = fopen("gamelog.txt", "w"); //Open write mode in file
    if (log) {  //If file opened successfully
        fprintf(log, "--- Tic Tac Toe Game ---\n"); //Write header to the file
        fclose(log); //Close the file
    }

    while(1){   //Until return statement equals to 1, check game over
        printBoard(size, board);  //Print the board

        if(currentPlayer == 1)  //Set current player's symbol
            currentSym = Player1;
        else if(currentPlayer == 2)
            currentSym = Player2;
        else
            currentSym = Player3;

        int row, col;  //To store row and column of the move

        if((Game_Mode == 2 && currentPlayer == 2) || (Game_Mode == 3 && currentPlayer > 1)) {  //Computer's turn
            computerMove(size, board, currentSym, &row, &col);  //Make computer move
            printf("Computer (Player %d, %c) plays at %d %d\n", currentPlayer, currentSym, row+1, col+1); //Print computer's move
        } else {
            while(getMove(size, board, &row, &col, currentSym, currentPlayer)){ //Get move from user until valid
				printf("Please enter a valid move.\n");
            }
            makeMove(size, board, row, col, currentSym); //Place the symbol on the board
        }
		
		// Log the move
        log = fopen("gamelog.txt", "a");  //Open append mode in file
        if (log) {  //If file opened successfully
            fprintf(log, "Player %d (%c) => Row %d, Column %d\n", currentPlayer, currentSym, row + 1, col + 1); //Write moves in the file
            fclose(log); //Close the file
        }

        if(gameOver(size, board, currentPlayer, currentSym)){  //Check if game is over
            printBoard(size, board);  //Print the board
            break;  //Exit the loop
        }

        currentPlayer = (currentPlayer % playerNum) + 1; //Switch to next player
    }
    
	printf("=================================\n");
	printf("            Game Over            \n");  //Game over message
	printf("       Thanks for playing!       \n");
	printf("=================================\n");

    for (int i = 0; i < size; i++) //Free the allocated memory
	    free(board[i]);
		    
    free(board); 
        return 0; //Exit the main function
}

//Function to initialize the game board
void initializeBoard(int n,char **board){ //Fill the game board with emply spaces
	for(int i = 0; i < n; i++){   //To iterate over each row of the board
		for(int j = 0; j < n; j++){  //To iterate over each column of the board
			board[i][j] = ' ';  //Initialize each character in the array to space ' '
		}
	}
}

//Function to print the tic-tac-toe board
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

//Function to get move from the user
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

//Function to validate the user move
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

//Function to make computer moves
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

//Function to place symbol of the user
void makeMove(int n, char **board, int row, int column, char sym){
	board[row][column] = sym; //Place the user's symbol in that cell
}

//Function to checki if player has win
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

//Function to check draw
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

//Function to end game
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
