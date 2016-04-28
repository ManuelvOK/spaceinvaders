#include <stdlib.h>
#include "../inc/datastructures.h"

struct entity * newEntity(int xPos, int yPos, int health, int symbol)
{
    struct entity *newEntity = malloc(sizeof(struct entity));
    if (newEntity == NULL)
        exit(EXIT_FAILURE);

    struct coord pos = { xPos, yPos };

    newEntity->pos = pos;
    newEntity->health = health;
    newEntity->symbol = symbol;

    return newEntity;
}

