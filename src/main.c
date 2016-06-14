#include <stdio.h>
#include <stdlib.h>

#include <game.h>
#include <io.h>

const char *usage = "Usage:\n"
                    "\t./spaceinvaders <savestate>\n";

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

    init_io();
    draw_board(state->the_board);

    do {
        proceed_state(read_input());
        draw_board(state->the_board);
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
