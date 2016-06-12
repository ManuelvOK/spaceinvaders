#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdbool.h>

enum entity_type {
    E_PLAYER,
    E_FIGHTER,
    E_WALL,
    E_LASER,
};

enum direction {
    D_UP,
    D_DOWN,
    D_LEFT,
    D_RIGHT,
};

struct player {
    int score;
};

struct fighter {
    enum direction current_dir;
};

struct laser {
    enum direction dir;
};

struct position {
    unsigned x;
    unsigned y;
};

struct entity {
    enum entity_type type;
    unsigned health;
    struct position pos;
    char symbol;
    union {
        struct player as_player;
        struct fighter as_fighter;
        struct laser as_laser;
    } ent;
    struct entity *next;
    bool valid;
};

struct entity_list {
    struct entity *first;
    unsigned length;
};

struct entity *init_entity(enum entity_type type, unsigned x, unsigned y,
                           unsigned health, char symbol);
struct entity *init_player(unsigned x, unsigned y);
struct entity *init_fighter(unsigned x, unsigned y);
struct entity *init_laser(unsigned x, unsigned y, enum direction dir);
struct entity *init_wall(unsigned x, unsigned y);

struct entity_list *init_list(void);
void list_add_entity(struct entity_list *l, struct entity *e);
void list_foreach(struct entity_list *l, void (*f)(struct entity *));
void list_filter(struct entity_list *l, bool (*p)(struct entity *));
void destroy_list(struct entity_list *l);

#endif /* ifndef ENTITIES_H */
