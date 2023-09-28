#ifndef IA_H
#define IA_H

/**
 * @file IA.h
 * @brief Artificial Intelligence Header
 *
 * This header file contains declarations for functions and data structures related to the game's artificial intelligence.
 */

#include "Constant.h"
#include "Jeu.h"
#include <unistd.h>



#define MAX_DEPTH 5
// Structure pour représenter une position sur le plateau
typedef struct {
    int row;
    int col;
} Move;

/**
 * @brief Minimax algorithm with alpha-beta pruning.
 *
 * This recursive function implements the minimax algorithm with alpha-beta pruning for AI gameplay.
 *
 * @param board The game board.
 * @param depth The current depth in the search tree.
 * @param isMaximizingPlayer 1 if it's the maximizing player's turn, 0 otherwise.
 * @param alpha The alpha value for alpha-beta pruning.
 * @param beta The beta value for alpha-beta pruning.
 * @param plyer The player's color (BLUE or RED).
 * @return The best value for the current game state.
 */
int minimax(char board[SIZE][SIZE], int depth, int isMaximizingPlayer, int alpha, int beta,char plyer);

/**
 * @brief Find the best move for the AI player.
 *
 * This function determines the best move for the AI player using the minimax algorithm.
 *
 * @param player The player's color (BLUE or RED).
 * @param bestMoveArray An array to store the best move coordinates [row, col].
 */
Move getBestMove(char board[SIZE][SIZE],int turn,char player);

/**
 * @brief AI's implementation of player vs. computer gameplay.
 *
 * @param color The player's chosen color (BLUE or RED).
 */
void playervcomputer(char color);

/**
 * @brief AI's implementation of computer vs. computer gameplay.
 */
void computervcomputer();

#endif
