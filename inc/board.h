#ifndef SPACEINVADERS_FIELD_H
#define SPACEINVADERS_FIELD_H

#include "entity.h"

/* Stores a 2-dimensional array of entities. */
struct board
{
    struct entity *data;
    unsigned width;
    unsigned height;
};

/* Creates a new board filled with empty entities. */
struct board brdCreate(unsigned width, unsigned height);

/* Frees the memory (allocated in brdCreate) of a board. */
void brdFree(struct board *this);

/* Returns the entity at a given coordinate. */
struct entity brdGet(struct board *this, unsigned x, unsigned y);

/* Returns an array of all entities in row 'y'.
 * The size of this array is 'this->width'.
 *
 * Do not free the pointer returned by this function.
 * */
struct entity *brdGetRow(struct board *this, unsigned y);

/* Sets an entity at a given coordinate. */
void brdSet(struct board *this, struct entity value, unsigned x, unsigned y);

#endif //SPACEINVADERS_FIELD_H
