# lpmines

It's Minesweeper, written in C for your terminal. What else could you
ask for?

## Features
 * Three levels of difficulty, or make your own custom difficulty!
 * Colour graphics on aixterm-compatible terminals!

## Building and (Un)Installing
 * Installing: On Linux systems, just `git clone` this repository, then
    `make`, then (`sudo`) `make install`. Your binary will be installed to 
    `/usr/games/lpmines` by default. If you don't like this, just change
    the `PREFIX` and `INSTTARGET` variables in the makefile.
 * Uninstalling: Just (`sudo`) `make uninstall`.
