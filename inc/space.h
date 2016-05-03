#ifndef SPACE_H
#define SPACE_H

#include <stdbool.h>
#include "entity.h"

struct space
{
    struct entity **array;
    unsigned width;
    unsigned height;
};

struct space *newSpace(unsigned width, unsigned height);
void setupSpace();
struct space *getSpace();
bool spaceOutOfBounds(struct space *space, unsigned x, unsigned y);
void setSpaceElement(struct space *space, unsigned x, unsigned y, struct entity *content);
struct entity *getSpaceElement(struct space *space, unsigned x, unsigned y);
void printSpace(struct space *space);
void addEntity(struct space *space, struct entity *entity);

#endif
