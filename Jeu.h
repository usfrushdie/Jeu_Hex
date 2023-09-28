#ifndef GAME_H
#define GAME_H

/**
 * @file jeu.h
 * @brief Game Header
 *
 * This header file contains declarations for functions and data structures related to the Hex Game.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "Board.h"
#include "Score.h"
#include "Constant.h"

/**
 * @brief Recursive depth-first search for player Blue.
 *
 * Marks the squares visited by the player, searching for a link between the left and right sides.
 * If a link exists, player Blue wins.
 *
 * @param x Starting X-coordinate.
 * @param y Starting Y-coordinate.
 * @param player The player's color (BLUE or RED).
 * @param visited 2D array to mark visited squares.
 * @param tab The game board.
 * @return 1 if the player Blue wins, 0 otherwise.
 */
int dfsb(int x, int y, char player, int visited[][SIZE], char tab[SIZE][SIZE]);


/**
 * @brief Recursive depth-first search for player Red.
 *
 * Marks the squares visited by the player, searching for a link between the top and bottom sides.
 * If a link exists, player Red wins.
 *
 * @param x Starting X-coordinate.
 * @param y Starting Y-coordinate.
 * @param player The player's color (BLUE or RED).
 * @param visited 2D array to mark visited squares.
 * @param tab The game board.
 * @return 1 if the player Red wins, 0 otherwise.
 */
int dfsr(int x, int y, char player, int visited[][SIZE], char tab[SIZE][SIZE]) ;

/**
 * @brief Check if a specified column (or row) contains a player's piece.
 *
 * @param tab The game board.
 * @param colnotraw If 1, check the column; if 0, check the row.
 * @param chooseone The column (or row) to check.
 * @return 1 if the column (or row) contains a player's piece, 0 otherwise.
 */
int checkexist(char tab[SIZE][SIZE],int colnotraw, int chooseone);

/**
 * @brief Check the victory condition for a player.
 *
 * @param player The player's color (BLUE or RED).
 * @param tab The game board.
 * @return 1 if the player wins, 0 otherwise.
 */
int CheckVictory(char player, char tab[SIZE][SIZE]);

/**
 * @brief AI's implementation of player vs. player gameplay.
 */
void playervplayer();

#endif
