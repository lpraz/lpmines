/*
 *  intops.c
 *  Contains functions related to math with integers, mainly used in
 *  rendering of the playfield.
 */

/* Import self */
#include "intops.h"

/* Local imports */
#include "const.h"

/* Gives digits in an integer. */
int numlength(int num) {
    int len;

    for (len = 1; num > BASE - 1; len++)
        num /= BASE;
    
    return len;
}

/* Finds the nth digit (starting at ones) of an int. */
int digitat(int num, int pos) {
    return num / powint(BASE, pos - 1) % BASE;
}

/* Calculates a power recursively. */
int powint(int base, int exp) {
    if (exp == 0)
        return 1;
    else if (exp == 1)
        return base;
    else if (exp % 2 == 0)
        return powint(base * base, exp / 2);
    else /* if (exp % 2 == 1) */
        return powint(base * base, (exp - 1) / 2);
}
