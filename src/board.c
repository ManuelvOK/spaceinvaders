#include <board.h>

#include <assert.h>
#include <stdlib.h>

static struct board *the_board;

static struct position next_pos(struct position pos, enum direction dir);

bool out_of_bounds(unsigned x, unsigned y) {
    return !(x < the_board->width && y < the_board->height);
}

struct entity *collision(unsigned x, unsigned y) {
    if (out_of_bounds(x, y)) {
        return NULL;
    }
    return the_board->map[the_board->width * y + x];
}

const struct board *generate_board(unsigned width, unsigned height) {
	assert(the_board == NULL);

    the_board = calloc(1, sizeof *the_board);
    assert(the_board != NULL);

    the_board->map = calloc(width * height, sizeof *the_board->map);
    assert(the_board->map != NULL);

    the_board->width = width;
    the_board->height = height;

    return the_board;
}

void destroy_board(void) {
    free(the_board->map);
    free(the_board);
    the_board = NULL;
}

bool place_entity(struct entity *e) {
    if (collision(e->pos.x, e->pos.y) || !e->valid) {
        return false;
    }
    the_board->map[the_board->width * e->pos.y + e->pos.x] = e;
    return true;
}

bool move_entity(struct entity *e, enum direction dir) {
    struct position new_pos = next_pos(e->pos, dir);

    if (out_of_bounds(new_pos.x, new_pos.y)
        || collision(new_pos.x, new_pos.y) != NULL) {
           return false;
    }

    the_board->map[the_board->width * e->pos.y + e->pos.x] = NULL;
    e->pos = new_pos;
    the_board->map[the_board->width * e->pos.y + e->pos.x] = e;
    return true;
}

bool remove_entity(struct entity *e) {
    if (collision(e->pos.x, e->pos.y) != e) {
        return false;
    }
    the_board->map[e->pos.x + the_board->width * e->pos.y] = NULL;
    e->valid = false;
    return true;
}

static struct position next_pos(struct position pos, enum direction dir) {
    switch (dir) {
        case D_UP :
           --pos.y;
           break;
        case D_DOWN :
           ++pos.y;
           break;
        case D_LEFT :
            --pos.x;
            break;
        case D_RIGHT :
            ++pos.x;
            break;
    }
    return pos;
}
