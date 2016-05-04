#define _BSD_SOURCE

#include <unistd.h>
#include "../inc/entity.h"
#include "../inc/io.h"
#include "../inc/globals.h"
#include "../inc/space.h"

int main()
{
    startVisuals();
    setupSpace();

    struct entity invader1 = newEntity(INVADER, '#', 1);
    struct entity invader2 = newEntity(INVADER, '~', 1);
    addEntity(1, 1,  invader1);
    addEntity(5, 2, invader2);

    while (true)
    {
        if (!handleInput())
        {
            break;
        }

        drawSpace(getSpace());
        usleep(REFRESH_SPEED);
    }

    stopVisuals();
    return 0;
}
