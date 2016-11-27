/*
 * field.c
 * Provides functions related to the playfield.
 */

/* Import self */
#include "field.h"

/* Local imports */
#include "cell.h"
#include "const.h"
#include "intops.h"

/* Stdlib imports */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Randomly generates a playfield. */
void generate(int sizex, int sizey, int mines, cell **playfield) {
    int randx, randy;
    
    /* Set RNG seed */
    srand(time(0));
    
    /* Make a clean playfield */
    for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            playfield[i][j].ground = EMPTY;
            playfield[i][j].surface = HIDDEN;
        }
    }
    
    /* Place mines and "how many mines near?" numbers */
    while (mines > 0) {
        randx = rand() % sizex;
        randy = rand() % sizey;
        
        if (playfield[randy][randx].ground != HAS_MINE) {
            playfield[randy][randx].ground = HAS_MINE;
            for (int i = (((randy - 1) > 0) ? (randy - 1) : 0);
                 i < (((randy + 1) >= sizey) ? sizey : (randy + 2));
                 i++) {
                for (int j = (((randx - 1) > 0) ? (randx - 1) : 0);
                     j < (((randx + 1) >= sizex) ? sizex : (randx + 2));
                     j++) {
                    if (playfield[i][j].ground == EMPTY)
                        playfield[i][j].ground = 1;
                    else if (playfield[i][j].ground != HAS_MINE)
                        playfield[i][j].ground++;;
                }
            }
            mines--;
        }
    }
}

/* Draws the playfield to the terminal. */
void drawfield(int sizex, int sizey, bool color, cell **playfield) {
    /* Print column numbers */
    if (color) printf(COL_NUM_COLOR);
    drawcolnums(sizex, sizey);

    for (int i = 0; i < sizey; i++) {
        /* Print row numbers */
        if (color)
            printf(ROW_NUM_COLOR);
        printf("%*d ", numlength(sizey), i + 1);
        
        for (int j = 0; j < sizex; j++) {
            /* Print contents of each cell */
            switch(playfield[i][j].surface) {
                case HIDDEN:
                    if (color) printf(HIDDEN_COLOR);
                    printf(" .");
                    break;
                case REVEALED:
                    switch(playfield[i][j].ground) {
                        case EMPTY:
                            if (color) printf(EMPTY_COLOR);
                            printf(" _");
                            break;
                        case HAS_MINE:
                            if (color) printf(EMPTY_COLOR);
                            printf(" ");
                            if (color) printf(MINE_COLOR);
                            printf("X");
                            break;
                        case 1:
                            if (color) printf(ONE_COLOR);
                            printf(" 1");
                            break;
                        case 2:
                            if (color) printf(TWO_COLOR);
                            printf(" 2");
                            break;
                        case 3:
                            if (color) printf(THREE_COLOR);
                            printf(" 3");
                            break;
                        case 4:
                            if (color) printf(FOUR_COLOR);
                            printf(" 4");
                            break;
                        case 5:
                            if (color) printf(FIVE_COLOR);
                            printf(" 5");
                            break;
                        case 6:
                            if (color) printf(SIX_COLOR);
                            printf(" 6");
                            break;
                        case 7:
                            if (color) printf(SEVEN_COLOR);
                            printf(" 7");
                            break;
                        case 8:
                            if (color) printf(EIGHT_COLOR);
                            printf(" 8");
                            break;
                        default:
                            printf(" %d", playfield[i][j].ground);
                            break;
                    }
                    break;
                case FLAGGED:
                    if (color) printf(FLAG_COLOR);
                    printf(" F");
                    break;
                default:
                    printf(" ?");
                    break;
            }
        }
        printf("\n");
    }    
}

/* Draws column numbers (written vertically) for the playfield. */
void drawcolnums(int sizex, int sizey) {
    int curdigit;

    for (int i = numlength(sizex); i > 0; i--) {
        printf("%*s ", numlength(sizey), " ");
        for (int j = 0; j < sizex; j++) {
            curdigit = digitat(j + 1, i);
            if (curdigit == 0 && j + 1 < powint(BASE, i - 1))
                printf("  ");
            else
                printf(" %d", curdigit);
        }
        printf("\n");
    }
}

/* Checks if the field has been completely swept, or if a mine has been
 * revealed.
 */
int finished(int sizex, int sizey, cell **playfield) {
    /* Check for exposed mines */
    for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            if (playfield[i][j].ground == HAS_MINE
                    && playfield[i][j].surface == REVEALED)
                return RESULT_EXPLODED;
        }
    }
    
    /* Check if revealed everything */
    for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            if (playfield[i][j].surface != REVEALED
                    && playfield[i][j].ground != HAS_MINE)
                return NOT_FINISHED;
        }
    }
    
    return RESULT_CLEARED;
}
