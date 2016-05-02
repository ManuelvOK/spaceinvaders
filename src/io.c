#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/io.h"

void drawEntity(struct entity *entity)
{
    mvprintw(entity->pos.y, entity->pos.x, "%c", entity->symbol);
}

void drawSpace(struct space *space)
{
    if (space == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (int y = 0; y < space->height; y++)
    {
        for (int x = 0; x < space->width; x++)
        {
            mvprintw(y, x * 2, "%1d_", getSpaceElement(space, x, y) == NULL);
        }
    }
}
