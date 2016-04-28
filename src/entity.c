#include <assert.h>
#include <stdlib.h>

#include <entity.h>
#include <globals.h>
#include <io.h>

struct entity *entity_array[WIDTH][HEIGHT];

struct entity *create_entity() {
    struct entity *entity = malloc(sizeof *entity);
    assert(entity != NULL);
    return entity;
}

void delete_entity(struct entity *entity) {
    entity_array[entity->x][entity->y] = NULL;
    free(entity);
}

void update(struct entity *entity) {
    assert(entity->update != NULL);
    entity->update(entity);
}

void move(struct entity *entity, int direction) {
    // Berechnung
    int new_x = entity->x;
    int new_y = entity->y;
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
    set_char_at(entity->x,entity->y,' ');
    entity_array[entity->x][entity->y] = NULL;
    // an neuer Position einfügen
    entity->x = new_x;
    entity->y = new_y;
    set_char_at(entity->x,entity->y,entity->symbol);
    entity_array[entity->x][entity->y] = entity;
}