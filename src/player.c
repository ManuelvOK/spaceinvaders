#include <player.h>
#include <entity.h>

void playerupdate(struct entity *player) {
    move(player,0);
}

struct entity *create_player() {
    struct entity *player = create_entity();
    struct entity tmp = {'A', 1, 1, playerupdate};
    *player = tmp;
    return player;
}
