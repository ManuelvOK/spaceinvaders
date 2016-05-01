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
    
    menu_win = newwin(HEIGHT, WIDTH, 0, 0);
    keypad(menu_win, TRUE);
    wtimeout(menu_win,0);
}
void tidy_display() {
    endwin();
}

void draw_board(void){
    wrefresh(menu_win);
}

void set_char_at(int x, int y, char c) {
    mvwprintw(menu_win,y,x,"%c",c);
}

int get_input() {
    int c;
    c = wgetch(menu_win);
    while (wgetch(menu_win) != -1);

    switch (c) {
        case KEY_UP:   return UP;
        case KEY_DOWN: return DOWN;
        case KEY_RIGHT:return RIGHT;
        case KEY_LEFT: return LEFT;
        case ' ':      return FIRE;
        default:       return STAY;
    }
}
