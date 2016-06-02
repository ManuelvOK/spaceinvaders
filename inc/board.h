#ifndef SPACEINVADERS_FIELD_H
#define SPACEINVADERS_FIELD_H

#include <stdio.h>
#include "entity.h"

/* Stores a 2-dimensional array of entities. */
struct board
{
    struct entity *data;
    unsigned width;
    unsigned height;
    unsigned xoffset;
    unsigned yoffset;
	char monster_state;
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

/*!
 * Writes the board to the given file and returns the number of bytes written
 * or 0 if something went wrong.
 */
size_t brdWrite(struct board *this, FILE *file);

#endif //SPACEINVADERS_FIELD_H
