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
    return ent.symbol == 0;
}

inline char entGetSymbol(struct entity ent)
{
    return ent.symbol + (char)32;
}

inline void entSetSymbol(struct entity *this, char symbol)
{
    this->symbol = symbol - (char)32;
}