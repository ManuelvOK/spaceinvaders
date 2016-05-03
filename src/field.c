#include <stdlib.h>

#include "../inc/entity.h"
#include "../inc/field.h"

struct field fldCreate(unsigned width, unsigned height)
{
    struct field fld;

    fld.width = width;
    fld.height = height;
    fld.data = (struct entity*)calloc(width * height, sizeof(struct entity));

    return fld;
}

void fldFree(struct field *this)
{
    free(this->data);
}



struct entity fldGet(struct field *this, unsigned x, unsigned y)
{
    if (x >= this->width)  return entGetEmpty();
    if (y >= this->height) return entGetEmpty();

    return this->data[y * this->width + x];
}

void fldSet(struct field *this, struct entity value, unsigned x, unsigned y)
{
    if (x >= this->width)  return;
    if (y >= this->height) return;

    this->data[y * this->width + x] = value;
}
