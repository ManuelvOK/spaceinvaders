#include <stdlib.h>

#include "../inc/entity.h"
#include "../inc/board.h"

#define INDEX(x, y, width) ((y) * (width) + (x))

struct board brdCreate(unsigned width, unsigned height)
{
    struct board brd;

    brd.width = width;
    brd.height = height;
    brd.data = (struct entity*)calloc(width * height, sizeof(struct entity));

    return brd;
}

void brdFree(struct board *this)
{
    free(this->data);
}



struct entity brdGet(struct board *this, unsigned x, unsigned y)
{
    if (x >= this->width)  return entCreateEmpty();
    if (y >= this->height) return entCreateEmpty();

    return this->data[INDEX(x, y, this->width)];
}

struct entity *brdGetRow(struct board *this, unsigned y)
{
    if (y >= this->height) return NULL;

    return this->data + INDEX(0, y, this->width);
}

void brdSet(struct board *this, struct entity value, unsigned x, unsigned y)
{
    if (x >= this->width)  return;
    if (y >= this->height) return;

    this->data[INDEX(x, y, this->width)] = value;
}
