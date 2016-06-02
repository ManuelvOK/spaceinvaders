#include <curses.h>
#include "../inc/board.h"
#include "../inc/entity.h"
#include "../inc/io.h"

#define WIDTH 64
#define HEIGHT 20

/* Reads a game state from a file, that was written by writeGameState.
 * Returns the number of bytes read.
 *
 * NOTE: The board is created by brdCreate, so you wanna call brdFree when
 *       you're done.
 */
size_t readGameState(const char *filename, struct board *brd);

/* Saves the current game state to a file and returns the number of bytes
 * written. If something went wrong, 0 is returned.*/
size_t writeGameState(const char *filename, struct board *brd);

/* Spawns the a block of enemies. */
void spawnEnemies(struct board *brd);

int main(void)
{
    struct board brd;

    brd = brdCreate(WIDTH, HEIGHT);

    spawnEnemies(&brd);

    initCurses();

    brdDraw(&brd);
    getch();
    writeGameState("savegame", &brd);

    endCurses();
    brdFree(&brd);

    return 0;
}

size_t readGameState(const char *filename, struct board *brd)
{
    size_t total;
    FILE *file = fopen(filename, "r");

    if (file == NULL) return 0;

    total = brdRead(brd, file);

    fclose(file);

    return total;
}

size_t writeGameState(const char *filename, struct board *brd)
{
    size_t total;
    FILE *file = fopen(filename, "w+");

    if (file == NULL) return 0;

    total = brdWrite(brd, file);

    fclose(file);

    return total;
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