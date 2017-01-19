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
