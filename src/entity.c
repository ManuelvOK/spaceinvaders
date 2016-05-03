#include <stdlib.h>
#include "../inc/entity.h"
#include "../inc/io.h"
#include "../inc/space.h"

// Returns a pointer to a new entity on the heap.
struct entity *newEntity(unsigned x, unsigned y, unsigned health, int symbol)
{
    struct entity *newEntity = malloc(sizeof(struct entity));
    
    if (newEntity == NULL)
    {
        terminate();
    }

    newEntity->x = x;
    newEntity->y = y;
    newEntity->health = health;
    newEntity->symbol = symbol;

    return newEntity;
}

// Moves an entity from one position on the global space to another.
void moveEntity(struct entity *entity, int deltaX, int deltaY)
{
    if (entity == NULL)
    {
        terminate();
    }

    unsigned newX = entity->x + deltaX;
    unsigned newY = entity->y + deltaY;

    if (!spaceOutOfBounds(getSpace(), newX, newY))
    {
        if (getSpaceElement(getSpace(), newX, newY) == NULL)
        {
            setSpaceElement(getSpace(), entity->x, entity->y, NULL);
            setSpaceElement(getSpace(), newX, newY, entity);
            entity->x = newX;
            entity->y = newY;
        }
    }
}
