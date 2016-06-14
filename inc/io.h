#ifndef IO_H
#define IO_H

#include <board.h>

enum input {
    I_LEFT,
    I_RIGHT,
    I_SHOOT,
    I_SAVE,
    I_QUIT,
    I_NOP,
};

void init_io(void);
void draw_board(const struct board *the_board);
void end_io(void);

enum input read_input(void);

void wait_tick(void);

#endif /* IO_H */
