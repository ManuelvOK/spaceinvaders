#include <entities.h>

#include <assert.h>
#include <stdlib.h>

struct entity *init_entity(enum entity_type type, unsigned x, unsigned y,
                           unsigned health, char symbol) {
    struct entity *ent = malloc(sizeof *ent);
    assert(ent != NULL);
    ent->type = type;
    ent->health = health;
    ent->pos = (struct position) {x, y};
    ent->symbol = symbol;
    ent->next = NULL;
    ent->valid = 1;
    return ent;
}

struct entity *init_player(unsigned x, unsigned y) {
	struct entity *entity = init_entity(E_PLAYER, x, y, 1, 'A');
    entity->ent.as_player.score = 0;
	return entity;
}

struct entity *init_fighter(unsigned x, unsigned y) {
	struct fighter fighter;
    fighter.current_dir = D_LEFT;

    struct entity *new_entity = init_entity(E_FIGHTER, x, y, 9001, 'Y');
    new_entity->ent.as_fighter = fighter;

    return new_entity;
}

struct entity *init_laser(unsigned x, unsigned y, enum direction dir) {
    struct entity *e = init_entity(E_LASER, x, y, 1, '|');
    e->ent.as_laser.dir = dir;
}

struct entity *init_wall(unsigned x, unsigned y) {
    return init_entity(E_WALL, x, y, 2, '0');
}

struct entity_list *init_list(void) {
    struct entity_list *l = malloc(sizeof *l);
    assert(l != NULL);
    l->first = NULL;
    l->length = 0;
    return l;
}

void list_add_entity(struct entity_list *l, struct entity *e) {
    assert(e != NULL);
    assert(l != NULL);
    e->next = l->first;
    l->first = e;
    ++l->length;
}

void list_foreach(struct entity_list *l, void (*f)(struct entity *)) {
    assert(l != NULL);
    struct entity *next = NULL;
    for (struct entity *iterator = l->first; iterator != NULL; iterator = next) {
        next = iterator->next;
        f(iterator);
    }
}


void list_filter(struct entity_list *l, int (*p)(struct entity *)) {
    return;
}

void destroy_list(struct entity_list *l) {
    assert(l != NULL);
    list_foreach(l, (void(*)(struct entity*)) free);
    free(l);
}
