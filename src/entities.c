#include <entities.h>

struct entity *init_entity(enum entity_type type, unsigned x, unsigned y,
                           unsigned health, char symbol);
struct entity *init_player(unsigned x, unsigned y);
struct entity *init_fighter(unsigned x, unsigned y);
struct entity *init_laser(unsigned x, unsigned y, enum direction dir);
struct entity *init_wall(unsigned x, unsigned y);

struct entity_list *init_list(void);
void list_add_entity(struct entity_list *l, struct entity *e);
void list_foreach(struct entity_list *l, void (*f)(struct entity *));

void list_filter(struct entity_list *l, int (*p)(struct entity *)) {
    return;
}

void destroy_list(struct entity_list *l);
