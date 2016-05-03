#include "../inc/entity.h"

struct entity entGetEmpty()
{
    struct entity e;

    e.symbol = 0;
    e.health = 0;

    return e;
}