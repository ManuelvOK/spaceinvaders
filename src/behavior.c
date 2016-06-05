#include <stdlib.h>
#include "../inc/behavior.h"
#include "../inc/globals.h"

struct space *globalSpace = NULL;

// Initialises and sets up the global space.
void setupSpace()
{
    globalSpace = newSpace(P_WIDTH, P_HEIGHT);
    
    struct entity player = newEntity(T_PLAYER, 'P', 1);
    struct entity invader = newEntity(T_INVADER, 'Y', 1);
    struct entity block = newEntity(T_BLOCK, '#', 3);
    setPlayer(globalSpace, getPos((unsigned char)(P_WIDTH / 2), P_HEIGHT - 1), player);

    for (unsigned char x = 0; x < globalSpace->width; x++)
    {
        setEntity(globalSpace, getPos(x, 1), invader);
    }

    for (unsigned char x = 12; x < 17; x++)
    {
        setEntity(globalSpace, getPos(x, 3), block);
    }
    // TODO: Add more invaders, blocks
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
    struct entity laser = newEntity(T_LASER, '\'', 1);
    struct pos spawnPos = getPlayerPos(globalSpace);
    spawnPos.y--;

    setEntity(globalSpace, spawnPos, laser);
}

// Moves all lasers up, damaging every entity they collide with.
void updateLasers()
{
    struct entity deadEntity = newEntity(T_INVADER, '.', 0);

    for (unsigned char y = 0; y < globalSpace->height; y++)
    {
        for (unsigned char x = 0; x < globalSpace->width; x++)
        {
            struct entity current = getEntity(globalSpace, getPos(x, y));

            if (current.type == T_LASER)
            {
                // Laser despawns at upper edge of space
                if (y == 0)
                {
                    setEntity(globalSpace, getPos(x, y), deadEntity);
                }
                // Move and collide
                else
                {
                    struct entity entityAbove = getEntity(globalSpace, getPos(x, y - 1));

                    if (entityAbove.health > 0)
                    {
                        setEntity(globalSpace, getPos(x, y - 1), damageEntity(entityAbove, 1));
                        setEntity(globalSpace, getPos(x, y), deadEntity);
                    }
                    else
                    {
                        setEntity(globalSpace, getPos(x, y - 1), current);
                        setEntity(globalSpace, getPos(x, y), deadEntity);
                    }
                }
            }
        }
    }
}
