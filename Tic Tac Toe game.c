#include<stdio.h>

int main(){

    int size;

    printf("Enter the board size N (3 <= N <= 10) : ");
    scanf("%d", &size);

    if(size < 3 || size > 10){
        printf("Invalid board size. Please enter a value between 3 and 10.\n");
        return 1;
    }

int Game_Mode;
    printf("1. Two Player\n");
    printf("2. Player vs Computer\n");
    printf("3. Multi Player\n");
    printf("Select Game Mode : ");
    scanf("%d", &Game_Mode);
    
    if(Game_Mode < 1 || Game_Mode > 3){
        printf("Invalid game mode. Please select a valid option.\n");
        return 1;
    }

    if(Game_Mode == 1){
        printf("Starting Two Player mode...\n");
    
    } else if(Game_Mode == 2){
        printf("Starting Player vs Computer mode...\n");
    
    } else if(Game_Mode == 3){
        printf("Slect number of players (3-10) : ");
        int numPlayers;
        scanf("%d", &numPlayers);
        printf("Starting Multi Player mode...\n");
    }
    return 0;
}