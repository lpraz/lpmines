/*
 * main.c
 * Provides top-level functions for lpmines. In essence, the glue that
 * holds the universe together.
 */

/* Imports for C libraries */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Local imports */
#include "action.h"
#include "cell.h"
#include "const.h"
#include "field.h"
#include "input.h"

/* Main method */
int main(int argc, char *argv[]) {
    /* Board vars */
    cell **playfield;
    int sizex, sizey, mines, flags;
    bool generated = false;
    sizex = sizey = mines = NO_INPUT_FLAG;
    flags = 0;
    
    /* Input vars */
    char in[INPUT_LENGTH];
    int x, y;
    char action;

    int result;
    
    bool color = true;
    
    /* Get command-line arguments, exit if appropriate */
    if (!args(argc, argv, &sizex, &sizey, &mines, &color))
        return 0;
    
    /* Intro menu; get difficulty */
    menu(&sizex, &sizey, &mines);
    
    /* Allocate memory for the playfield */
    playfield = malloc(sizey * sizeof(cell*));
    
    if (playfield == NULL) {
        printf("Memory error when allocating cell column, exiting...");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < sizey; i++) {
        playfield[i] = malloc(sizex * sizeof(cell));
        if (playfield[i] == NULL) {
            printf("Memory error when allocating cell row, exiting...");
            exit(EXIT_FAILURE);
        }
    }
    
    /* Game loop */
    while (result = finished(sizex, sizey, playfield), !result) {
        /* Print field */
        drawfield(sizex, sizey, color, generated, playfield);
        
        /* Get input */
        printf("You placed %d/%d flags. It's your move: ", flags, mines);
        scanf("%s", in);
        
        /* Clear screen */
        printf("\033[2J\033[H");
        
        /* Use input */
        split(in, &x, &y, &action);
        parsemove(x, y, action, sizex, sizey, mines, &flags, &generated,
                  playfield);
    }
    
    /* Show result */
    drawfield(sizex, sizey, color, generated, playfield);
    
    printf(EMPTY_COLOR);
    if (result == RESULT_CLEARED)
        printf("You cleared all the mines! Congratulations!\n");
    else if (result == RESULT_EXPLODED)
        printf("You detonated a mine. Better luck next time...\n");
    
    /* Free up the playfield memory */
    for (int i = 0; i < sizey; i++)
        free(playfield[i]);
    free(playfield);
    
    return EXIT_SUCCESS;
} 
