#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <game.h>
#include <io.h>

const char *usage = "Usage:\n"
                    "\t./spaceinvaders <savestate>\n";

void *move_fighter_thread(void *retval);

static pthread_mutex_t board_mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {
    const struct game_state *state = NULL;
    if (argc > 2) {
        puts(usage);
        exit(EXIT_FAILURE);
    }
    if (argc == 2) {
        FILE *savestate = fopen(argv[1], "r");
        if (savestate != NULL) {
            state = load_state(savestate);
            fclose(savestate);
        }
    }
    if (state == NULL) {
        state = new_state();
    }

    srand(time(NULL));

    pthread_t tid;
    assert(pthread_create(&tid, NULL, move_fighter_thread, NULL) == 0);

    init_io();
    draw_board(state->the_board);

    do {
        pthread_mutex_lock(&board_mutex);
        proceed_state(read_input());
        draw_board(state->the_board);
        pthread_mutex_unlock(&board_mutex);
        wait_tick();
    } while (state->game_running == true);

    end_io();

    if (argc == 2) {
        FILE *savestate = fopen(argv[1], "w");
        if (savestate != NULL) {
            save_state(savestate);
            fclose(savestate);
        }
    }
    return 0;
}

void *move_fighter_thread(void *arg) {
    (void) arg;
    for (;;) {
        for (unsigned i = 0; i < 16; ++i) {
            wait_tick();
        }
        pthread_mutex_lock(&board_mutex);
        move_fighters();
        pthread_mutex_unlock(&board_mutex);
    }
    return NULL;
}
