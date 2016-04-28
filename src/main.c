#include <ncurses.h>
#include "../inc/datastructures.h"
#include "../inc/io.h"

int main(void)
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    //timeout(0);

    struct entity *test = newEntity(1, 1, 1, '#');
    drawEntity(test);

    mvprintw(10, 0, "Press any key to exit...");
    getch();

    endwin();
    return 0;
}

