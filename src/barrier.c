#include <stdlib.h>
#include <stdarg.h>

#include <assert.h>
#include <stdio.h>

#include <barrier.h>
#include <entity.h>
#include <class.h>
#include <globals.h>

struct class *barrier_class = NULL;

enum {STATECOUNT = 3};
char barriersymbols[STATECOUNT] = ".oO";

static void init(struct object *barrier) {
    int *health = attr(barrier,HEALTH);
    *health = STATECOUNT;
    set(barrier,SYMBOL,&(barriersymbols[*health-1]));
}

static void *update(struct object *barrier,va_list args) {
    (void)args;
    int *health = attr(barrier,HEALTH);
    if (*health == 0) {
        delete_object(barrier);
    } else {
        // change symbol and redraw
        set(barrier,SYMBOL,&(barriersymbols[*health-1]));
        float *x = attr(barrier,X);
        float *y = attr(barrier,Y);
        call(barrier,GOTO,*x,*y);
    }
    return NULL;
}

void init_barrier_class() {
    if (barrier_class == NULL) {
        init_entity_class();
        barrier_class = create_class(entity_class,init,NULL);
        register_method(barrier_class,UPDATE,update);
    }
}