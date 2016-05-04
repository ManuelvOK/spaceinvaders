#include <stdlib.h>
#include "../inc/io.h"
#include "../inc/globals.h"
#include "../inc/space.h"

struct space *globalSpace = NULL;

// Returns a pointer to a new space on the heap.
struct space *newSpace(unsigned char width, unsigned char height, struct pos playerPos)
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
    newSpace->playerPos = playerPos;
    newSpace->width = width;
    newSpace->height = height;

    return newSpace;
}

// Initialises the global space variable.
void setupSpace()
{
    struct pos playerPos = { (unsigned char)(WIDTH / 2), HEIGHT -1 };   // Could be generalised
    globalSpace = newSpace(WIDTH, HEIGHT, playerPos);
}

// Returns the global space variable.
struct space *getSpace()
{
    return globalSpace;
}

// Sets the player position of a space.
void setPlayer(struct space *space, struct pos coords)
{
    if (spaceOutOfBounds(space, coords))
    {
        terminate();
    }

    space->playerPos = coords;
}

// Returns the position of the player of a space.
struct pos getPlayer(struct space *space)
{
    if (space == NULL)
    {
        terminate();
    }

    return space->playerPos;
}

// Returns true if a space can be accessed at specific coordinates.
bool spaceOutOfBounds(struct space *space, struct pos coords)
{
    return (space == NULL || coords.x < 0 || coords.x >= space->width ||
        coords.y < 0 || coords.y >= space->height);
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

// Non-destructive wrapper for adding an entity to the global space.
void addEntity(unsigned char x, unsigned char y, struct entity entity)
{
    struct pos insertPos = { x, y };

    if (getEntity(globalSpace, insertPos).health == 0)
    {
        setEntity(globalSpace, insertPos, entity);
    }
}

// Moves an entity of the global space relatively to its current coordinates.
void moveEntity(struct pos current, struct pos change)
{   
    struct pos newPos = { current.x + change.x, current.y + change.y };
    
    if (!spaceOutOfBounds(globalSpace, newPos))
    { 
        struct entity atCurrent = getEntity(globalSpace, current);
        struct entity atNew = getEntity(globalSpace, newPos);

        if (atNew.health == 0)
        {
            setEntity(globalSpace, newPos, atCurrent);
            setEntity(globalSpace, current, atNew);
        }
    }
}
