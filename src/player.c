#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include <player.h>
#include <entity.h>
#include <class.h>
#include <globals.h>
#include <projectile.h>

struct class *player_class = NULL;

void *playerupdate(struct object *player,va_list args) {
    (void)args;
    call(player,MOVE,STAY);
    return NULL;
}

void *playercontrol(struct object *player,va_list args) {
    int direction = (int) va_arg(args,int);
    call(player,MOVE,direction);
    if (direction & FIRE) {
        call(player,FIRE);
    }
    return NULL;
}

char playersymbol = 'A';

void init_player(struct object *player) {
    set(player,SYMBOL,&playersymbol);
    int *h = attr(player,HEADING);
    *h = UP;
    call(player,GOTO,WIDTH/2,HEIGHT/2);
}

void init_player_class() {
    if (player_class == NULL) {
        init_entity_class();
        init_projectile_class();
        player_class = create_class(entity_class,init_player,NULL);
        register_method(player_class,UPDATE,playerupdate);
        register_method(player_class,CONTROL,playercontrol);
    }
}