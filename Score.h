/**
 * @file Score.h
 * @brief Header file for evaluating the game board and calculating scores.
 *
 * This header file contains declarations for functions used to evaluate the game board
 * and calculate scores based on the current state of the board. These functions are
 * used in the game's artificial intelligence (AI) logic to make informed moves.
 */

#ifndef SCORE_H
#define SCORE_H
#include "Constant.h"
#include <stdbool.h>

/**
 * @brief Evaluate the game board for a given player.
 *
 * This function evaluates the game board for a specified player and returns a score
 * that represents the board's favorability for that player. The score is based on various
 * factors, including the presence of adjacent pieces and potential winning conditions.
 *
 * @param array The game board represented as a 2D array.
 * @param player The player color (BLUE or RED).
 * @return An integer score representing the favorability of the board for the player.
 */
int evaluateBoard(char array[SIZE][SIZE], char player);





#endif
