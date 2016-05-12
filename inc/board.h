#ifndef SPACEINVADERS_FIELD_H
#define SPACEINVADERS_FIELD_H

#include "entity.h"

struct board
{
    struct entity *data;
    unsigned width;
    unsigned height;
};

struct board brdCreate(unsigned width, unsigned height);
void brdFree(struct board *this);

struct entity brdGet(struct board *this, unsigned x, unsigned y);
void brdSet(struct board *this, struct entity value, unsigned x, unsigned y);

#endif //SPACEINVADERS_FIELD_H
