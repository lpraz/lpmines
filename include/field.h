/*
 * field.h
 * Defines abstract functions related to the playfield.
 */

#ifndef FIELD_H
#define FIELD_H

/* Local imports */
#include "cell.h"
#include "const.h"

/* Stdlib imports */
#include <stdbool.h>

/* Constants - colours */
#define COL_NUM_COLOR "\033[0;93m"
#define ROW_NUM_COLOR "\033[0;93m"
#define HIDDEN_COLOR "\033[0m"
#define EMPTY_COLOR "\033[0m"
#define FLAG_COLOR "\033[0;91m"
#define MINE_COLOR "\033[41;37m"

#define ONE_COLOR "\033[0;34m"
#define TWO_COLOR "\033[0;32m"
#define THREE_COLOR "\033[0;31m"
#define FOUR_COLOR "\033[0;33m"
#define FIVE_COLOR "\033[0;94m"
#define SIX_COLOR "\033[0;92m"
#define SEVEN_COLOR "\033[0;91m"
#define EIGHT_COLOR "\033[0;93m"

/* Randomly generates a playfield. */
void generate(int sizex, int sizey, int mines, cell **playfield);

/* Draws the playfield to the terminal. */
void drawfield(int sizex, int sizey, bool color, cell **playfield);

/* Draws column numbers (written vertically) for the playfield. */
void drawcolnums(int sizex, int sizey);

/* Checks if the field has been completely swept. */
int finished(int sizex, int sizey, cell **playfield);

#endif
