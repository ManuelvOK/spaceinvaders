#include <curses.h>
#include "../inc/board.h"
#include "../inc/entity.h"
#include "../inc/io.h"

#define WIDTH 64
#define HEIGHT 20

/* Spawns the a block of enemies.  */
void spawnEnemies(struct board *brd);

int main(void)
{
    struct board brd = brdCreate(WIDTH, HEIGHT);

    spawnEnemies(&brd);

    initCurses();

    brdDraw(&brd);
    getch();

    endCurses();
    brdFree(&brd);

    return 0;
}

void spawnEnemies(struct board *brd)
{
    int x, y;
    struct entity enemy = entCreateMonster();

    for (x = 0; x < 12; x++)
    {
        for (y = 0; y < 10; y++)
        {
            brdSet(brd, enemy, 4 * x + 4, y);
        }
    }
}