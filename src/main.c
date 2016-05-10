#define _BSD_SOURCE

#include <unistd.h>
#include "../inc/behavior.h"
#include "../inc/entity.h"
#include "../inc/io.h"
#include "../inc/globals.h"
#include "../inc/space.h"

int main()
{
    startVisuals();
    setupSpace();

    while (true)
    {
        if (!handleInput())
        {
            break;
        }

        drawSpace(getSpace());
        usleep(REFRESH_SPEED);
        updateLasers();
    }

    stopVisuals();
    return 0;
}
