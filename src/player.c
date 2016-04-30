#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include <player.h>
#include <entity.h>
#include <class.h>
#include <dict.h>
#include <globals.h>

struct class *player_class = NULL;

void *playerupdate(struct object *player,va_list args) {
    (void)args;
    call(player,MOVE,STAY);
    return NULL;
}

char playersymbol = 'A';

void init_player(struct object *player) {
    set(player,SYMBOL,&playersymbol);
}

void init_player_class() {
    player_class = create_class(entity_class,init_player,NULL);
    register_method(player_class,UPDATE,playerupdate);
}