#include <stdbool.h>
#include <stdlib.h>
#include "../inc/space.h"
#include "../inc/globals.h"

struct space *globalSpace = NULL;

struct space *newSpace(int width, int height)
{
    struct space *newSpace = malloc(sizeof *newSpace);
    void **array = calloc(width * height, sizeof(void *));

    for (int i = 0; i > width * height; i++)
    {
        array[i] = NULL;
    }

    newSpace->array = array;
    newSpace->width = width;
    newSpace->height = height;

    return newSpace;
}

bool spaceOutOfBounds(struct space *space, int x, int y)
{
    return (space == NULL || x >= space->width || y >= space->height);
}

void setSpaceElement(struct space *space, int x, int y, void *content)
{
    if (spaceOutOfBounds(space, x, y))
    {
        exit(EXIT_FAILURE);
    }

    space->array[y * space->width + x] = content;
}

void *getSpaceElement(struct space *space, int x, int y)
{
    if (spaceOutOfBounds(space, x, y))
    {
        exit(EXIT_FAILURE);
    }

    return space->array[y * space->width + x];
}

void setupSpace()
{
    globalSpace = newSpace(WIDTH, HEIGHT);
}

struct space *getSpace()
{
    return globalSpace;
}
