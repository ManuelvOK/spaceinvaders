#include <ncurses.h>
#include "../inc/behaviour.h"
#include "../inc/entity.h"
#include "../inc/io.h"
#include "../inc/globals.h"
#include "../inc/space.h"

int main()
{
    startVisuals();
    setupSpace();
    drawSpacePadding(getSpace());

    while (true)
    {
        if (!handleInput())
        {
            break;
        }

        drawSpace(getSpace());
        napms(P_REFRESH_SPEED);
        // invadersRandomAttack();
        updateLasers();
    }

    stopVisuals();
    return 0;
}
