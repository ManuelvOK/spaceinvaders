#include <board.h>

// board logic like moving ships or size of the board
int width = 0;
int height = 0;


void generate_board(/*int width, int height*/) {

}

void move_player(struct entity *player, int x_pos, int y_pos) {
    if (player == NULL) {
        return;
    }

    player->x = x_pos;
    player->y = y_pos;
}


void move_fleet_row(struct fighter_row *row, int rel_x, int rel_y) {
    if (row == NULL) {
        return;
    }

    for (struct fighter *fighter = row->first; fighter != NULL; fighter = fighter->next) {
            fighter->data.x += rel_x;
            fighter->data.y += rel_y;
    }
}
