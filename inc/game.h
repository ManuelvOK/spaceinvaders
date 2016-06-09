#ifndef GAME_H
#define GAME_H

#include <stdio.h>

#include <board.h>
#include <entities.h>

enum {
    DEFAULT_WIDTH = 50,
    DEFAULT_HEIGHT = 30,
    DEFAULT_ROWS = 5,
};

struct game_state {
    struct entity_list *players;
    struct entity_list *walls;
    struct entity_list *lasers;
    struct entity_list **fighters;
    unsigned n_fighter_rows;
    const struct board *the_board;
};

const struct game_state *load_state(FILE *savestate);
const struct game_state *new_state(void);
bool save_state(FILE *savestate);

#endif /* ifndef GAME_H */
