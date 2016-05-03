#include <stdlib.h>
#include "../inc/io.h"
#include "../inc/globals.h"
#include "../inc/space.h"

struct space *globalSpace = NULL;

// Returns a pointer to a new space on the heap.
struct space *newSpace(unsigned width, unsigned height)
{
    struct space *newSpace = malloc(sizeof *newSpace);
    struct entity **array = calloc(width * height, sizeof(struct entity *));

    if (newSpace == NULL || array == NULL)
    {
        terminate();
    }

    newSpace->array = array;
    newSpace->width = width;
    newSpace->height = height;

    return newSpace;
}

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

// Returns true if a space can be accessed at specific coordinates.
bool spaceOutOfBounds(struct space *space, unsigned x, unsigned y)
{
    return (space == NULL || x >= space->width || y >= space->height);
}

// Destructively sets the element of a space to a given pointer.
void setSpaceElement(struct space *space, unsigned x, unsigned y, struct entity *content)
{
    if (spaceOutOfBounds(space, x, y))
    {
        terminate();
    }

    space->array[y * space->width + x] = content;
}

// Returns the content of a space at specific coordinates.
struct entity *getSpaceElement(struct space *space, unsigned x, unsigned y)
{
    if (spaceOutOfBounds(space, x, y))
    {
        terminate();
    }

    return space->array[y * space->width + x];
}

// Non-destructive wrapper for adding an entity to the space.
void addEntity(struct space *space, struct entity *entity)
{
    if (entity == NULL || space == NULL)
    {
        terminate();
    }

    if (getSpaceElement(space, entity->x, entity->y) == NULL)
    {
        setSpaceElement(space, entity->x, entity->y, entity);
    }
}
