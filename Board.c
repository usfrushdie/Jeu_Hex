/**
 * @file Board.c
 * @brief Hex Game Board Functions
 * @author Group 5
 * @date 2023-09-22
 */

/**
 * @defgroup BoardModule Board Module
 * @brief Functions and structures related to the game board.
 */

/**
 * @file Board.h
 * @brief Board Module Header
 * @ingroup BoardModule
 */
#include "Board.h"

char board[SIZE][SIZE];
char copyboard[SIZE][SIZE];

/**
 * @fn void initialization()
 * @brief Initialize the Hex game board with empty cells.
 *
 * This function fills the entire Hex game board with empty cells (var EMPTY).
 */
/* Fill the board with the var Empty */
void initialization(){
    int i;
	int j;
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            board[i][j] = EMPTY ;
        }
	}
}



/**
 * @fn void displayBoard()
 * @brief Display the Hex game board.
 *
 * This function prints the current state of the Hex game board, including cell contents.
 */
void displayBoard(){
	int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("+---+"); // Upper line
        }
        printf("\n"); // New line

        for (j = 0; j < SIZE; j++) {
            if (board[i][j]==RED)
                {printf("| \x1b[31mR\x1b[0m |"); // Cell
                }
            else {if (board[i][j]==BLUE)
                {printf("| \x1b[34mB\x1b[0m |"); // Cell
                }
            else{
            printf("| %c |", board[i][j]); // Cell
            }}
        }
        printf("\n"); // New line
    }

    // Ligne du bas du cadre
    for (j = 0; j < SIZE; j++) {
        printf("+---+");
    }
    printf("\n");
	}
	
/**
 * @fn void pasteBoard()
 * @brief Copy the contents of the game board to a backup board.
 *
 * This function creates a copy of the current Hex game board and stores it in a backup board (copyboard).
 */
void pasteBoard(){
    int i;
    int j;
     for ( i = 0; i < SIZE; i++){
        for ( j = 0; j < SIZE; j++){
            copyboard[i][j]=board[i][j];
}
}
}

/**
 * @fn void convertirPosition(char position[3], int *ligne, int *colonne)
 * @brief Convert a user-entered position to board indices.
 *
 * This function takes a user-entered position (e.g., "A1") and converts it to corresponding
 * row (ligne) and column (colonne) indices for the Hex game board.
 *
 * @param position The user-entered position string (e.g., "A1").
 * @param ligne Pointer to store the row index.
 * @param colonne Pointer to store the column index.
 */
void convertirPosition(char position[3], int *ligne, int *colonne) {
    *colonne = position[0] - 'A';
    *ligne = position[1] - '1';
}


