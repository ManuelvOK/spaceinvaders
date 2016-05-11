#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <structures.h>

void move_player(struct entity *player, int x_pos, int y_pos);
void move_fleet_row(struct fighter_row *row, int rel_x, int rel_y);
void generate_board();


#endif /* BOARD_H */
