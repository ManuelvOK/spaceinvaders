#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/behavior.h"
#include "../inc/entity.h"
#include "../inc/io.h"
#include "../inc/globals.h"

// Ends ncurses and makes the program terminate.
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

    mvprintw(HEIGHT + 1, 0, "Controls: A - move left, D - move right, SPACEBAR - shoot");
    mvprintw(HEIGHT + 2, 0, "Press ESC to exit");
    
    refresh();
}

// Makes ncurses terminate.
void stopVisuals()
{
    endwin();
}

// Prints the outline of a space.
void drawSpaceOutline(struct space *space)
{
    if (space == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (unsigned char y = 0; y < space->height; y++)
    {
        for (unsigned char x = 0; x < space->width; x++)
        {
            mvprintw(y, x*2 + 1, "|");
        }
    }

    refresh();
}

// Prints the contents of a space on the screen.
void drawSpace(struct space *space)
{
    if (space == NULL)
    {
        exit(EXIT_FAILURE);
    }

    struct pos currentPos;

    for (unsigned char y = 0; y < space->height; y++)
    {
        currentPos.y = y;

        for (unsigned char x = 0; x < space->width; x++)
        {
            currentPos.x = x;

            if (getEntity(getSpace(), currentPos).health == 0)
            {
                mvprintw(y, x*2, "_");
            }
            else
            {
                mvprintw(y, x*2, "%c", getEntity(getSpace(), currentPos).symbol);
            }
        }
    }

    refresh();
}

// Reads possible keyboard input and returns whether KEY_QUIT was pressed.
bool handleInput()
{
    int ch = getch();

    if (ch == KEY_QUIT)
    {
        return false;
    }
    else if (ch == KEY_MOVE_LEFT)
    {
        movePlayer(-1);
    }
    else if (ch == KEY_MOVE_RIGHT)
    {
        movePlayer(1);
    }
    else if (ch == KEY_SHOOT)
    {
        spawnPlayerLaser();
    }

    return true;
}
