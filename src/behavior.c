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
    // TODO: Add more invaders, blocks

    updateCanFire();
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
    struct pos currentPos;

    for (signed char y = 0; y < globalSpace->height; y++)
    {
        currentPos.y = y;

        for (signed char x = 0; x < globalSpace->width; x++)
        {
            currentPos.x = x;
            struct entity current = getEntity(globalSpace, currentPos);

            if (current.type == T_LASER)
            {
                // Laser despawns at upper edge of space
                if (y == 0)
                {
                    setEntity(globalSpace, currentPos, deadEntity);
                }
                // Move and collide
                else
                {
                    struct entity entityAbove = getEntity(globalSpace, getPos(x, y - 1));

                    if (entityAbove.health > 0)
                    {
                        setEntity(globalSpace, getPos(x, y - 1), damageEntity(entityAbove, 1));
                        setEntity(globalSpace, currentPos, deadEntity);
                        updateCanFire();
                    }
                    else
                    {
                        setEntity(globalSpace, getPos(x, y - 1), current);
                        setEntity(globalSpace, currentPos, deadEntity);
                    }
                }
            }
        }
    }
}

// Updates canFire flag for all entities.
void updateCanFire()
{
    struct entity entity;
    struct pos lowestInvaderPos = { -1, -1 };
    struct pos currentPos;

    for (signed char x = 0; x < globalSpace->width; x++)
    {
        currentPos.x = x;

        for (signed char y = 0; y < globalSpace->height; y++)
        {
            currentPos.y = y;

            // Disable canFire for all entities
            entity = getEntity(globalSpace, currentPos);
            entity.canFire = 0;
            setEntity(globalSpace, currentPos, entity);

            // Save lowest invader position
            if (entity.health > 0 && entity.type == T_INVADER)
            {
                lowestInvaderPos = currentPos;
            }
        }

        // Enable canFire for lowest invader if possible
        if (lowestInvaderPos.x >= 0 && lowestInvaderPos.y >= 0)
        {
            entity = getEntity(globalSpace, lowestInvaderPos);
            entity.canFire = 1;
            setEntity(globalSpace, lowestInvaderPos, entity);
        }
    }
}
