#ifndef ENTITY_H
#define ENTITY_H

#define INVADER 0
#define BLOCK 1
#define LASER 2
#define PLAYER 3

#include <stdbool.h>

struct entity
{
    unsigned type : 2;
    unsigned symbol : 7;
    unsigned health : 3;
    unsigned flag1 : 1;     // Flag names are placeholders
    unsigned flag2 : 1;
    unsigned flag3 : 1;
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
