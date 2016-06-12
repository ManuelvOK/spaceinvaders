#ifndef IO_H
#define IO_H

#include <board.h>

void init_io(void);
void draw_board(const struct board *the_board);
void end_io(void);

#endif /* IO_H */
