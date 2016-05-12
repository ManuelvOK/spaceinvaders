#include <time.h>
#include <assert.h>

#include <globals.h>
#include <io.h>
#include <class.h>
#include <entity.h>
#include <player.h>
#include <barrier.h>
#include <fighter.h>

/// delay function by Vilhelm Gray on http://stackoverflow.com/questions/3930363/implement-time-delay-in-c
// todo: replace by less cpu power consuming function
void delay(double dly){
    /* save start clock tick */
    const clock_t start = clock();

    clock_t current;
    do{
        /* get current clock tick */
        current = clock();

        /* break loop when the requested number of seconds have elapsed */
    }while((double)(current-start)/CLOCKS_PER_SEC < dly);
}


int main(void) {
    init_display();
    init_player_class();
    init_barrier_class();
    init_fighter_class();
    
    //place barriers
    int x,y;
    int barriertemplate[3][7] = {{0,0,1,1,1,0,0},{0,1,0,0,0,1,0},{0,1,0,0,0,1,0}};
    for (x = 1; x < WIDTH; ++x) {
        for (y = 0; y < 3; ++y) {
            if (barriertemplate[y][x%7]) {
                struct object *barrier = create_from(barrier_class);
                call(barrier, GOTO, (float)x, (float)y+HEIGHT-6);
            }
        }
    }
    //insert fighter
    for (x = 1; x < WIDTH; ++x) {
        for (y = 0; y < 3; ++y) {
            if (!(x%3)) {
                struct object *fighter = create_from(fighter_class);
                call(fighter, GOTO, (float)x, (float)y*3+2);
            }
        }
    }
    
    struct object *player = create_from(player_class);
    
    // main loop
    int control = STAY;
    while (!(control & QUIT)) {
        update_entities();
        control = get_input();
        call(player,CONTROL,control);
        draw_board();
        delay(0.02);
    }
    // tidy screen
    delete_object(player); // todo: delete all entities
    tidy_display();
    return 0;
}
