#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include <projectile.h>
#include <entity.h>
#include <class.h>
#include <globals.h>

struct class *projectile_class = NULL;

void *projectileupdate(struct object *projectile,va_list args) {
    (void)args;
    call(projectile,MOVE,UP);
    return NULL;
}

char projectilesymbol = '|';

void init_projectile(struct object *projectile) {
    set(projectile,SYMBOL,&projectilesymbol);
}

void *on_collide(struct object *projectile, va_list args) {
    struct object *other = (void *) va_arg(args,void *);
    if (other == NULL) {
        delete_object(projectile);
    }
    return NULL;
}

void *fire(struct object *entity, va_list args) {
    (void)args;
    float *x = attr(entity,X);
    float *y = attr(entity,Y);
    int *heading = attr(entity,HEADING);
    int dx = 0;
    int dy = 0;
    dx += 0 != (*heading & RIGHT);
    dx -= 0 != (*heading & LEFT);
    dy += 0 != (*heading & DOWN);
    dy -= 0 != (*heading & UP);
    struct object *projectile = create_from(projectile_class);
    call(projectile,GOTO,*x+dx,*y+dy);
    return NULL;
}

void init_projectile_class() {
    if (projectile_class == NULL) {
        init_entity_class();
        projectile_class = create_class(entity_class,init_projectile,NULL);
        register_method(projectile_class,UPDATE,projectileupdate);
        register_method(projectile_class,ON_COLLIDE,on_collide);
        register_method(entity_class,FIRE,fire);
    }
}