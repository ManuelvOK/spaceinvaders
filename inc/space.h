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

struct space *newSpace(unsigned char width, unsigned char height, struct pos playerPos);
void setupSpace();
struct space *getSpace();
void setPlayer(struct space *space, struct pos coords);
struct pos getPlayer();
bool spaceOutOfBounds(struct space *space, struct pos coords);
void setEntity(struct space *space, struct pos coords, struct entity content);
struct entity getEntity(struct space *space, struct pos coords);
void addEntity(unsigned char x, unsigned char y, struct entity entity);
void moveEntity(struct pos current, struct pos change);

#endif
