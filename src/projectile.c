#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include <projectile.h>
#include <entity.h>
#include <class.h>
#include <globals.h>

struct class *projectile_class = NULL;

char projectilesymbol = '|';

static void init(struct object *projectile) {
    set(projectile,SYMBOL,&projectilesymbol);
}

static void *update(struct object *projectile,va_list args) {
    (void)args;
    int *heading = attr(projectile,HEADING);
    call(projectile,MOVE,*heading);
    return NULL;
}

static void *on_collide(struct object *projectile, va_list args) {
    struct object *other = (void *) va_arg(args,void *);
    if (other != NULL) {
        int *health = attr(other,HEALTH);
        *health -= 1;
    }
    delete_object(projectile);
    return NULL;
}

static void *fire(struct object *entity, va_list args) {
    (void)args;
    float *x = attr(entity,X);
    float *y = attr(entity,Y);
    int *heading = attr(entity,HEADING);
    int dx = 0;
    int dy = 0;
    dx += !!(*heading & RIGHT);
    dx -= !!(*heading & LEFT);
    dy += !!(*heading & DOWN);
    dy -= !!(*heading & UP);
    struct object *projectile = create_from(projectile_class);
    int *p_heading = attr(projectile,HEADING);
    *p_heading = *heading;
    call(projectile,GOTO,*x+dx,*y+dy);
    return NULL;
}

void init_projectile_class() {
    if (projectile_class == NULL) {
        init_entity_class();
        projectile_class = create_class(entity_class,init,NULL);
        register_method(projectile_class,UPDATE,update);
        register_method(projectile_class,ON_COLLIDE,on_collide);
        register_method(entity_class,FIRE,fire);
    }
}