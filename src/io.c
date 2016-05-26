#include "../inc/board.h"
#include "../inc/entity.h"
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

char getChar(char monster_state, struct entity ent)
{
    switch (ent.type)
    {
        case ETYPE_EMPTY: return ' ';
        case ETYPE_MONSTER:
            if (monster_state) return 'W';
            else return 'M';
        case ETYPE_PLAYER: return 'A';
        case ETYPE_LASER: return '|';
    }
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

        // iterate through columns and create the string for this row
        for (x = 0; x < this->width; x++)
            str[x] = getChar(this->monster_state, row[x]);

        // print string
        mvaddstr(y + this->yoffset, this->xoffset, str);
    }
}
