#include <ncurses.h>
#include "../inc/entity.h"
#include "../inc/io.h"
#include "../inc/space.h"
#include "../inc/globals.h"

int main()
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    //timeout(0);

    //struct entity *test = newEntity(1, 1, 1, '#');
    //drawEntity(test);
    setupSpace();
    drawSpace(getSpace());

    mvprintw(HEIGHT + 1, 0, "Press any key to exit...");
    getch();

    endwin();
    return 0;
}
