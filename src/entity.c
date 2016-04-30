#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <stdio.h>

#include <entity.h>
#include <globals.h>
#include <class.h>
#include <io.h>

struct object *entity_array[WIDTH][HEIGHT];

struct class *entity_class = NULL;

void init_entity(struct object *entity) {
    entity_array[1][1] = entity;
    int *x = malloc(sizeof x);
    int *y = malloc(sizeof y);
    assert(x != NULL);
    assert(y != NULL);
    // search for free place on board
    *x = 1;
    *y = 1;
    set(entity,X,x);
    set(entity,Y,y);
}

void destroy_entity(struct object *entity) {
    free(attr(entity,X));
    free(attr(entity,Y));
}

void *move(struct object *entity, va_list args) {
    int direction = (int) va_arg(args,int);
    char *symbol = attr(entity,SYMBOL);
    int *x = attr(entity,X);
    int *y = attr(entity,Y);
    // Berechnung
    assert(x != NULL);
    int new_x = *x;
    int new_y = *y;
    int dx = 0;
    int dy = 0;
    dx += 0 != (direction & RIGHT);
    dx -= 0 != (direction & LEFT);
    dy += 0 != (direction & DOWN);
    dy -= 0 != (direction & UP);
    new_x+=dx;
    new_y+=dy;
    new_x%=WIDTH; // vlt. später ersetzen durch einfaches Wand-Verhalten
    new_y%=HEIGHT;
    // von alter Position löschen
    set_char_at(*x,*y,' ');
    entity_array[*x][*y] = NULL;
    // an neuer Position einfügen
    *x = new_x;
    *y = new_y;
    set_char_at(*x,*y,*symbol);
    entity_array[*x][*y] = entity;
    return NULL;
}

void init_entity_class() {
    entity_class = create_class(NULL,init_entity,NULL);
    register_method(entity_class,MOVE,move);
}