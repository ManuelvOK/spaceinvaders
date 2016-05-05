#include <stdlib.h>
#include "../inc/io.h"
#include "../inc/globals.h"
#include "../inc/space.h"

struct space *globalSpace = NULL;

// Returns a pointer to a new space on the heap.
struct space *newSpace(unsigned char width, unsigned char height)
{
    unsigned size = width * height;
    struct space *newSpace = malloc(sizeof *newSpace);
    struct entity *array = calloc(size, sizeof(struct entity));

    if (newSpace == NULL || array == NULL)
    {
        terminate();
    }

    struct entity deadEntity = newEntity(INVADER, '.', 0);
    
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
        terminate();
    }

    space->playerPos = coords;
    setEntity(space, coords, player);
}

// Returns the position of the player of a space.
struct pos getPlayerPos(struct space *space)
{
    if (space == NULL)
    {
        terminate();
    }

    return space->playerPos;
}

// Destructively sets the element of a space to a given entity.
void setEntity(struct space *space, struct pos coords, struct entity content)
{
    if (spaceOutOfBounds(space, coords))
    {
        terminate();
    }

    space->array[coords.y * space->width + coords.x] = content;
}

// Returns the content of a space at specific coordinates.
struct entity getEntity(struct space *space, struct pos coords)
{
    if (spaceOutOfBounds(space, coords))
    {
        terminate();
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

// Wrappers and specific functions

// Initialises the global space variable.
void setupSpace()
{
    globalSpace = newSpace(WIDTH, HEIGHT);
}

// Returns the global space variable.
struct space *getSpace()
{
    return globalSpace;
}

// Non-destructive wrapper for adding an entity to the global space.
void addEntity(unsigned char x, unsigned char y, struct entity entity)
{
    if (getEntity(globalSpace, getPos(x, y)).health == 0)
    {
        setEntity(globalSpace, getPos(x, y), entity);
    }
}

// Wrapper for moving the player of the global space.
void movePlayer(struct pos change)
{
    moveEntity(globalSpace, getPlayerPos(globalSpace), change);
}
