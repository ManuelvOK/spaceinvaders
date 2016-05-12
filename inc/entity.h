#ifndef SPACEINVADERS_ENTITY_H
#define SPACEINVADERS_ENTITY_H

/* Represents an entity of the game (pixel, monster, player, etc...).
 *
 * If you want to access the ascii symbol of the entity, use entGetSymbol() and
 * entSetSymbol() instead of accessing ent.symbol directly.
 *
 * You can only store ascii values 32 through 95 including
 * (includes capital letters, numbers, space and a few symbols).
 */
struct entity
{
    unsigned char symbol : 6;
    unsigned char health : 2;
};

/* creates a new empty entity */
struct entity entCreateEmpty();

/* checks if en entity is empty */
inline int entIsEmpty(struct entity ent);

/* returns the symbol of an entity */
inline char entGetSymbol(struct entity ent);

/* sets the symbol of an entity */
inline void entSetSymbol(struct entity *this, char symbol);

#endif // SPACEINVADERS_ENTITY_H
