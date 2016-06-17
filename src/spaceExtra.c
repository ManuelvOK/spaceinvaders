#include <stdlib.h>
#include <time.h>
#include "../inc/globals.h"
#include "../inc/spaceExtra.h"

// Spawns a laser on a space at given coordinates.
void spawnLaser(struct space *space, struct pos coords, unsigned moveUp)
{
    struct entity laser = newEntity(T_LASER, '\'', 1);
    laser.moveUp = moveUp % 2;
    coords.y += (laser.moveUp * (-2)) + 1;

    setEntity(space, coords, laser);
}

// Moves all lasers of a space, damaging every entity they collide with.
void updateLasers(struct space *space)
{
    struct entity deadEntity = newEntity(T_INVADER, '.', 0);
    struct entity current;
    struct entity nextEntity;
    struct pos currentPos;
    struct pos nextPos;
    unsigned char *updated = calloc(space->width * space->height, sizeof *updated);

    for (signed char y = 0; y < space->height; y++)
    {
        currentPos.y = y;

        for (signed char x = 0; x < space->width; x++)
        {
            currentPos.x = x;
            current = getEntity(space, currentPos);

            if (current.type == T_LASER && !updated[y * space->width + x])
            {
                if (current.moveUp)
                {
                    nextPos = getPos(x, y - 1);
                }
                else
                {
                    nextPos = getPos(x, y + 1);
                }

                // Laser despawns at upper / lower edge
                if (spaceOutOfBounds(space, nextPos))
                {
                    setEntity(space, currentPos, deadEntity);
                }
                // Move to next position
                else
                {
                    nextEntity = getEntity(space, nextPos);

                    if (nextEntity.health > 0)
                    {
                        setEntity(space, nextPos, damageEntity(nextEntity, 1));
                        setEntity(space, currentPos, deadEntity);
                        updateCanFire(space);
                    }
                    else
                    {
                        setEntity(space, nextPos, current);
                        setEntity(space, currentPos, deadEntity);
                        updated[nextPos.y * space->width + nextPos.x] = 1;
                    }
                }
            }
        }
    }
}

// Updates canFire flag for all entities of a space.
void updateCanFire(struct space *space)
{
    struct entity entity;
    struct pos lowestInvaderPos = { -1, -1 };
    struct pos currentPos;

    for (signed char x = 0; x < space->width; x++)
    {
        currentPos.x = x;

        for (signed char y = 0; y < space->height; y++)
        {
            currentPos.y = y;

            // Disable canFire for all entities
            entity = getEntity(space, currentPos);
            entity.canFire = 0;
            setEntity(space, currentPos, entity);

            // Save lowest invader position
            if (entity.health > 0 && entity.type == T_INVADER)
            {
                lowestInvaderPos = currentPos;
            }
        }

        // Enable canFire for lowest invader if possible
        if (lowestInvaderPos.x >= 0 && lowestInvaderPos.y >= 0)
        {
            entity = getEntity(space, lowestInvaderPos);
            entity.canFire = 1;
            setEntity(space, lowestInvaderPos, entity);
        }
    }
}

// Initialises the seed for random numbers.
void initRandom()
{
    srand(time(NULL));
}

// Makes a random invader of a space potentially shoot.
void randomInvaderAttack(struct space *space)
{
    // P_ATTACK_CHANCE % chance
    if (rand() % 100 < P_ATTACK_CHANCE)
    {
        struct pos coords;

        do
        {
            unsigned x = rand() % space->width;
            unsigned y = rand() % space->height;
            coords = (struct pos) { x, y };
        }
        while (!getEntity(space, coords).canFire);

        spawnLaser(space, coords, 0);
    }
}

/*
void moveInvaders(struct space *space, unsigned dir)
{
    struct pos currentPos;

    for (signed char y = 0; y < space->height; y++)
    {
        currentPos.y = y;

        for (signed char x = 0; x < space->width; x++)
        {
            currentPos.x = x;
        }
    }
}
*/
