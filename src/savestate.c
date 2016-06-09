#include <stdio.h>
#include <errno.h>

#include "../inc/savestate.h"

bool read_savestate(FILE *savestate, struct game_state *state) {
   savestate = fopen("~/.spaceinvaders/savestate", "r");
   if (savestate == NULL && errno == ENOENT) {
      return false;
   }
   
   struct entity_list *players = malloc(sizeof players);
   struct entity_list *walls = malloc(sizeof walls);
   struct entity_list *lasers = malloc(sizeof lasers);
   struct entity_list **fighters = malloc(sizeof fighters);
   struct board *the_board = malloc(sizeof the_board);
   struct entity *ent_buffer = malloc(sizeof ent_buffer);


   if (players == NULL
      || walls == NULL
      || lasers == NULL
      || fighters == NULL
      || the_board == NULL
      || ent_buffer == NULL) {
      return false;
   }
      /* reserve much memory for players who saved a hudge score */
   char buffer[512];
   while ((buffer = fgets(buffer, 512)) != NULL) {
      switch (buffer[0]) {
         case 'B':   /* BOARD */
            break;
         case 'P':   /* PLAYER */
            break;
         case 'W':   /* WALL */
            break;
         case 'F':   /* FIGHTER */
            break;
         case 'L':   /* LASER */
            break;
      }
   }
   
   fclose(savestate);
   return false;
}
