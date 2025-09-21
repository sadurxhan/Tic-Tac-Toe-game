#include<stdio.h>

void initializeBoard(int n, char board[n][n]);
void printBoard(int n, char board[n][n]);
int  getMove(int n, char board[n][n], int *r, int *c, char sym);

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

    /* int Game_Mode;

    printf("1. Two Player\n");
    printf("2. Player vs Computer\n");
    printf("3. Multi Player\n");
    printf("Select Game Mode : ");
    scanf("%d", &Game_Mode);

    if(Game_Mode == 1){
        printf("Starting Two Player mode...\n");
    
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
    } */
    return 0;
}

void initializeBoard(int n, char board[n][n]){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            board[i][j] = '_';
}

void printBoard(int n, char board[n][n]){
    printf("\n   ");
    for(int j=0;j<n;j++) printf("%2d", j+1);
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%2d ", i+1);
        for(int j=0;j<n;j++) printf("%2c", board[i][j]);
        printf("\n");
    }
}

int  getMove(int n, char board[n][n], int *r, int *c, char sym){
        int raw , coloum;
        printf("Enter your move (row and column) for %c:", sym);
        scanf("%d %d", &raw, &coloum);
        if(raw < 1 || raw > n || coloum < 1 || coloum > n || board[raw][coloum] != '_'){
            printf("Invalid move. Try again.\n");
            return 1;
        }
}
