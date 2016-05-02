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
    int control = STAY;
    while ((c = getch()) != -1) {
        switch (c) {
            case KEY_UP:   control |= UP   ; break;
            case KEY_DOWN: control |= DOWN ; break;
            case KEY_RIGHT:control |= RIGHT; break;
            case KEY_LEFT: control |= LEFT ; break;
            case ' ':      control |= FIRE ; break;
            case 27:       control |= QUIT ; break;
        }
    }
    return control;
}
