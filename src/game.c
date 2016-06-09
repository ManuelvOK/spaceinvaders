#include <game.h>

#include <assert.h>
#include <stdlib.h>

#include <board.h>
#include <entities.h>
#include <savestate.h>

static struct game_state *the_state;

static struct game_state *empty_state() {
    struct game_state *state =  calloc(1, sizeof *the_state);
    assert(state != NULL);

    state->players = init_list();
    state->walls = init_list();
    state->lasers = init_list();

    return state;
}

const struct game_state *load_state(FILE *savestate) {
    assert(the_state == NULL);
    the_state = empty_state();

    if (!read_savestate(savestate, the_state)) {
        destroy_list(the_state->players);
        destroy_list(the_state->lasers);
        destroy_list(the_state->walls);
        if (the_state->fighters != NULL) {
            for (unsigned i = 0; i < the_state->n_fighter_rows; ++i) {
                destroy_list(the_state->fighters[i]);
            }
            free(the_state->fighters);
        }
        if (the_state->the_board != NULL) {
            destroy_board();
        }
        free(the_state);
        the_state = NULL;
    }

    return the_state;
}

const struct game_state *new_state(void) {
    assert(the_state == NULL);

    the_state = empty_state();
    the_state->n_fighter_rows = DEFAULT_ROWS;
    the_state->fighters = calloc(the_state->n_fighter_rows,
                                 sizeof *the_state->fighters);
    assert(the_state->fighters != NULL);

    for (unsigned i = 0; i < the_state->n_fighter_rows; ++i) {
        the_state->fighters[i] = init_list();
    }

    the_state->the_board = generate_board(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    return the_state;
}

bool save_state(FILE *savestate) {
    assert(the_state != NULL);

    return write_savestate(savestate, the_state);
}
