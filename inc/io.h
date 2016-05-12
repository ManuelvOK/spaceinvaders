#ifndef IO_H
#define IO_H

#include "board.h"

void initCurses();
void endCurses();

void brdDraw(struct board *this);

#endif // IO_H
