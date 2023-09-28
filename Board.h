#ifndef BOARD_H
#define BOARD_H

/**
 * @file board.h
 * @brief Board Header
 *
 * This header file defines functions and data structures related to the game board.
 */

#include "Constant.h"
#include <string.h>
#include <stdio.h>


extern char board[SIZE][SIZE];
extern char copyboard[SIZE][SIZE];
/* 
    Board of the game
*/

/**
 * @brief Create the game board and initialize it.
 *
 * This function initializes the game board, filling it with empty values.
 */
void initialization() ; //Create the board

/**
 * @brief Print the game board to the console.
 *
 * This function prints the current state of the game board to the console.
 */
void displayBoard(); //print the board


/**
 * @brief Copy the current game board to a secondary board.
 *
 * This function copies the contents of the current game board to another board.
 */
void pasteBoard();

/**
 * @brief Convert a user input position to row and column coordinates.
 *
 * This function converts a user-provided position (e.g., "A1") to row and column coordinates.
 *
 * @param position The user input position string.
 * @param ligne Pointer to an integer to store the row coordinate.
 * @param colonne Pointer to an integer to store the column coordinate.
 */
void convertirPosition(char position[3], int *ligne, int *colonne);


#endif
