#include <SDL/SDL.h>
#include <pthread.h>
#include "init.c"
#include "keyboardHandler.c"
#include "inputHandler.c"
#include "graphics.c"
//#include "game.h"

extern void *init(char *);
extern void *keyboardHandler();
extern void *inputHandler();
extern void *render(struct game *);
extern void *renderInit(struct game *);


pthread_t keyboardThread;
pthread_t inputThread;

struct game game;

int main( int argc, char *argv[] ) {
	
	init("The Endgame");
	int targ = 0;
	pthread_create(&keyboardThread, NULL, &keyboardHandler, &game);
	pthread_create(&inputThread, NULL, &inputHandler, &game);

	game.blockCount = 2;
	game.blocks[1].x = 50;
        game.blocks[1].y = 50;
        game.blocks[2].x = 150;
        game.blocks[2].y = 150;
	game.player.x = 200;
	game.player.y = 200;
	
	renderInit(&game);
	
	while(1){
		// Start frame
		long long frame = (long long) SDL_GetTicks();
		
		render(&game);

		game.player.x += 1;
		game.player.y += 1;

		/* ================== */
		/* FRAME FINALIZATION */
		/* ================== */
		long long time_to_spare = 1000/30 - (SDL_GetTicks() - frame);
		//Uint32 wait = 100;
		Uint32 wait = (time_to_spare > 0) ? (Uint32) time_to_spare : 0 ; 
		//printf("Time to Spare: %d\n", wait);
		SDL_Delay(wait); // wait until this loop has taken 1/60 second.
	}

}
