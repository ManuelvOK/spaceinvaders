#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>

enum entityType
{
    T_INVADER = 0,
    T_BLOCK = 1,
    T_LASER = 2,
    T_PLAYER = 3,
};

struct entity
{
    unsigned type : 2;
    unsigned symbol : 7;
    unsigned health : 3;
    unsigned canFire : 1;   // Whether invader can fire
    unsigned moveUp : 1;    // Whether lasers shall move up
    unsigned flag3 : 1;     // Flag names are placeholders
    unsigned flag4 : 1;
};

struct pos
{
    signed char x;
    signed char y;
};

struct entity newEntity(unsigned type, unsigned char symbol, unsigned health);
struct pos getPos(signed char x, signed char y);
bool posEquals(struct pos coords1, struct pos coords2);
struct entity damageEntity(struct entity entity, unsigned char damage);

#endif
