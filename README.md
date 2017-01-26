# lpmines
It's Minesweeper, written in C for your terminal. What else could you
ask for?

## Features
 * Three levels of difficulty, or make your own custom difficulty!
 * Colour graphics on aixterm-compatible terminals!

## Building and (Un)Installing
 * Building: On Linux systems, just `git clone` this repository, then
    `make`.
 * Installing: After building, (`sudo`) `make install`. Your binary will be
    installed to `/usr/bin/bfpp` by default. If you don't like this, just
    change the `PREFIX` and `INSTTARGET` variables in the makefile.
 * Uninstalling: Just (`sudo`) `make uninstall`.

## How to Play
Commands in lpmines take the form:

    x;y;a

where `(x, y)` is the location of the cell on the playfield, and `a` is
the action you want to perform. The semicolons used to delimit the
instructions may also be replaced by periods, commas or colons.

A list of possible actions:
 * `d`: Dig a cell. Use this carefully, as if you dig a mine, your game is
    over!
 * `f` or `p`: Place a flag on a cell. Use it to mark a cell that you think
    has a mine on it, as flagged cells can't be dug.
 * `r`: Remove a flag from a cell. Use it when that cell you flagged might
    not have a mine, after all.
