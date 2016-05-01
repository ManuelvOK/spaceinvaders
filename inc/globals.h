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
    
    // Entity methods/attributes
    SYMBOL,
    X,Y,
    HEADING,
    UPDATE,         // ()
    MOVE,           // (direction)
    GOTO,           // (x,y)
    CONTROL,        // (control)
    ON_COLLIDE,     // (other object, x, y)
    };
