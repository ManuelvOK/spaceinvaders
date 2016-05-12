#ifndef IO_H
#define IO_H

#include "board.h"

/* Sets up curses stuff. */
void initCurses();

/* Restores the default terminal. */
void endCurses();

/* Draws the board on screen. */
void brdDraw(struct board *this);

#endif // IO_H
