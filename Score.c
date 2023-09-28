/**
 * @file score.c
 * @brief Functions for scoring the game board.
 *
 * This source file contains the implementation of functions for scoring
 * the game board based on the positions of player tokens.
 */

#include "Score.h"
#include "Jeu.h"

/**
 * @brief Evaluates the score of the game board for a specific player.
 *
 * This function evaluates the score of the game board for a given player based on
 * the positions of their tokens. It counts the number of adjacent (diagonal)
 * tokens owned by the player and their opponent and assigns scores accordingly.
 *
 * @param array The game board represented as a 2D array.
 * @param player The player for whom the board is being evaluated (RED or BLUE).
 * @return The score of the board for the specified player.
 */
int evaluateBoard(char array[SIZE][SIZE], char player) {
    // Dans cette implémentation simple, nous allons compter le nombre de cases
    // adjacentes (diagonales) appartenant au joueur 'X' et au joueur 'O'.
    char opponent=(player==BLUE)?RED:BLUE;

    int scorePlayer= 0;
    int scoreOpponent= 0;

    // Parcourir le plateau et compter les diagonales pour chaque joueur
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == player) {
                // Si la case appartient à 'X', incrémentez son score en fonction du nombre de voisins 
                if (i > 0 && board[i - 1][j-1] == player) {
                    scorePlayer++;
                }
                if (j > 0 && board[i+1][j + 1] == player) {
                    scorePlayer++;
                }
                if (i > 0 && board[i + 1][j-1] == player) {
                    scorePlayer++;
                }
                if (j > 0 && board[i-1][j + 1] == player) {
                    scorePlayer++;
                }
            } else if (board[i][j] == opponent) {
                // Si la case appartient à 'O', incrémentez son score en fonction du nombre de voisins 
                if (i > 0 && board[i - 1][j-1] == opponent) {
                    scoreOpponent++;
                }
                if (j > 0 && board[i+1][j - 1] == opponent) {
                    scoreOpponent++;
                }
                if (i > 0 && board[i + 1][j+1] == opponent) {
                    scoreOpponent++;
                }
                if (j > 0 && board[i-1][j + 1] == opponent) {
                    scoreOpponent++;
                }
            }
        }
    }
    if (CheckVictory(player, array)){scorePlayer+=10000;} // la victoire est le plus important
    if (CheckVictory(opponent, array)){scoreOpponent+=10000;}

    if (player==BLUE){
        for (int i = 0; i < SIZE; i++) {
            
                if (checkexist(array,1,i)){scorePlayer+=500;}
            }
       

    }  
    else  {for (int i = 0; i < SIZE; i++) {
            
                if (checkexist(array,0,i)){scorePlayer+=500;}
            }}


    // La différence entre les scores des joueurs est l'évaluation
    return scorePlayer - scoreOpponent;
}


