#include <stdio.h>
#include <ncurses.h>
#include "../inc/io.h"

void drawEntity(struct entity *entity)
{
    mvprintw(entity->pos.y, entity->pos.x, "%c", entity->symbol);
}

