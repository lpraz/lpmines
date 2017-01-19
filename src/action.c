/*
 * action.c
 * Provides functions related to manipulation of the playfield by the
 * player in a game.
 */

/* Import self */
#include "action.h"

/* Local imports */
#include "cell.h"
#include "const.h"

/* Stdlib imports */
#include <stdio.h>

/* Performs an in-game action based on a command. */
void parsemove(int x, int y, char action, int sizex, int sizey,
               int *flags, cell **playfield) {
    /* Check if cell location is valid */
    if (x >= sizex || x < 0 || y > sizey || y < 0) {
        printf("That isn't a valid cell!\n");
        return;
    }
    
    /* Perform the action */
    switch(action) {
        case 'd': /* Dig */
            dig(x, y, sizex, sizey, playfield);
            break;
        case 'p': /* Place flag */
        case 'f':
            pflag(x, y, flags, playfield);
            break;
        case 'r': /* Remove flag */
            rflag(x, y, flags, playfield);
            break;
        default: /* Anything else */
            printf("That isn't a valid action!\n");
            break;
    }
}

/* Checks if a cell on the field is diggable. If so, digs it. */
void dig(int x, int y, int sizex, int sizey, cell **playfield) {
    if (playfield[y][x].surface == HIDDEN) {
        printf("Dug at (%d, %d).\n", x + 1, y + 1);
        digrec(x, y, sizex, sizey, playfield);
    } else if (playfield[y][x].surface == REVEALED) {
        printf("(%d, %d) is already exposed!\n", x + 1, y + 1);
    } else if (playfield[y][x].surface == FLAGGED) {
        printf("(%d, %d) is flagged!\n", x + 1, y + 1);
    }
}

/* Digs a cell, and if it is empty, digs all those around it until it
 * reaches the edge of the playfield or a non-empty cell.
 */
void digrec(int x, int y, int sizex, int sizey, cell **playfield) {
    playfield[y][x].surface = REVEALED;
    
    if (playfield[y][x].ground == EMPTY)
        for (int i = (((y - 1) < 0) ? 0 : (y - 1));
             i < (((y + 1) >= sizey) ? sizey : (y + 2));
             i++)
            for (int j = (((x - 1) < 0) ? 0 : (x - 1));
                 j < (((x + 1) >= sizex) ? sizex : (x + 2));
                 j++)
                if (playfield[i][j].surface == HIDDEN)
                    digrec(j, i, sizex, sizey, playfield);

}

/* Checks if a cell on the field can have a flag placed on it. If so
 * places it. */
void pflag(int x, int y, int *flags, cell **playfield) {
    if (playfield[y][x].surface == HIDDEN) {
        printf("Placed a flag at (%d, %d).\n", x + 1, y + 1);
        playfield[y][x].surface = FLAGGED;
        (*flags)++;
    } else if (playfield[y][x].surface == FLAGGED) {
        printf("(%d, %d) already has a flag!\n", x + 1, y + 1);
    } else if (playfield[y][x].surface == REVEALED) {
        printf("(%d, %d) is exposed!\n", x + 1, y + 1);
    }
}

/* Checks if a cell on the field can have a flag removed from it. If
 * so, removes it. */
void rflag(int x, int y, int *flags, cell **playfield) {
    if (playfield[y][x].surface == FLAGGED) {
        printf("Removed flag at (%d, %d).\n", x + 1, y + 1);
        playfield[y][x].surface = HIDDEN;
        (*flags)--;
    } else if (playfield[y][x].surface == HIDDEN) {
        printf("(%d, %d) has no flag!\n", x + 1, y + 1);
    } else if (playfield[y][x].surface == REVEALED) {
        printf("(%d, %d) is exposed!\n", x + 1, y + 1);
    }
}
