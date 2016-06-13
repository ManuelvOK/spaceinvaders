#ifndef GLOBAL_SPACE_H
#define GLOBAL_SPACE_H

#include "spaceCore.h"

void setupSpace();
struct space *getSpace();
void setSpace(struct space *space);
void movePlayer(unsigned char deltaX);
void spawnPlayerLaser();

#endif
