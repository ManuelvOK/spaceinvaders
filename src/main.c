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
    setupPlayer();

    struct entity *invader1 = newEntity(1, 1, 1, '#');
    struct entity *invader2 = newEntity(5, 2, 1, '~');
    addEntity(getSpace(), invader1);
    addEntity(getSpace(), invader2);

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
