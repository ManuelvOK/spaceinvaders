#include <board.h>

static struct board *the_board;

int out_of_bounds(unsigned x, unsigned y);
struct entity *collision(unsigned x, unsigned y);
const struct board *generate_board(unsigned width, unsigned height);

int place_entity(struct entity *e);
int move_entity(struct entity *e, enum direction dir);
int remove_entity(struct entity *e);
