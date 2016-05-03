#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/io.h"

// Ends ncurses and makes the program terminate
void terminate()
{
    endwin();
    exit(EXIT_FAILURE);
}

// Prints the contents of the space on the screen.
void drawSpace(struct space *space)
{
    if (space == NULL)
    {
        exit(EXIT_FAILURE);
    }

    struct entity *currentPtr;

    for (unsigned y = 0; y < space->height; y++)
    {
        for (unsigned x = 0; x < space->width; x++)
        {
            currentPtr = getSpaceElement(space, x, y);
            if (currentPtr == NULL)
            {
                mvprintw(y, x*2, "_|");
            }
            else
            {
                mvprintw(y, x*2, "%c|", currentPtr->symbol);
            }
        }
    }
}
