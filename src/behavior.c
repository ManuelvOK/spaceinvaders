#include <stdlib.h>
#include "../inc/behavior.h"
#include "../inc/globals.h"

struct space *globalSpace = NULL;

// Initialises and sets up the global space.
void setupSpace()
{
    globalSpace = newSpace(WIDTH, HEIGHT);
    
    struct entity player = newEntity(PLAYER, 'P', 1);
    struct entity invader = newEntity(INVADER, 'Y', 1);
    setPlayer(globalSpace, getPos((unsigned char)(WIDTH / 2), HEIGHT - 1), player);

    for (unsigned char x = 0; x < globalSpace->width; x++)
    {
        setEntity(globalSpace, getPos(x, 1), invader);
    }
    // TODO: Add more invaders, blocks
}

// Returns the global space variable.
struct space *getSpace()
{
    return globalSpace;
}

// Wrapper for moving the player of the global space horizontally.
void movePlayer(unsigned char deltaX)
{
    moveEntity(globalSpace, getPlayerPos(globalSpace), getPos(deltaX, 0));
}

// Spawns a laser in front of the player of the global space.
void spawnPlayerLaser()
{
    struct entity laser = newEntity(LASER, '\'', 1);
    struct pos spawnPos = getPlayerPos(globalSpace);
    spawnPos.y--;

    setEntity(globalSpace, spawnPos, laser);
}

// Moves all lasers up, damaging every entity they collide with.
void updateLasers()
{
    struct entity deadEntity = newEntity(INVADER, '.', 0);

    for (unsigned char y = 0; y < globalSpace->height; y++)
    {
        for (unsigned char x = 0; x < globalSpace->width; x++)
        {
            struct entity current = getEntity(globalSpace, getPos(x, y));

            if (current.type == LASER)
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
                        entityAbove.health--;
                        setEntity(globalSpace, getPos(x, y - 1), entityAbove);
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
