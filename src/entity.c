#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <stdio.h>

#include <entity.h>
#include <globals.h>
#include <class.h>
#include <list.h>
#include <io.h>

struct class *entity_class = NULL;

struct object *entity_array[WIDTH][HEIGHT];

struct list entity_list = {NULL};

void init_entity(struct object *entity) {
    list_add(&entity_list,entity);
    // TODO: insert into list too
    int *x = malloc(sizeof x);
    int *y = malloc(sizeof y);
    int *h = malloc(sizeof h);
    assert(x != NULL);
    assert(y != NULL);
    assert(h != NULL);
    // search for free place on board
    *x = -1;
    *y = -1;
    *h = STAY;
    set(entity,X,x);
    set(entity,Y,y);
    set(entity,HEADING,h);
}

int inside_screen(int x,int y) {
    return ((0 <= x) && (x < WIDTH) && (0 <= y) && (y < HEIGHT));
}

void destroy_entity(struct object *entity) {
    int *x = attr(entity,X);
    int *y = attr(entity,Y);
    if (inside_screen(*x,*y)) {
        set_char_at(*x,*y,' ');
        entity_array[*x][*y] = NULL;
    }
    list_remove(&entity_list,entity);
    free(attr(entity,X));
    free(attr(entity,Y));
    free(attr(entity,HEADING));
}

void *entity_goto(struct object *entity, va_list args) {
    int new_x = (int) va_arg(args,int);
    int new_y = (int) va_arg(args,int);
    char *symbol = attr(entity,SYMBOL);
    int *x = attr(entity,X);
    int *y = attr(entity,Y);
    // auf Kollisionen prüfen;
    if ((new_x == *x) && (new_y == *y)) return NULL; // do nothing when not changing position
    if (!inside_screen(new_x,new_y)) {
        call(entity,ON_COLLIDE,NULL,new_x,new_y); //NULL for colliding with wall
    }
    else if (entity_array[new_x][new_y] != NULL) {
        call(entity,ON_COLLIDE,entity_array[new_x][new_y],new_x,new_y);
    }
    else {
        // von alter Position löschen
        if (inside_screen(*x,*y)) {
            set_char_at(*x,*y,' ');
            entity_array[*x][*y] = NULL;
        }
        // Position ändern
        *x = new_x;
        *y = new_y;
        // an neuer Position eintragen
        set_char_at(*x,*y,*symbol);
        entity_array[*x][*y] = entity;
    }
    return NULL;
}

void *move(struct object *entity, va_list args) {
    int direction = (int) va_arg(args,int);
    int *x = attr(entity,X);
    int *y = attr(entity,Y);
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
    call(entity,GOTO,new_x,new_y);
    return NULL;
}

void *dummi(struct object *entity, va_list args) {
    (void)entity;
    (void)args;
    return NULL;
}

void update_entities() {
    struct object *entity;
    entity_list.bookmark = entity_list.first;
    while (entity_list.bookmark != NULL) {
        entity = entity_list.bookmark->value;
        entity_list.bookmark = entity_list.bookmark->next;
        call(entity,UPDATE);
    }
}

void init_entity_class() {
    if (entity_class == NULL) {
        entity_class = create_class(NULL,init_entity,destroy_entity);
        register_method(entity_class,MOVE,move);
        register_method(entity_class,GOTO,entity_goto);
        register_method(entity_class,ON_COLLIDE,dummi);
    }
}