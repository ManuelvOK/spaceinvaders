#ifndef SAVESTATE_H
#define SAVESTATE_H

#include <game.h>
#include <stdbool.h>
#include <stdio.h>

bool read_savestate(FILE *savestate, struct game_state *state);

bool write_savestate(FILE *savestate, const struct game_state *state);

#endif /* ifndef SAVESTATE_H */
