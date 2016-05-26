#include "../inc/entity.h"

struct entity entCreateEmpty()
{
    struct entity e;

    e.type = ETYPE_EMPTY;
    e.health = 0;

    return e;
}

struct entity entCreateMonster()
{
    struct entity e;

    e.type = ETYPE_MONSTER;
    e.health = 1;

    return e;
}