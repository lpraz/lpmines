/*
 * action.h
 * Defines abstract functions related to the player's manipulation of
 * the playfield during a game.
 */

#ifndef ACTION_H
#define ACTION_H

/* Local imports */
#include "cell.h"

/* Stdlib imports */
#include <stdbool.h>

/* Performs an in-game action based on a command. */
void parsemove(int x, int y, char action, int sizex, int sizey, int mines,
               int *flags, bool *generated, cell **playfield);

/* Checks if a cell on the field is diggable. If so, digs it. */
void dig(int x, int y, int sizex, int sizey, cell **playfield);

/* Digs a cell, and if it is empty, digs all those around it until it
 * reaches the edge of the playfield or a non-empty cell.
 */
void digrec(int x, int y, int sizex, int sizey, cell **playfield);

/* Checks if a cell on the field can have a flag placed on it. If so
 * places it. */
void pflag(int x, int y, int *flags, cell **playfield);

/* Checks if a cell on the field can have a flag removed from it. If
 * so, removes it. */
void rflag(int x, int y, int *flags, cell **playfield);

#endif
