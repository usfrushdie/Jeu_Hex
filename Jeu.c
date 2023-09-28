/**
 * @file Jeu.c
 * @brief Implementation of functions related to the Hex game logic.
 */

#include "Jeu.h"

/**
 * @brief Depth-First Search for Blue Player (Horizontal)
 *
 * This function performs a depth-first search (DFS) to check for a connected path
 * from the left side to the right side of the Hex board for the Blue player.
 *
 * @param x Current column index.
 * @param y Current row index.
 * @param player The player color (BLUE or RED).
 * @param visited A 2D array to mark visited squares.
 * @param tab The Hex game board.
 * @return 1 if a winning path is found; otherwise, 0.
 */
int dfsb(int x, int y, char player, int visited[][SIZE],char tab[SIZE][SIZE]) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || visited[x][y] || tab[x][y] != player) {
        return 0;  // Case to stop DFS research
    }
    visited[x][y] = 1;  // Marks the square as visited

    if (y == SIZE - 1) {
        return 1;  // The player has arrived to the right side, he wins.
    }

    // Recursive calls of DFS for neighboring squares
    if (dfsb(x - 1, y - 1, player, visited,tab) || dfsb(x + 1, y + 1, player, visited,tab) ||
        dfsb(x - 1, y + 1, player, visited,tab) || dfsb(x + 1, y - 1, player, visited,tab)) {
        return 1;  // If the neigboring square creates a victory, return 1
    }
    return 0;
    } 

/**
 * @brief Depth-First Search for Red Player (Vertical)
 *
 * This function performs a depth-first search (DFS) to check for a connected path
 * from the top side to the bottom side of the Hex board for the Red player.
 *
 * @param x Current column index.
 * @param y Current row index.
 * @param player The player color (BLUE or RED).
 * @param visited A 2D array to mark visited squares.
 * @param tab The Hex game board.
 * @return 1 if a winning path is found; otherwise, 0.
 */
int dfsr(int x, int y, char player, int visited[][SIZE],char tab[SIZE][SIZE]) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || visited[y][x] || tab[y][x] != player) {
        return 0;  // Case to stop DFS research
    }
    visited[y][x] = 1;  // Marks the square as visited

    if (y == SIZE - 1) {
        return 1;  // The player has arrived to the bottom side, he wins.
    }

    // Recursive calls of DFS for neighboring squares
    if (dfsr(x - 1, y - 1, player, visited,tab) || dfsr(x + 1, y + 1, player, visited,tab) ||
        dfsr(x - 1, y + 1, player, visited,tab) || dfsr(x + 1, y - 1, player, visited,tab)) {
        return 1;  // Si l'un des voisins conduit à la victoire, retourne 1
    }
    return 0;
    }
    
    /**
 * @brief Check for the Existence of Opponent's Pieces in a Column or Row
 *
 * This function checks if there are opponent's pieces in a specified column or row
 * on the Hex game board.
 *
 * @param tab The Hex game board.
 * @param colnotraw Flag indicating whether to check a column (1) or row (0).
 * @param chooseone The index of the column or row to check.
 * @return 1 if player's pieces are found; otherwise, 0.
 */
int checkexist(char tab[SIZE][SIZE],int colnotraw,int chooseone){
    int rep=0;
    int i;
    for (i = 0; i < SIZE; i++){if (colnotraw){if (tab[i][chooseone]==BLUE){rep=1; break;}}else {if (tab[chooseone][i]==RED){rep=1; break;}}}
    
    return rep;
}

 /**
 * @brief Check for Victory Condition
 *
 * This function checks if a player has won the Hex game by connecting their pieces
 * from one side to the other.
 *
 * @param player The player color (BLUE or RED).
 * @param tab The Hex game board.
 * @return 1 if the player has won; otherwise, 0.
 */
int CheckVictory(char player, char tab[SIZE][SIZE]) {
    // Search for a horizontal link from the left side to the right one
    if (player==BLUE){
    
	
    int i;
    for (i = 0; i < SIZE; i++) { if (checkexist(tab,1,5)){
        if (tab[i][0] == player) {
            int visited[SIZE][SIZE] = {0};  // Table to mark visited squares
            if (dfsb(i, 0, player, visited,tab)) {
                return 1;  // 'player blue' has won
            }}
        }
    }
    return 0; }
	if (player==RED){
	
    int i;
    for (i = 0; i < SIZE; i++) {if(checkexist(tab,0,5)){
        if (tab[0][i] == player) {
            int visited[SIZE][SIZE] = {0};  // Table to mark visited squares
            if (dfsr(i, 0, player, visited,tab)) {
                return 1;  // 'player red' has won
            }}
        }
    }
    return 0; } // still no winner
return 0;
}



/**
 * @brief AI's implementation of player vs. player gameplay.
 */
void playervplayer(){
    initialization();

	int cond=0;// this a condition to know if the turn ends
	char player = BLUE;//to know whose turn it is
	
	
	int turn = 0;
	while (turn < 36){
	

	printf("player %c where do you play ?\n", player);
	char pos[3];
    int c;
    int l;//coord c too
	while (cond==0){
	scanf("%s", pos); 
    if(strlen(pos)!=2){while(strlen(pos) != 2){printf("Bad instruction \n Please enter a letter between A and E and a digit between 1 and 6 : \n");scanf("%s", pos);}}
    convertirPosition(pos, &c, &l);

	
    
    
    if(board[c][l]==EMPTY){cond=1; board[c][l]=player; printf("well play\n\n"); displayBoard();
    }
	
   
    
    
    else {printf("you can't play there!");}
	}
    
if (CheckVictory(player, board)){printf("Victory player %c, you're so strong dude !", player);break;}

cond=0; if (player==BLUE){player= RED;} else{player=BLUE;} turn++;
}
printf("end of the game");

}




