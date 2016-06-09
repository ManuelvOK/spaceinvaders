#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include "space.h"

void terminate(char *message);
void startVisuals();
void stopVisuals();
void drawSpacePadding(struct space *space);
void drawSpace(struct space *space);
bool handleInput();
void saveSpaceToFile(struct space *space);
struct space *loadSpaceFromFile();

#endif
