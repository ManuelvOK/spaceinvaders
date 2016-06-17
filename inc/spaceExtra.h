#ifndef SPACE_EXTRA_H
#define SPACE_EXTRA_H

#include "entity.h"
#include "spaceCore.h"

void spawnLaser(struct space *space, struct pos coords, unsigned moveUp);
void updateLasers(struct space *space);
void updateCanFire(struct space *space);
void initRandom();
void randomInvaderAttack(struct space *space);
void moveInvaders(struct space *space);

#endif
