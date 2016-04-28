#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

struct coord
{
    int x;
    int y;
};

struct entity
{
    struct coord pos;
    int health;
    int symbol;
};

struct entity * newEntity(int xPos, int yPos, int health, int symbol);

#endif
