#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "entity.h"
#include "space.h"

void setupSpace();
struct space *getSpace();
void movePlayer(unsigned char deltaX);
void spawnPlayerLaser();
void updateLasers();
void moveInvaders();

#endif
