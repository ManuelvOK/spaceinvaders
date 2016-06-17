#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>

enum params
{
    P_WIDTH = 30,           // width of space
    P_HEIGHT = 20,          // height of space
    P_REFRESH_SPEED = 100,  // 100ms
    P_PADDING = 1,          // width of padding
    P_NO_ENTITY_CHAR = '.', // char for no entity
    P_OUTLINE_CHAR_V = '|', // char for vertical outline
    P_OUTLINE_CHAR_H = '=', // char for horizontal outline
    P_ATTACK_CHANCE = 10,   // chance in % of invader attack
};

enum keyInput
{
    K_MOVE_LEFT = 97,       // a
    K_MOVE_LEFT_ALT = 65,   // A
    K_MOVE_RIGHT = 100,     // d
    K_MOVE_RIGHT_ALT = 68,  // D
    K_SHOOT = 32,           // spacebar
    K_SHOOT_ALT = 32,       // spacebar
    K_EXIT = 27,            // escape
    K_EXIT_ALT = 27,        // escape
    K_SAVE = 121,           // y
    K_SAVE_ALT = 89,        // Y
    K_LOAD = 120,           // x
    K_LOAD_ALT = 88,        // X
};

#endif
