#ifndef SPACEINVADERS_ENTITY_H
#define SPACEINVADERS_ENTITY_H

struct entity
{
    unsigned char symbol : 6; // ascii - 32
    unsigned char health : 2;
};

struct entity entCreateEmpty();

inline char entGetSymbol(struct entity ent);
inline void entSetSymbol(struct entity *this, char symbol);


#endif // SPACEINVADERS_ENTITY_H
