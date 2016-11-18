/*
 *  const.h
 *  Provides constants used by various methods in the program.
 */

#ifndef CONST_H
#define CONST_H

/* What base number system are we using? */
#define BASE 10

/* Cell surface state */
#define HIDDEN 1
#define REVEALED 2
#define FLAGGED 3

/* Cell ground state */
#define EMPTY -2
#define HAS_MINE -1

/* Field params by difficulty */
#define BEGINNER_WIDTH 10
#define BEGINNER_HEIGHT 10
#define BEGINNER_MINES 10
#define INTERMEDIATE_WIDTH 20
#define INTERMEDIATE_HEIGHT 20
#define INTERMEDIATE_MINES 40
#define EXPERT_WIDTH 30
#define EXPERT_HEIGHT 20
#define EXPERT_MINES 90
#define MAX_CUSTOM_WIDTH 30
#define MAX_CUSTOM_HEIGHT 20
#define MAX_CUSTOM_MINES 150

/* Input vals */
#define INPUT_LENGTH 10
#define NO_INPUT_FLAG -1
#define COMMAND_TOKENS ".,;:"

/* Pretty colors! */
#define COL_NUM_COLOR "\033[40,93m"
#define ROW_NUM_COLOR "\033[40,93m"
#define HIDDEN_COLOR "\033[0m"
#define FLAG_COLOR "\033[40,91m"
#define MINE_COLOR "\033[41,37m"

#define ONE_COLOR "\033[40,34m"
#define TWO_COLOR "\033[40,32m"
#define THREE_COLOR "\033[40,31m"
#define FOUR_COLOR "\033[40,33m"
#define FIVE_COLOR "\033[40,94m"
#define SIX_COLOR "\033[40,92m"
#define SEVEN_COLOR "\033[40,91m"
#define EIGHT_COLOR "\033[40,93m"

/* Results */
#define NOT_FINISHED 0
#define RESULT_EXPLODED 2
#define RESULT_CLEARED 1

#endif
