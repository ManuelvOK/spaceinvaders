#ifndef IO_H
#define IO_H

void display_init();
void display_tidy();
void draw_board(void);
void set_char_at(int x, int y, char c);

int get_direction();

#endif /* IO_H */
