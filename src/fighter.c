#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <time.h>

#include <fighter.h>
#include <entity.h>
#include <class.h>
#include <globals.h>
#include <projectile.h>

struct class *fighter_class = NULL;

char fightersymbol = 'V';

static void init(struct object *fighter) {
    float *counter = malloc(sizeof counter);
    assert(counter != NULL);
    set(fighter,COUNTER,counter);
    set(fighter,SYMBOL,&fightersymbol);

    int *h = attr(fighter,HEADING);
    int *health = attr(fighter,HEALTH);
    *counter = 0;
    *h = DOWN;
    *health = 1;
}

static void deinit(struct object *fighter) {
    free(attr(fighter,COUNTER));
}

static void *update(struct object *fighter,va_list args) {
    (void)args;
    int *health = attr(fighter,HEALTH);
    int *counter = attr(fighter,COUNTER);

    if (*health == 0) {
        delete_object(fighter);
    } else {
        int random = rand();
        if (!(random%10)) call(fighter,MOVE,LEFT);
        if (!((random+1)%10)) call(fighter,MOVE,RIGHT);
        if (!(random%50)) call(fighter,FIRE);
        ++*counter;
    }
    return NULL;
}

void init_fighter_class() {
    if (fighter_class == NULL) {
        init_entity_class();
        init_projectile_class();
        fighter_class = create_class(entity_class,init,deinit);
        register_method(fighter_class,UPDATE,update);
        time_t t;
        time(&t);
        srand((unsigned int) t);
    }
}