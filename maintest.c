/**
 * @file maintest.c
 * @brief Implementation of unit tests for the game logic.
 *
 * This file contains the implementation of unit tests for the game logic
 * using the CheckVictory function. It defines multiple test cases to check
 * the victory conditions of the game.
 */

#include "Jeu.h"
#include <stdio.h>


/**
 * @brief Runs a test function and tracks test results.
 *
 * This function runs a test function and tracks the number of test failures
 * and the total number of test runs.
 *
 * @param f          The test function to run.
 * @param failures   Pointer to the total number of test failures.
 * @param runs       Pointer to the total number of test runs.
 */
void run_test(int (*f)(), int *failures, int *runs) { 
if (!f()) (*failures)++;
(*runs)++;
}

/**
 * @brief Test case for victory on an empty board.
 *
 * This test case checks if the CheckVictory function correctly identifies
 * that there is no victory on an empty game board.
 *
 * @return 1 if the test passes, 0 if it fails.
 */
int testVictoryEmptyBoard(){
char test[SIZE][SIZE] = {
        {'O','O','O','O','O','O'},
        {'O','O','O','O','O','O'},
        {'O','O','O','O','O','O'},
        {'O','O','O','O','O','O'},
        {'O','O','O','O','O','O'},
        {'O','O','O','O','O','O'},
    
    };

    return (CheckVictory(RED, test) == 0 && CheckVictory(BLUE, test) == 0);


}


/**
 * @brief Test case for a red victory.
 *
 * This test case checks if the CheckVictory function correctly identifies
 * a victory for the red player on the game board.
 *
 * @return 1 if the test passes, 0 if it fails.
 */
int testRedVictory(){
char test[SIZE][SIZE] = {
        {'R','O','O','O','O','O'},
        {'O','R','O','O','O','O'},
        {'O','O','R','O','O','O'},
        {'R','R','O','R','O','O'},
        {'O','O','R','O','R','O'},
        {'O','O','O','R','O','O'},
    
    };

    return (CheckVictory(RED, test) == 1 && CheckVictory(BLUE, test) == 0);


}

/**
 * @brief Test case for a blue victory.
 *
 * This test case checks if the CheckVictory function correctly identifies
 * a victory for the blue player on the game board.
 *
 * @return 1 if the test passes, 0 if it fails.
 */
int testBlueVictory(){
char test[SIZE][SIZE] = {
        {'O','O','O','O','O','O'},
        {'O','B','O','O','O','O'},
        {'B','O','B','O','O','O'},
        {'O','B','O','B','O','B'},
        {'O','O','B','O','B','O'},
        {'O','O','O','O','O','O'},
    
    };

    return (CheckVictory(RED, test) == 0 && CheckVictory(BLUE, test) == 1);


}

/**
 * @brief Test case for a blue diagonal victory.
 *
 * This test case checks if the CheckVictory function correctly identifies
 * a diagonal victory for the blue player on the game board.
 *
 * @return 1 if the test passes, 0 if it fails.
 */
int testBlueDiagVictory(){
char test[SIZE][SIZE] = {
        {'B','O','B','O','B','O'},
        {'O','B','O','B','O','O'},
        {'O','O','B','O','O','O'},
        {'O','O','O','B','O','O'},
        {'O','O','O','O','B','O'},
        {'O','O','O','O','O','B'},
    
    };

    return (CheckVictory(RED, test) == 0 && CheckVictory(BLUE, test) == 1);


}

/**
 * @brief Test case for a blue diagonal victory.
 *
 * This test case checks if the CheckVictory function correctly identifies
 * a diagonal victory for the blue player on the game board.
 *
 * @return 1 if the test passes, 0 if it fails.
 */
int testRedDiagVictory(){
 char test[SIZE][SIZE] = {
        {'R','O','B','O','B','O'},
        {'O','R','O','B','O','O'},
        {'O','O','R','O','O','O'},
        {'O','O','O','R','O','O'},
        {'O','O','O','O','R','O'},
        {'O','O','O','O','O','R'},
    
    };

    return (CheckVictory(RED, test) == 1 && CheckVictory(BLUE, test) == 0);


}

/**
 * @brief Test case for a double victory.
 *
 * This test case checks if the CheckVictory function correctly identifies
 * a double victory for both the red and blue players on the game board.
 *
 * @return 1 if the test passes, 0 if it fails.
 */
int testDoubleVictory(){
    char test[SIZE][SIZE] = {
        {'R','B','B','B','B','B'},
        {'B','R','B','B','B','O'},
        {'O','O','R','O','O','O'},
        {'O','O','O','R','O','O'},
        {'O','O','O','O','R','O'},
        {'O','O','O','O','O','R'},
    
    };


    return (CheckVictory(RED, test) == 1 && CheckVictory(BLUE, test) == 1);


}

/**
 * @brief Test case for an external victory.
 *
 * This test case checks if the CheckVictory function correctly identifies
 * no victory for both the red and blue players on the game board.
 *
 * @return 1 if the test passes, 0 if it fails.
 */
int testExternVictory(){
    char test[SIZE][SIZE] = {
        {'B','O','O','O','O','O'},
        {'R','O','O','O','O','B'},
        {'O','O','O','O','O','O'},
        {'O','O','O','O','O','O'},
        {'O','O','O','O','O','O'},
        {'O','O','O','O','O','O'},
    
    };


    return (CheckVictory(RED, test) == 0 && CheckVictory(BLUE, test) == 0);


}

/**
 * @brief Main function for running unit tests.
 *
 * This function runs a series of unit tests for the game logic and prints
 * the number of test failures and the total number of tests run.
 *
 * @return The number of test failures.
 */
int main(){
    int test_count = 0, failures = 0;

    
    run_test(testVictoryEmptyBoard, &failures, &test_count);
    run_test(testBlueVictory, &failures, &test_count);
    run_test(testRedVictory, &failures, &test_count);
    run_test(testBlueDiagVictory, &failures, &test_count);
    run_test(testRedDiagVictory, &failures, &test_count);
    run_test(testDoubleVictory, &failures, &test_count);
    run_test(testExternVictory, &failures, &test_count);
    printf("%d failures out of %d tests\n", failures, test_count);

return failures;


}
