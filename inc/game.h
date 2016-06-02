#ifndef GAME_H
#define GAME_H

#include <entities.h>

struct game_state {
    struct entity_list *players;
    struct entity_list *walls;
    struct entity_list *lasers;
    struct entity_list **fighters;
    unsigned n_fighter_rows;
};

#endif /* ifndef GAME_H */
