#include <stdlib.h>
#include "../inc/entity.h"
#include "../inc/globals.h"
#include "../inc/globalSpace.h"
#include "../inc/spaceExtra.h"

struct space *globalSpace = NULL;

// Initialises and sets up the global space.
void setupSpace()
{
    globalSpace = newSpace(P_WIDTH, P_HEIGHT);

    struct entity player = newEntity(T_PLAYER, 'P', 1);
    struct entity invader = newEntity(T_INVADER, 'Y', 1);
    struct entity block = newEntity(T_BLOCK, '#', 3);
    setPlayer(globalSpace, getPos((unsigned char)(P_WIDTH / 2), P_HEIGHT - 1), player);

    for (unsigned char x = 1; x < globalSpace->width - 1; x++)
    {
        setEntity(globalSpace, getPos(x, 1), invader);
        setEntity(globalSpace, getPos(x, 3), invader);
        setEntity(globalSpace, getPos(x, 5), invader);
    }

    for (unsigned char x = 12; x < 17; x++)
    {
        setEntity(globalSpace, getPos(x, 9), block);
    }

    for (unsigned char x = 0; x < globalSpace->width; x++)
    {
        setEntity(globalSpace, getPos(x, 15), block);
        setEntity(globalSpace, getPos(x, 16), block);
    }

    spawnLaser(globalSpace, getPos(0, 0), 0);
    // TODO: Add more invaders, blocks

    updateCanFire(globalSpace);
}

// Returns the global space variable.
struct space *getSpace()
{
    return globalSpace;
}

// Sets the gobal space variable.
void setSpace(struct space *space)
{
    globalSpace = space;
}

// Wrapper for moving the player of the global space horizontally.
void movePlayer(unsigned char deltaX)
{
    moveEntity(globalSpace, getPlayerPos(globalSpace), getPos(deltaX, 0));
}

// Spawns a laser in front of the player of the global space.
void spawnPlayerLaser()
{
    spawnLaser(globalSpace, getPlayerPos(globalSpace), 1);
}
