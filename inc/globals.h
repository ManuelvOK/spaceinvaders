#ifndef GLOBALS_H
#define GLOBALS_H

enum params
{
    P_WIDTH = 30,
    P_HEIGHT = 20,
    P_REFRESH_SPEED = 100,  // 100ms
};

enum keyInput
{
    K_MOVE_LEFT = 97,       // a
    K_MOVE_LEFT_ALT = 65,   // A
    K_MOVE_RIGHT = 100,     // d
    K_MOVE_RIGHT_ALT = 68,  // D
    K_SHOOT = 32,           // SPACEBAR
    K_SHOOT_ALT = 32,       // SPACEBAR
    K_EXIT = 27,            // ESCAPE
    K_EXIT_ALT = 27,        // ESCAPE
    K_SAVE = 121,           // y
    K_SAVE_ALT = 89,        // Y
    K_LOAD = 120,           // x
    K_LOAD_ALT = 88,        // X
};

#endif
