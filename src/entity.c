#include <stdlib.h>
#include "../inc/entity.h"
#include "../inc/space.h"

struct entity *newEntity(int xPos, int yPos, int health, int symbol)
{
    struct entity *newEntity = malloc(sizeof(struct entity));
    if (newEntity == NULL)
    {
        exit(EXIT_FAILURE);
    }

    struct coord pos = { xPos, yPos };

    newEntity->pos = pos;
    newEntity->health = health;
    newEntity->symbol = symbol;

    return newEntity;
}

void move(struct entity *entity, int deltaX, int deltaY)
{
    if (entity == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int x = entity->pos.x;
    int y = entity->pos.y;

    if (getSpaceElement(getSpace(), x + deltaX, y + deltaY) == NULL)
    {
        setSpaceElement(getSpace(), x, y, NULL);
        setSpaceElement(getSpace(), x + deltaX, y + deltaY, entity);
    }
}
