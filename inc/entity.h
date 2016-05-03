#ifndef ENTITY_H
#define ENTITY_H

struct entity
{
    unsigned x;
    unsigned y;
    unsigned health;
    int symbol;
};

struct entity * newEntity(unsigned x, unsigned y, unsigned health, int symbol);
void setupPlayer();
struct entity *getPlayer();
void moveEntity(struct entity *entity, int deltaX, int deltaY);

#endif
