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
    state->game_running = true;

    return state;
}

static void emit_laser(struct entity *origin) {
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

void proceed_state(enum input i) {
    switch (i) {
        case I_LEFT: move_entity(the_state->players->first, D_LEFT); break;
        case I_RIGHT: move_entity(the_state->players->first, D_RIGHT); break;
        case I_SAVE: break;
        case I_QUIT: the_state->game_running = false; break;
        case I_SHOOT: emit_laser(the_state->players->first); break;
        default: return;
    }
}

void move_fighters(void) {
    static enum direction cur_dir = D_RIGHT;
    static unsigned cur_row = 0;
    struct entity_list *cur_list = the_state->fighters[cur_row];
    if (cur_list->first != NULL) {
        unsigned row_y = cur_list->first->pos.y;
        unsigned b_width = the_state->the_board->width;
        if (cur_dir == D_RIGHT) {
            struct entity *to_check = the_state->the_board->map[row_y *
                                            b_width + b_width -1];
            if (to_check != NULL && to_check->type == E_FIGHTER) {
                cur_dir = D_LEFT;
            }
        } else {
            struct entity *to_check = the_state->the_board->map[row_y * b_width];
            if (to_check != NULL && to_check->type == E_FIGHTER) {
                cur_dir = D_RIGHT;
            }
        }
        for (struct entity *e = the_state->fighters[cur_row]->first;
                e != NULL;
                e = e->next) {
            move_entity(e, cur_dir);
        }
    }
    cur_row = (cur_row + 1) % the_state->n_fighter_rows;
}
