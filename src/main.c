#include <time.h>
#include <assert.h>

#include <globals.h>
#include <io.h>
#include <player.h>
#include <entity.h>
#include <class.h>

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
    init_display();
    init_player_class();
    
    struct object *player = create_from(player_class);
        
    int control = STAY;
    while (!(control & QUIT)) {
        update_entities();
        control = get_input();
        call(player,CONTROL,control);
        draw_board();
        delay(0.02);
    }
    delete_object(player);
    tidy_display();
    return 0;
}
