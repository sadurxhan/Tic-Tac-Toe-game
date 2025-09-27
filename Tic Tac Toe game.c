#include<stdio.h>

#define Player1 'X'
#define Player2 'O'
#define Player3 'Z'

void initializeBoard(int n, char board[n][n]);
void printBoard(int n, char board[n][n]);
int getMove(int n, char board[n][n], int *r, int *c, char sym, int playerNum);

int main(){
    int size;
    int Game_Mode;

    printf("Enter the board size n (3 <= size <= 10) : ");
    scanf("%d", &size);

    if(size < 3 || size > 10){
        printf("Invalid board size. Please enter a value between 3 and 10.\n");
        return 1;
    }
    char board[size][size];
    initializeBoard(size, board);   
    printBoard(size, board);

    printf("1. Two Player\n");
    //printf("2. Player vs Computer\n");
    //printf("3. Multi Player\n");
    printf("Select Game Mode : ");
    scanf("%d", &Game_Mode);

    if(Game_Mode == 1){
        printf("Starting Two Player mode...\n");
    
    } /* else if(Game_Mode == 2){
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
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard(int n, char board[n][n]){
    printf("\n");
    printf("   ");

    for(int j = 0; j < n; j++) {
        printf(" %d ", j + 1);
        if(j < n - 1) printf(" ");
    }
    printf("\n");
    
    for(int i = 0; i < n; i++) {
        printf(" %d ", i + 1);
        
        for(int j = 0; j < n; j++) {
            printf(" %c ", board[i][j]);
            if(j < n - 1) printf("|");
        }
        printf("\n");
        
        if(i < n - 1) {
            printf("   ");
            for(int j = 0; j < n; j++){
                printf("---");
                if(j < n - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

int getMove(int n, char board[n][n], int *r, int *c, char sym, int playerNum) {
    int raw, coloum;
    printf("Player %d (%c), enter your move (row column): ", playerNum, sym); 
    scanf("%d %d", &raw, &coloum);
    
    int row_index = raw - 1;
    int col_index = coloum - 1;
    
    if (validateMove(n, board, row_index, col_index)) {
        *r = row_index;
        *c = col_index; 
        return 0;
    } else {
        return 1;
    }
}

int validateMove(int n, char board[n][n], int row, int col){
    if(row < 0 || row >= n || col < 0 || col >= n) {
        printf("Invalid move. Row and column must be between 1 and %d.\n", n);
        return 0;
    }
    if(board[row][col] != ' ') {
        printf("Invalid move. Cell is already occupied.\n");
        return 0;
    }
    return 1;
}

void makeMove(int n, char board[n][n], int row, int col, char sym){
    board[row][col] = sym;
}

int checkWin(int n, char board[n][n], char sym){

    // Check rows
    for(int i = 0; i < n; i++) {
        int win = 1;
        for(int j = 0; j < n; j++) {
            if(board[i][j] != sym) {
                win = 0;
                break;
            }
        }
        if(win) return 1;
    }

    // Check columns
    for(int j = 0; j < n; j++) {
        int win = 1;
        for(int i = 0; i < n; i++) {
            if(board[i][j] != sym) {
                win = 0;
                break;
            }
        }
        if(win) return 1;
    }

    // Check main diagonal
    int win = 1;
    for(int i = 0; i < n; i++) {
        if(board[i][i] != sym) {
            win = 0;
            break;
        }
    }
    if(win) return 1;

    // Check anti diagonal
    win = 1;
    for(int i = 0; i < n; i++) {
        if(board[i][n - 1 - i] != sym) {
            win = 0;
            break;
        }
    }
    if(win) return 1;

    return 0;
}
