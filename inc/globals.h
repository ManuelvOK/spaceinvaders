enum {
    // IO Stuff
    WIDTH = 80,
    HEIGHT = 24,
    
    // Controls/Directions
    STAY = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 4,
    RIGHT = 8,
    FIRE = 16,
    QUIT = 32,
    
    // Entity methods/attributes
    SYMBOL,
    X,Y,
    DX,DY,
    HEADING,
    HEALTH,
    COUNTER,
    UPDATE,         // ()
    MOVE,           // (direction)
    GOTO,           // (x,y)
    CONTROL,        // (control)
    ON_COLLIDE,     // (other object, x, y)
    };
