#include <savestate.h>

#include <assert.h>
#include <stdlib.h>

#include <board.h>
#include <game.h>

static FILE *target_file;

static int get_fighter_row(unsigned y_pos, struct game_state *state) {
    for (unsigned i = 0; i < state->n_fighter_rows; ++i) {
        if (state->fighters[i]->length == 0
            || state->fighters[i]->first->pos.y == y_pos) {
            return i;
        }
    }
    return -1;
}

static void serialise(struct entity *e) {
    fprintf(target_file, "%u %u %u %u %u\n", e->pos.x, e->pos.y, e->type,
            e->symbol, e->health);
}

bool read_savestate(FILE *savestate, struct game_state *state) {
    int n_read;
    unsigned width, height;
    n_read = fscanf(savestate, "SP %u %u %u", &width, &height,
                    &state->n_fighter_rows);
    if (n_read != 3) {
        return false;
    }
    state->the_board = generate_board(width, height);
    state->fighters = calloc(state->n_fighter_rows,
                             sizeof *state->fighters);
    assert(state->fighters != NULL);
    for (unsigned i = 0; i < state->n_fighter_rows; ++i) {
        state->fighters[i] = init_list();
    }


    enum entity_type type;
    unsigned x, y;
    unsigned symbol, health;
    struct entity *entity;

    while ((n_read = fscanf(savestate,
                            "%u %u %u %u %u",
                            &x, &y, &type, &symbol, &health)) != EOF) {
        if (n_read != 5) {
            return false;
        }

        switch (type) {
            case E_PLAYER:
                entity = init_player(x, y);
                list_add_entity(state->players, entity);
                break;
            case E_WALL:
                entity = init_wall(x, y);
                list_add_entity(state->walls, entity);
                break;
            case E_FIGHTER:
                entity = init_fighter(x, y);
                int row = get_fighter_row(y, state);
                if (row < 0) {
                    return false;
                }
                list_add_entity(state->fighters[row], entity);
                break;
            default:
                break;
        }
    }
    return true;
}

bool write_savestate(FILE *savestate, const struct game_state *state) {
    fprintf(savestate, "SP %u %u %u\n", state->the_board->width,
            state->the_board->height, state->n_fighter_rows);
    target_file = savestate;
    list_foreach(state->players, serialise);
    list_foreach(state->walls, serialise);
    for (unsigned i = 0; i < state->n_fighter_rows; ++i) {
       list_foreach(state->fighters[i], serialise);
    }
    target_file = NULL;
    return true;
}
