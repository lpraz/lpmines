/*
 * field.c
 * Provides functions related to the playfield.
 */

/* Import self */
#include "field.h"

/* Local imports */
#include "const.h"
#include "intops.h"

/* Stdlib imports */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Randomly generates a playfield. */
void generate(int sizex, int sizey, int mines,
              int (*ground)[MAX_HEIGHT][MAX_WIDTH],
              int (*surface)[MAX_HEIGHT][MAX_WIDTH]) {
    int randx, randy;
    
    /* Set RNG seed */
    srand(time(0));
    
    /* Make a clean playfield */
    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            (*ground)[i][j] = EMPTY;
            if (i < sizey && j < sizex)
                (*surface)[i][j] = HIDDEN;
            else
                (*surface)[i][j] = REVEALED;
        }
    }
    
    /* Place mines and "how many mines near?" numbers */
    while (mines > 0) {
        randx = rand() % sizex;
        randy = rand() % sizey;
        
        printf("Mine at %d %d\n", randx, randy);
        if ((*ground)[randy][randx] != HAS_MINE) {
            (*ground)[randy][randx] = HAS_MINE;
            for (int i = (((randy - 1) > 0) ? (randy - 1) : 0);
                 i < (((randy + 1) >= sizey) ? sizey : (randy + 2));
                 i++) {
                for (int j = (((randx - 1) > 0) ? (randx - 1) : 0);
                     j < (((randx + 1) >= sizex) ? sizex : (randx + 2));
                     j++) {
                    if ((*ground)[i][j] == EMPTY)
                        (*ground)[i][j] = 1;
                    else if ((*ground)[i][j] != HAS_MINE)
                        (*ground)[i][j]++;;
                }
            }
            mines--;
        }
    }
}

/* Draws the playfield to the terminal. */
void drawfield(int sizex, int sizey, bool color,
               int ground[MAX_HEIGHT][MAX_WIDTH],
               int surface[MAX_HEIGHT][MAX_WIDTH]) {
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
            switch(surface[i][j]) {
                case HIDDEN:
                    if (color) printf(HIDDEN_COLOR);
                    printf(" .");
                    break;
                case REVEALED:
                    switch(ground[i][j]) {
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
                            printf(" %d", ground[i][j]);
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
int finished(int sizex, int sizey,
             int ground[MAX_HEIGHT][MAX_WIDTH],
             int surface[MAX_HEIGHT][MAX_WIDTH]) {
    /* Check for exposed mines */
    for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            if (ground[i][j] == HAS_MINE && surface[i][j] == REVEALED)
                return RESULT_EXPLODED;
        }
    }
    
    /* Check if revealed everything */
    for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            if (surface[i][j] != REVEALED && ground[i][j] != HAS_MINE)
                return NOT_FINISHED;
        }
    }
    
    return RESULT_CLEARED;
}
