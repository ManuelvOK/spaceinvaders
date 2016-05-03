#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include "entity.h"
#include "space.h"

void terminate();
void startVisuals();
void stopVisuals();
void drawSpace(struct space *space);
bool handleInput();

#endif
