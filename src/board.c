#include <board.h>

static struct board *the_board;

bool out_of_bounds(unsigned x, unsigned y);
struct entity *collision(unsigned x, unsigned y);
const struct board *generate_board(unsigned width, unsigned height);

bool place_entity(struct entity *e);
bool move_entity(struct entity *e, enum direction dir);
bool remove_entity(struct entity *e);
