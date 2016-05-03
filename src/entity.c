#include <stdlib.h>
#include "../inc/entity.h"
#include "../inc/io.h"
#include "../inc/globals.h"
#include "../inc/space.h"

struct entity *player;

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

// Initialises the global player variable.
void setupPlayer()
{
    player = newEntity((unsigned)(WIDTH / 2), HEIGHT - 1, 1, 'A');
    addEntity(getSpace(), player);
}

// Returns the global player variable.
struct entity *getPlayer()
{
    return player;
}

// Moves an entity from one position on the global space to another.
void moveEntity(struct entity *entity, int deltaX, int deltaY)
{
    if (entity == NULL)
    {
        terminate();
    }

    if ((int)(entity->x) + deltaX >= 0 || (int)(entity->y) + deltaY >= 0)
    {
        unsigned newX = (int)(entity->x) + deltaX;
        unsigned newY = (int)(entity->y) + deltaY;
    
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
}
