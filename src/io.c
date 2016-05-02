#include <stdio.h>
#include <ncurses.h>

#include <io.h>
#include <globals.h>

#include <assert.h>

// This File contains a lot of things that have to be done with ncurses instead

WINDOW *menu_win;

void init_display() {
    initscr();
    noecho();
    cbreak();   /* Line buffering disabled. pass on everything */
    curs_set(0);
    
    keypad(stdscr, TRUE);
    timeout(0);
}
void tidy_display() {
    endwin();
}

void draw_board(void){
    refresh();
}

void set_char_at(int x, int y, char c) {
    mvprintw(y,x,"%c",c);
}

int get_input() {
    int c;
    c = getch();
    while (getch() != -1); // restliche Eingaben verwerfen

    switch (c) {
        case KEY_UP:   return UP;
        case KEY_DOWN: return DOWN;
        case KEY_RIGHT:return RIGHT;
        case KEY_LEFT: return LEFT;
        case ' ':      return FIRE;
        case 27:       return QUIT;
        default:       return STAY;
    }
}
