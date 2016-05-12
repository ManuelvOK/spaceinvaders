#include <stdlib.h>

#include "../inc/entity.h"
#include "../inc/board.h"

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

    return this->data[y * this->width + x];
}

void brdSet(struct board *this, struct entity value, unsigned x, unsigned y)
{
    if (x >= this->width)  return;
    if (y >= this->height) return;

    this->data[y * this->width + x] = value;
}
