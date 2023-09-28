/**
 * @file IA.c
 * @brief AI Implementation
 * @author Group 5
 * @date 2023-09-22
 */
#include <stdio.h>
#include <limits.h>
#include "IA.h"



// Fonction récursive minimax avec élagage alpha-bêta
/**
 * @brief Minimax function with alpha-beta pruning.
 *
 * This function implements the minimax algorithm with alpha-beta pruning to determine the best move.
 *
 * @param board The game board.
 * @param depth The depth of the search tree.
 * @param isMaximizingPlayer Indicates if it's the maximizing player's turn.
 * @param alpha The alpha value for alpha-beta pruning.
 * @param beta The beta value for alpha-beta pruning.
 * @param player The current player's color (BLUE or RED).
 * @return The best value determined by the minimax algorithm.
 */
int minimax(char board[SIZE][SIZE], int depth, int isMaximizingPlayer, int alpha, int beta, char plyer) {
    if (depth == 0|| CheckVictory(BLUE,board)||CheckVictory(RED,board)) {
        return evaluateBoard(board, plyer);
    }

    int bestValue;
    if (isMaximizingPlayer) {
        bestValue = INT_MIN;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Si la case (i, j) est vide, essayez ce coup
                if (board[i][j] == EMPTY) {
                    board[i][j] = plyer;  // Supposons que l'IA est 'X'
                    int value = minimax(board, depth - 1, 0, alpha, beta,plyer);
                    board[i][j] = EMPTY;  // Annulez le coup
                    bestValue = (value > bestValue) ? value : bestValue;
                    alpha = (alpha > bestValue) ? alpha : bestValue;
                    if (beta <= alpha) {
                        break;  // Élagage alpha-bêta
                    }
                }
            }
        }
    } else {
        bestValue = INT_MAX;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Si la case (i, j) est vide, essayez ce coup
                if (board[i][j] == EMPTY) {
                    board[i][j] =(plyer==BLUE)?RED : BLUE; // Supposons que l'adversaire est 'O'
                    int value = minimax(board, depth - 1, 1, alpha, beta,plyer);
                    board[i][j] = EMPTY;  // Annulez le coup
                    bestValue = (value < bestValue) ? value : bestValue;
                    beta = (beta < bestValue) ? beta : bestValue;
                    if (beta <= alpha) {
                        break;  // Élagage alpha-bêta
                    }
                }
            }
        }
    }
    return bestValue;
}

// Fonction pour obtenir le meilleur coup pour l'IA
/**
 * @brief Get the best move for the AI player.
 *
 * This function calculates the best move for the AI player using the minimax algorithm.
 *
 * @param board The game board.
 * @param turn The current turn.
 * @param player The player's color (BLUE or RED).
 * @return The best move determined by the AI.
 */
Move getBestMove(char board[SIZE][SIZE],int turn,char player) {
    int bestValue = -INT_MAX;
    Move bestMove;
    int depth= MAX_DEPTH;
    bestMove.row = -1;
    bestMove.col = -1;
    if (turn >=30){depth--;}
    if (turn > 34){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY){
                    bestMove.row = i;
                    bestMove.col = j;
                 return bestMove;
            
            }
        }    
    }
    
    }
    if (turn==0){bestMove.row = 3;
                    bestMove.col = 1;
                 return bestMove;}
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //printf("%d%d\n", i, j );
            
            // Si la case (i, j) est vide, essayez ce coup
            if (board[i][j] == EMPTY) {
                board[i][j] = player;  // Supposons que l'IA est 'X'
                if (CheckVictory(player,board)){bestMove.row = i;
                    bestMove.col = j;
                 return bestMove;}
                int moveValue = minimax(board, depth, 0, INT_MIN, INT_MAX, player);
                board[i][j] = EMPTY;  // Annulez le coup

                if (moveValue > bestValue) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestValue = moveValue;
                }
            }
        }
    }
    if( bestMove.row ==-1|| bestMove.col==-1){
        for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY){
                    bestMove.row = i;
                    bestMove.col = j;
                 return bestMove;
            }}}}
    return bestMove;
}


/**
 * @brief AI's implementation of player vs. computer gameplay.
 *
 * This function handles the player vs. computer gameplay, where the AI makes decisions for the computer.
 *
 * @param color The player's chosen color (BLUE or RED).
 */
void playervcomputer(char color){
    initialization();
        int cond=0;// this a cond to know if the turn ends
	    char player = BLUE;//to know whose turn it is
	
	
	int turn = 0;
	while (turn < 38){
	
    int c;
	int l;//coord c too
    
    
    if(turn ==0 && color!=player){
    Move bestMove = getBestMove(board, turn, player);
    printf("%c%d\n", 'A' + bestMove.col, bestMove.row + 1);
    c = bestMove.row ;
    l = bestMove.col;
    
    printf("Bot played %d %d", c, l);}

	
	
	
    
    
    while (cond==0){
	
    printf("player %c where do you play ?\n", player);
    if(color==player){
    char pos[3];
	scanf("%s", pos); 
    if(strlen(pos)!=2){while(strlen(pos) != 2){printf("Bad instruction \n Please enter a letter between A and E and a digit between 1 and 6 : \n");scanf("%s", pos);}}
    convertirPosition(pos, &c, &l);}
    else {
    Move bestMove = getBestMove(board, turn, player);
    printf("%c%d\n", 'A' + bestMove.col, bestMove.row + 1);
    c = bestMove.row ;
    l = bestMove.col;
    
    printf("Bot played %d %d", c, l);
    }

	if(board[c][l]==EMPTY){cond=1; board[c][l]=player; printf("well play\n\n"); displayBoard();


	
	
	}
	else {printf("you can't play there!");}

	}
    if (CheckVictory(player, board)){printf("Victory player %c, you're so strong dude !", player);break;}



cond=0; if (player==BLUE){player= RED;} else{player=BLUE;} turn++;
}


 
 printf("end of the game");

 
 
 
 }
 

/**
 * @brief AI's implementation of computer vs. computer gameplay.
 *
 * This function handles computer vs. computer gameplay, where both sides are controlled by the AI.
 */
void computervcomputer(){
    initialization();
        int cond=0;// this a cond to know if the turn ends
	    char player = BLUE;//to know whose turn it is
	
	
	int turn = 0;
	while (turn < 36){
	

	printf("player %c where do you play ?\n", player);
	int c;
	int l;//coord c too
	while (cond==0){
	printf("Tour n°%d\n", turn);
    Move bestMove = getBestMove(board, turn, player);
    printf("%c%d\n", 'A' + bestMove.col, bestMove.row + 1);
    c = bestMove.row;
    l = bestMove.col ;
    
    
    
    
    printf("Bot %c played %d %d", player, c, l);
    

	if(board[c][l]==EMPTY){cond=1; board[c][l]=player; printf("well play\n\n"); displayBoard();
    sleep(1);

	
	
	}
	else {printf("you can't play there!");}
	}


if (CheckVictory(player, board)){printf("Victory player %c, you're so strong dude !", player);break;}

cond=0; if (player==BLUE){player= RED;} else{player=BLUE;} turn++;
}


 printf("end of the game");
 
 }
