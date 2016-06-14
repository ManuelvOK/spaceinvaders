#include <ncurses.h>
#include "../inc/entity.h"
#include "../inc/io.h"
#include "../inc/globals.h"
#include "../inc/globalSpace.h"
#include "../inc/spaceCore.h"
#include "../inc/spaceExtra.h"

int main()
{
    startVisuals();
    setupSpace();
    drawSpacePadding(getSpace());
    initRandom();

    while (true)
    {
        if (!handleInput())
        {
            break;
        }

        randomInvaderAttack(getSpace());
        drawSpace(getSpace());
        napms(P_REFRESH_SPEED);
        updateLasers(getSpace());
    }

    stopVisuals();
    return 0;
}
