#ifndef SPACEINVADERS_ENTITY_H
#define SPACEINVADERS_ENTITY_H

#define ETYPE_EMPTY 0
#define ETYPE_MONSTER 1
#define ETYPE_PLAYER 2
#define ETYPE_LASER 4

/* Represents an entity of the game (pixel, monster, player, etc...). */
struct entity
{
    unsigned char type : 4;
	unsigned char health : 4;
};

/* checks if en entity is empty */
static inline int entIsEmpty(struct entity ent)
{
	return ent.type == ETYPE_EMPTY;
}

/* creates a new empty entity */
struct entity entCreateEmpty();

/* creates a new monser */
struct entity entCreateMonster();

#endif // SPACEINVADERS_ENTITY_H
