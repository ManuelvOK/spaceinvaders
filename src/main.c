#include <unistd.h>
#include <ncurses.h>
#include "../inc/behavior.h"
#include "../inc/entity.h"
#include "../inc/io.h"
#include "../inc/globals.h"
#include "../inc/space.h"

int main()
{
    startVisuals();
    setupSpace();
    drawSpaceOutline(getSpace());

    while (true)
    {
        if (!handleInput())
        {
            break;
        }

        drawSpace(getSpace());
        napms(P_REFRESH_SPEED);
        updateLasers();
    }

    stopVisuals();
    return 0;
}
