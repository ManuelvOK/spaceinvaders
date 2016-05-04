#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/entity.h"
#include "../inc/io.h"
#include "../inc/globals.h"

// Ends ncurses and makes the program terminate
void terminate()
{
    endwin();
    exit(EXIT_FAILURE);
}

// Sets up ncurses and shows misc. visual content.
void startVisuals()
{ 
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    timeout(0);

    mvprintw(HEIGHT + 1, 0, "Controls: WASD - move around");
    mvprintw(HEIGHT + 2, 0, "Press ESC to exit");
}

// Makes ncurses terminate.
void stopVisuals()
{
    endwin();
}

// Prints the contents of the space on the screen.
void drawSpace(struct space *space)
{
    if (space == NULL)
    {
        exit(EXIT_FAILURE);
    }

    struct pos currentPos;

    for (unsigned y = 0; y < space->height; y++)
    {
        currentPos.y = y;

        for (unsigned x = 0; x < space->width; x++)
        {
            currentPos.x = x;

            if (getEntity(getSpace(), currentPos).health == 0)
            {
                mvprintw(y, x*2, "_|");
            }
            else
            {
                mvprintw(y, x*2, "%c|", getEntity(getSpace(), currentPos).symbol);
            }
        }
    }
}

// Reads possible keyboard input and returns whether ESC was pressed.
bool handleInput()
{
    int ch = getch();

    if (ch == KEY_ESC)
    {
        return false;
    }
    else if (ch == KEY_MOVE_UP)
    {
        moveEntity(getPlayer(), getPos(0, -1));
    }
    else if (ch == KEY_MOVE_DOWN)
    {
        moveEntity(getPlayer(), getPos(0, 1));
    }
    else if (ch == KEY_MOVE_LEFT)
    {
        moveEntity(getPlayer(), getPos(-1, 0));
    }
    else if (ch == KEY_MOVE_RIGHT)
    {
        moveEntity(getPlayer(), getPos(1, 0));
    }

    return true;
}
