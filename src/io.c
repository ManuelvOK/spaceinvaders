#include <io.h>

#include <assert.h>
#include <ncurses.h>
#include <stdlib.h>

static char *board_cache;

void init_io(void) {
    initscr();
    curs_set(0);
    start_color();
    clear();
    noecho();
    keypad(stdscr, TRUE);
    cbreak();
    nodelay(stdscr, TRUE);
    int i = getch();
    (void) i;
}

void draw_board(const struct board *board) {
    if (board_cache == NULL) {
        board_cache = calloc(board->width * board-> height,
                             sizeof *board_cache);
        assert(board_cache != NULL);
        clear();
        move(0, 0);

        printw("|");
        for (unsigned x = 0; x < board->width; ++x) {
            printw("=");
        }
        printw("|\n");

        for (unsigned y = 0; y < board->height; ++y) {
            printw("|");
            move(y + 1, board->width + 1);
            printw("|\n");
        }

        printw("|");
        for (unsigned x = 0; x < board->width; ++x) {
            printw("=");
        }
        printw("|\n");
    }

    for (unsigned y = 0; y < board->height; ++y) {
        for (unsigned x = 0; x < board->width; ++x) {
            if (board->map[board->width*y+x] == NULL) {
                if (board_cache[board->width*y+x] != 0) {
                    board_cache[board->width*y+x] = 0;
                    mvprintw(y + 1, x + 1, "%c", ' ');
                }
            } else if (board_cache[board->width*y+x]
                    != board->map[board->width*y+x]->symbol) {
                board_cache[board->width*y+x] = board->map[board->width*y+x]->symbol;
                mvprintw(y + 1, x + 1, "%c", board_cache[board->width*y+x]);
            }
        }
    }
    refresh();
}

void end_io(void) {
    endwin();
}
