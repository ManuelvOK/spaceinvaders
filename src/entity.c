#include "../inc/entity.h"



struct entity entCreateEmpty()
{
    struct entity e;

    e.symbol = 0;
    e.health = 0;

    return e;
}

inline int entIsEmpty(struct entity ent)
{
    union
    {
        struct entity ent;
        unsigned char chr;
    } u;

    u.ent = ent;

    return u.chr == 0;
}

inline char entGetSymbol(struct entity ent)
{
    return ent.symbol + 32;
}

inline void entSetSymbol(struct entity *this, char symbol)
{
    this->symbol = symbol - 32;
}