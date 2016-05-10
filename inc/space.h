#ifndef SPACE_H
#define SPACE_H

#include <stdbool.h>
#include "entity.h"

struct space
{
    struct entity *array;
    struct pos playerPos;
    unsigned char width;
    unsigned char height;
};

struct space *newSpace(unsigned char width, unsigned char height);
bool spaceOutOfBounds(struct space *space, struct pos coords);
void setPlayer(struct space *space, struct pos coords, struct entity player);
struct pos getPlayerPos(struct space *space);
void setEntity(struct space *space, struct pos coords, struct entity content);
struct entity getEntity(struct space *space, struct pos coords);
void moveEntity(struct space *space, struct pos current, struct pos change);

#endif
