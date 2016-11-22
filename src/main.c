/*
 * main.c
 * Provides top-level functions for lpmines. In essence, the glue that
 * holds the universe together.
 */

/* Imports for C libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Local imports */
#include "action.h"
#include "const.h"
#include "field.h"
#include "input.h"

/* Main method */
int main(void) {
    /* Board vars */
    int ground[MAX_HEIGHT][MAX_WIDTH];
    int surface[MAX_HEIGHT][MAX_WIDTH];
    int sizex, sizey, mines;
    
    /* Input vars */
    char in[INPUT_LENGTH];
    int x, y;
    char action;

    int result;
    
    /* Intro menu; get difficulty */
    menu(&sizex, &sizey, &mines);
    
    /* Generate the playfield */
    generate(sizex, sizey, mines, &ground, &surface);
    
    /* Game loop */
    while (result = finished(sizex, sizey, ground, surface), !result) {
        /* Print field */
        drawfield(sizex, sizey, ground, surface);
        
        /* Get input */
        printf("It's your move: ");
        scanf("%s", in);
        
        /* Clear screen */
        printf("\033[2J\033[H");
        
        /* Use input */
        split(in, &x, &y, &action);
        parsemove(x, y, action, sizex, sizey, &ground, &surface);
    }
    
    /* Show result */
    drawfield(sizex, sizey, ground, surface);
    
    if (result == RESULT_CLEARED)
        printf("You cleared all the mines! Congratulations!\n");
    else if (result == RESULT_EXPLODED)
        printf("You uncovered a mine. Better luck next time...\n");
    
    return 0;
} 
