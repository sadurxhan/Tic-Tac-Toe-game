#include<stdio.h>

void initializeBoard(int n, char b[n][n]);
void printBoard(int n, char b[n][n]);
int  getMove(int n, char b[n][n], int *r, int *c, char sym);
void placeSymbol(int n, char b[n][n], int r, int c, char sym);
int  inBounds(int n, int r, int c);
int  isEmpty(int n, char b[n][n], int r, int c);
void clearStdin(void);

int main(){

    int size;

    printf("Enter the board size N (3 <= size <= 10) : ");
    scanf("%d", &size);

    if(size < 3 || size > 10){
        printf("Invalid board size. Please enter a value between 3 and 10.\n");
        return 1;
    }

    char board[size][size];

    initializeBoard(size, board);
    printBoard(size, board);

    int Game_Mode;

    printf("1. Two Player\n");
    printf("2. Player vs Computer\n");
    printf("3. Multi Player\n");
    printf("Select Game Mode : ");
    scanf("%d", &Game_Mode);

    if(Game_Mode == 1){
        printf("Starting Two Player mode...\n");
        void initializeBoard(int size, char board[size][size]);
    
    } else if(Game_Mode == 2){
        printf("Starting Player vs Computer mode...\n");
    
    } else if(Game_Mode == 3){
        printf("Slect number of players : ");
        int numPlayers;
        scanf("%d", &numPlayers);
        printf("Starting Multi Player mode...\n");
    
    } else {
        printf("Invalid game mode. Please select a valid option.\n");
        return 1;
    }
    return 0;
}

void initializeBoard(int n, char b[n][n]){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            b[i][j] = '_';
}

void printBoard(int n, char b[n][n]){
    printf("\n   ");
    for(int j=0;j<n;j++) printf("%2d", j+1);
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%2d ", i+1);
        for(int j=0;j<n;j++) printf("%2c", b[i][j]);
        printf("\n");
    }
}