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

void brdDraw(struct board *this)
{
    int x, y;
    struct entity *row;
    char str[this->width + 1];

    str[this->width] = '\0';

    // iterate through all rows
    for (y = 0; y < this->height; y++)
    {
        row = brdGetRow(this, y);

        // iterate through columns an create the string for this row
        for (x = 0; x < this->width; x++)
            str[x] = entGetSymbol(row[x]);

        // print string
        mvaddstr(y, 0, str);
    }
}
