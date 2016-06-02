#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#include <entities.h>

struct board {
    unsigned width;
    unsigned height;
    struct entity **map;
};

bool out_of_bounds(unsigned x, unsigned y);
struct entity *collision(unsigned x, unsigned y);
const struct board *generate_board(unsigned width, unsigned height);

bool place_entity(struct entity *e);
bool move_entity(struct entity *e, enum direction dir);
bool remove_entity(struct entity *e);

#endif /* ifndef BOARD_H */
