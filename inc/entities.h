#ifndef ENTITIES_H
#define ENTITIES_H

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
    int valid;
};

struct entity_list {
    struct entity *first;
    unsigned length;
};

#endif /* ifndef ENTITIES_H */
