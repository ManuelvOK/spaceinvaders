#ifndef STRUCTURES_H
#define STRUCTURES_H

struct entity {
    char symbol;
    int health;
    int x;
    int y;
};

struct fighter {
    struct entity data;
    struct fighter *next;
    struct fighter *prev;
};

struct fighter_row {
    struct fighter *first;
    struct fighter *last;
    struct fighter_row *next_row;
    struct fighter_row *prev_row;

};

struct fleet {
    struct fighter_row *first;
    struct fighter_row *last;
};

#endif /* STRUCTURES_H */
