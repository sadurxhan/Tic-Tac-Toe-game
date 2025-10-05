#include "tictactoe.h"

/*---------------------------------------------------------------
  Function Name : main
  Purpose       : To control the full game flow.
  Inputs        : None
  Output        : 0 when game ends successfully
  Logic         :
      - Ask user for board size and game mode.
      - Create board using malloc.
      - Start the game loop for player and computer turns.
      - Record moves in file.
      - Stop when player wins or game draws.
      - Free all allocated memory at the end.
----------------------------------------------------------------*/

int main(void){

        srand(time(NULL));  //To generate computer moves

        int size; //Size of the board
        int Game_Mode; //Game mode selection
        int playerNum; //Number of players
        int currentPlayer; //To track current player
        char currentSym; //To track current player's symbol

        printf("           ---------------------------------\n");
        printf("                       Welcome             \n");
        printf("                         to                \n");
        printf("                 Tic-Tac-Toe Game ^_'      \n");
        printf("           ---------------------------------\n \n");

        printf("Enter the size of the board: ");  //Get board size from user
        scanf("%d", &size);

        if(size < 3 || size > 10){ //Check whether size between 3 to 10
                printf("Invalid board size. Select between 3 to 10.\n");
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

        FILE *log = fopen("gamelog.txt", "w"); //Open write mode in file
        if(log){  //If file opened successfully
                fprintf(log, "--- Tic Tac Toe Game ---\n"); //Write header to the file
                fclose(log); //Close the file
        }

        while(1){    //Until return statement equals to 1, check game over
                printBoard(size, board);  //Print the board

                if(currentPlayer == 1)  //Set current player's symbol
                        currentSym = Player1;
                else if(currentPlayer == 2)
                        currentSym = Player2;
                else
                        currentSym = Player3;
	
	int row, col;  //To store row and column of the move

        if((Game_Mode == 2 && currentPlayer == 2) || (Game_Mode == 3 && currentPlayer > 1)){  //Computer's turn
                computerMove(size, board, currentSym, &row, &col);  //Make computer move
                printf("Computer (Player %d, %c) plays at %d %d\n", currentPlayer, currentSym, row+1, col+1); //Print computer's move
        }
        else{
                while(getMove(size, board, &row, &col, currentSym, currentPlayer))  //Get move from user until valid
                        printf("Please enter a valid move.\n");
                makeMove(size, board, row, col, currentSym); //Place the symbol on the board
        }

	// Log the move
        log = fopen("gamelog.txt", "a");  //Open append mode in file
        if(log){  //If file opened
                //Write moves in the file
                fprintf(log, "Player %d (%c) -> Row %d, Column %d\n", currentPlayer, currentSym, row + 1, col + 1);
                fclose(log); //Close the file
        }

        if(gameOver(size, board, currentPlayer, currentSym)){  //Check if game is over
                printBoard(size, board);  //Print the board
                break;  //Exit the loop
        }

        currentPlayer = (currentPlayer % playerNum) + 1; //Switch to next player

        }

	printf("          ---------------------------------\n");
        printf("                      Game Over            \n");  //Game over message
        printf("                 Thanks for playing!       \n");
        printf("          ---------------------------------\n");

        for (int i = 0; i < size; i++) //Free the allocated memory
            free(board[i]);

        free(board);
        return 0; //Exit the main function
}





