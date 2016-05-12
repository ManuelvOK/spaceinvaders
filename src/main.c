// TODO: Breite und Hoehe automatisch auslesen (statt hard zu coden)
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/board.h"
#include "../inc/entity.h"
#include "../inc/io.h"

#define WIDTH 64
#define HEIGHT 32

int main(void)
{
    struct board brd = brdCreate(WIDTH, HEIGHT);
    struct entity ent = entCreateEmpty();

    entSetSymbol(&ent, 'X');
    brdSet(&brd, ent, 2, 5);

    initCurses();
    brdDraw(&brd);
    getch();
    endCurses();

    brdFree(&brd);

    return 0;
}
