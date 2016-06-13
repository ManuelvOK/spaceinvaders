#include <stdio.h>
#include <stdlib.h>
#include "../inc/io.h"
#include "../inc/globals.h"
#include "../inc/spaceCore.h"

// Returns a pointer to a new space on the heap.
struct space *newSpace(unsigned char width, unsigned char height)
{
    unsigned size = width * height;
    struct space *newSpace = malloc(sizeof *newSpace);
    struct entity *array = calloc(size, sizeof(struct entity));

    if (newSpace == NULL || array == NULL)
    {
        terminate("newSpace");
    }

    struct entity deadEntity = newEntity(T_INVADER, '.', 0);

    for (unsigned i = 0; i < size; i++)
    {
        array[i] = deadEntity;
    }

    newSpace->array = array;
    newSpace->playerPos = getPos(0, 0);
    newSpace->width = width;
    newSpace->height = height;

    return newSpace;
}

// Returns true if a space can be accessed at specific coordinates.
bool spaceOutOfBounds(struct space *space, struct pos coords)
{
    return (space == NULL || coords.x < 0 || coords.x >= space->width ||
        coords.y < 0 || coords.y >= space->height);
}

// Adds a given entity to a space and makes it the space's player.
void setPlayer(struct space *space, struct pos coords, struct entity player)
{
    if (spaceOutOfBounds(space, coords))
    {
        terminate("setPlayer");
    }

    space->playerPos = coords;
    setEntity(space, coords, player);
}

// Returns the position of the player of a space.
struct pos getPlayerPos(struct space *space)
{
    if (space == NULL)
    {
        terminate("getPlayerPos");
    }

    return space->playerPos;
}

// Destructively sets the element of a space to a given entity.
void setEntity(struct space *space, struct pos coords, struct entity content)
{
    if (spaceOutOfBounds(space, coords))
    {
        char *message = calloc(100, sizeof(char));
        sprintf(message, "setEntity x: %d y: %d width: %d, height: %d", coords.x,
            coords.y, P_WIDTH, P_HEIGHT);
        terminate(message);
    }

    space->array[coords.y * space->width + coords.x] = content;
}

// Returns the content of a space at specific coordinates.
struct entity getEntity(struct space *space, struct pos coords)
{
    if (spaceOutOfBounds(space, coords))
    {
        char *message = calloc(100, sizeof(char));
        sprintf(message, "getEntity x: %d y: %d width: %d, height: %d", coords.x,
            coords.y, P_WIDTH, P_HEIGHT);
        terminate(message);
    }

    return space->array[coords.y * space->width + coords.x];
}

// Moves an entity of a space relatively to its current coordinates.
void moveEntity(struct space *space, struct pos current, struct pos change)
{
    struct pos newPos = { current.x + change.x, current.y + change.y };

    if (!spaceOutOfBounds(space, newPos))
    {
        struct entity atCurrent = getEntity(space, current);
        struct entity atNew = getEntity(space, newPos);

        if (atNew.health == 0)
        {
            setEntity(space, newPos, atCurrent);
            setEntity(space, current, atNew);

            if (posEquals(getPlayerPos(space), current))
            {
                space->playerPos = newPos;
            }
        }
    }
}
