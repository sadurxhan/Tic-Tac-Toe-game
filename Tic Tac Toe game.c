#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define Player1 'X'
#define Player2 'O'
#define Player3 'Z'

void initializeBoard(int n, char board[n][n]);
void printBoard(int n, char board[n][n]);
int getMove(int n, char board[n][n], int *r, int *c, char sym, int playerNum);
int ComputerMove(int n, char board[n][n], char sym, int *r, int *c);
int validateMove(int n, char board[n][n], int row, int column);
void makeMove(int n, char board[n][n], int row, int column, char sym);
int checkWin(int n, char board[n][n], char sym);
int checkDraw(int n, char board[n][n], char sym);
int gameOver(int n, char board[n][n], int currentPlayer, char currentSym);

int main(void){

	srand(time(NULL));

	int size;
	int Game_Mode;
	int playerNum;
	int currentPlayer;
	char currentSym;

	printf("=================================\n");
	printf("             Welcome             \n");
	printf("               to                \n");
        printf("       Tic-Tac-Toe Game ^_'      \n");
	printf("==================================\n \n");
	
	printf("Enter the size of the board: ");
	scanf("%d", &size);

	if(size < 3 || size > 10){ //Check whether size between 3 to 10
		printf("Invalid board size. Select between 3 to 10.");
		return 1;
	}

	char board[size][size]; // declare 2D array for board
    initializeBoard(size, board);
	       
    printf("1. Two Player\n");
    printf("2. Player vs Computer\n");
    printf("3. Multi Player\n");
    
	printf("Select Game Mode : ");
    scanf("%d", &Game_Mode);;

	if (Game_Mode == 1) {
        printf("Starting Two Player Mode....\n");
        playerNum = 2;
    } 
    else if (Game_Mode == 2){
        printf("Starting Player vs Computer Mode....\n");
        playerNum = 2;
    } 
    else if(Game_Mode == 3){
        printf("Enter the number of Players: ");
        scanf("%d", &playerNum);
        if(playerNum == 3)
            printf("Starting Multi-Player Mode....\n");
        else{
            printf("Currently 3 Player Mode only available\n");
            return 1;
        }
    } 
    else{
        printf("Invalid game mode. Select a valid mode\n");
        return 1;
    }

    currentPlayer = 1;

    while(1){
        printBoard(size, board);

        if(currentPlayer == 1)
            currentSym = Player1;
        else if(currentPlayer == 2)
            currentSym = Player2;
        else
            currentSym = Player3;

        int row, col;

        if((Game_Mode == 2 && currentPlayer == 2) || (Game_Mode == 3 && currentPlayer > 1)) {
            ComputerMove(size, board, currentSym, &row, &col);
            printf("Computer (Player %d, %c) plays at %d %d\n", currentPlayer, currentSym, row+1, col+1);
        } else {
            while(getMove(size, board, &row, &col, currentSym, currentPlayer)){
            }
            makeMove(size, board, row, col, currentSym);
        }

        if(gameOver(size, board, currentPlayer, currentSym)){
            printBoard(size, board);
            break;
        }

        currentPlayer = (currentPlayer % playerNum) + 1;
    }

	printf("Game Over. Thanks for playing!\n");
    return 0;
}

//Function to initialize the game board
void initializeBoard(int n,char board[n][n]){ //Fill the game board with emply spaces
	for(int i = 0; i < n; i++){   //To iterate over each row of the board
		for(int j = 0; j < n; j++){  //To iterate over each column of the board
			board[i][j] = ' ';  //Initialize each character in the array to space ' '
		}
	}
}

//Function to print the tic-tac-toe board
void printBoard(int n, char board[n][n]){
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
int getMove(int n, char board[n][n], int *r, int *c, char sym, int playerNum){
	int row;    //Declare row & column to get input
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
int validateMove(int n, char board[n][n], int row, int column){
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
int ComputerMove(int n, char board[n][n], char sym, int *r, int *c){
	int row_index;
	int col_index;

	do{
		row_index = rand() % n;
		col_index = rand() % n;
	} while((!validateMove(n, board, row_index, col_index)));
	
	*r = row_index;
	*c = col_index;

	makeMove(n, board, row_index, col_index, sym);
	return 0;
}

//Function to place symbol of the user
void makeMove(int n, char board[n][n], int row, int column, char sym){
	board[row][column] = sym; //Place the user's symbol in that cell
}

//Function to checki if player has win
int checkWin(int n, char board[n][n], char sym){

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
	        
		if(win)
			return 1; //If all cells in the main diagonal have same symbol. That is a winning diagonal
	}

	//Check anti diagonals
	win = 1; //Assuming main diagonal is a winning diagonal
	for(int i = 0; i < n; i++){ //Loop through each cell in the anti diagonal
		if(board[i][n - i - 1] != sym){ //If any cell doesn't have same symbol
			win = 0; //This isn't winning anti diagonal
			break; //Stop checking
		}
			
		if(win)
			return 1; //If all cells in the anti diagonal have same symbol. That is winning diagonal 
	}
	return 0;
}

//Function to check draw
int checkDraw(int n, char board[n][n], char sym){
	for(int i = 0; i < n; i++){
		for(int j = 0; j< n; j++){
			if(board[i][j] == ' '){
				return 0;
			}
		}
	}
	return 1;
}

//Function to end game
int gameOver(int n, char board[n][n], int currentPlayer, char currentSym){
	if(checkWin(n, board, currentSym)){
		printf("Player %d (%c) wins!\n", currentPlayer, currentSym);
		return 1;
	}
	if(checkDraw(n, board, currentSym)){
		printf("It's a draw! No more moves left.\n");
		return 1;
	}
	return 0;
}

