#define _BSD_SOURCE

#include <ncurses.h>
#include <unistd.h>
#include "../inc/entity.h"
#include "../inc/io.h"
#include "../inc/globals.h"
#include "../inc/space.h"

int main()
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(0);

    mvprintw(HEIGHT + 1, 0, "Press any key to exit...");
    
    struct entity *invader1 = newEntity(1, 1, 1, '#');
    struct entity *invader2 = newEntity(5, 2, 1, '~');
    setupSpace();
    addEntity(getSpace(), invader1);
    addEntity(getSpace(), invader2);

    int ch;

    while (true)
    {
        ch = getch();
        
        if (ch == KEY_ESC)
        {
            break;
        }
        else if (ch == KEY_MOVE_UP)
        {
            moveEntity(invader1, 0, -1);
        }
        else if (ch == KEY_MOVE_DOWN)
        {
            moveEntity(invader1, 0, 1);
        }
        else if (ch == KEY_MOVE_RIGHT)
        {
            moveEntity(invader1, 1, 0);
        }
        else if (ch == KEY_MOVE_LEFT)
        {
            moveEntity(invader1, -1, 0);
        }

        drawSpace(getSpace());
        usleep(100000);
    }

    endwin();
    return 0;
}
