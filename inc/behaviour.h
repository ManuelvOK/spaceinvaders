#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "entity.h"
#include "space.h"

void setupSpace();
struct space *getSpace();
void movePlayer(unsigned char deltaX);
void spawnLaser(struct pos coords, unsigned moveUp);
void spawnPlayerLaser();
void updateLasers();
void moveInvaders();
void setSpace(struct space *space);
void updateCanFire();
void invadersRandomAttack();

#endif
