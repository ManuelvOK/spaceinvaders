#ifndef BOARD_H
#define BOARD_H

#include <entities.h>

struct board {
    unsigned width;
    unsigned height;
    struct entity **map;
};

int out_of_bounds(unsigned x, unsigned y);
struct entity *collision(unsigned x, unsigned y);
const struct board *generate_board(unsigned width, unsigned height);

int place_entity(struct entity *e);
int move_entity(struct entity *e, enum direction dir);
int remove_entity(struct entity *e);

#endif /* ifndef BOARD_H */
