#ifndef SPACEINVADERS_FIELD_H
#define SPACEINVADERS_FIELD_H

#include "entity.h"

struct field
{
    struct entity *data;
    unsigned width;
    unsigned height;
};

struct field fldCreate(unsigned width, unsigned height);
void fldFree(struct field *this);

struct entity fldGet(struct field *this, unsigned x, unsigned y);
void fldSet(struct field *this, struct entity value, unsigned x, unsigned y);

#endif //SPACEINVADERS_FIELD_H
