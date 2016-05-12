#ifndef GLOBALS_H
#define GLOBALS_H

// TODO: Replace macros with constants
#define WIDTH 30
#define HEIGHT 20
#define REFRESH_SPEED 100       // 100ms

enum
{
    KEY_MOVE_UP = 119,          // W
    KEY_MOVE_DOWN = 115,        // S
    KEY_MOVE_LEFT = 97,         // A
    KEY_MOVE_RIGHT = 100,       // D
    KEY_SHOOT = 32,             // SPACEBAR
    KEY_QUIT = 27               // ESCAPE FIXME: 'KEY_EXIT' doesn't work as name
};

#endif
