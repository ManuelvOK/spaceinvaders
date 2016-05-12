#include "../inc/board.h"
#include "../inc/io.h"

#include <curses.h>

void initCurses()
{
    initscr();
}

void endCurses()
{
    endwin();
}
