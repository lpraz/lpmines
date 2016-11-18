/*
 *  intops.h
 *  Defines abstract functions and constants related to math with
 *  integers, mainly used in rendering of the playfield.
 */

#ifndef INTOPS_H
#define INTOPS_H

/* Gives digits in an integer. */
int numlength(int num);

/* Finds the nth digit (starting at ones) of an int. */
int digitat(int num, int pos);

/* Calculates a power. */
int powint(int base, int exp);

#endif
