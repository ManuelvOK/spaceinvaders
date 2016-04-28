#include <time.h>

#include <io.h>
#include <player.h>
#include <entity.h>

/// delay function by Vilhelm Gray on http://stackoverflow.com/questions/3930363/implement-time-delay-in-c
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
    display_init();
    
    struct entity *player = create_player();
    
    while (1) {
        update(player);
        move(player,get_direction());
        draw_board();
        delay(0.02);
    }
    delete_entity(player);
    display_tidy();
    return 0;
}
