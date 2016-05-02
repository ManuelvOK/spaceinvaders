#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include <player.h>
#include <entity.h>
#include <class.h>
#include <globals.h>
#include <projectile.h>

struct class *player_class = NULL;

char playersymbol = 'A';

static void init_player(struct object *player) {
    float *dx = malloc(sizeof dx);
    float *dy = malloc(sizeof dy);
    assert(dx != NULL);
    assert(dy != NULL);
    set(player,DX,dx);
    set(player,DY,dy);
    set(player,SYMBOL,&playersymbol);
    int *h = attr(player,HEADING);
    *h = UP;
    *dx = 0;
    *dy = 0;
    call(player,GOTO,(float) WIDTH/2, (float) HEIGHT/2);
}

static void deinit_player(struct object *player) {
    free(attr(player,DX));
    free(attr(player,DY));
}

static void *playerupdate(struct object *player,va_list args) {
    (void)args;
    float *x  = attr(player,X);
    float *y  = attr(player,Y);
    float *dx = attr(player,DX);
    float *dy = attr(player,DY);
    call(player,GOTO,*x+*dx,*y+*dy);
    return NULL;
}

static void *playercontrol(struct object *player,va_list args) {
    int direction = (int) va_arg(args,int);
    float *dx = attr(player,DX);
    float *dy = attr(player,DY);
    float a = 0.1;
    *dx += a * !!(direction & RIGHT);
    *dx -= a * !!(direction & LEFT);
    *dy += a * !!(direction & DOWN);
    *dy -= a * !!(direction & UP);
    if (*dx > 1) *dx = 1;
    if (*dx <-1) *dx =-1;
    if (*dy > 1) *dy = 1;
    if (*dy <-1) *dy =-1;
    
    if (direction & FIRE) {
        call(player,FIRE);
    }
    return NULL;
}

static void *on_collide(struct object *player, va_list args) {
    (void)args;
    float *dx = attr(player,DX);
    float *dy = attr(player,DY);
    *dx = 0;
    *dy = 0;
    return NULL;
}

void init_player_class() {
    if (player_class == NULL) {
        init_entity_class();
        init_projectile_class();
        player_class = create_class(entity_class,init_player,deinit_player);
        register_method(player_class,UPDATE,playerupdate);
        register_method(player_class,CONTROL,playercontrol);
        register_method(player_class,ON_COLLIDE,on_collide);
    }
}