#include <SDL/SDL.h>
#include <pthread.h>
#include "init.c"
#include "keyboardHandler.c"
#include "inputHandler.c"
#include "graphics.c"

extern void *init(char *);
extern void *keyboardHandler();
extern void *inputHandler();
extern void *renderInit();


pthread_t keyboardThread;
pthread_t inputThread;

int main( int argc, char *argv[] ) {
	
	init("The Endgame");
	int targ = 0;
//	Game game;
	pthread_create(&keyboardThread, NULL, &keyboardHandler, &targ);
	pthread_create(&inputThread, NULL, &inputHandler, &targ);
	while(1){
		// Start frame
		Uint32 frame = SDL_GetTicks();
		
		render()
		
		/* ================== */
		/* FRAME FINALIZATION */
		/* ================== */
		Uint32 time_to_spare =(Uint32) 1000/60 - 
						(SDL_GetTicks() - frame);
		Uint32 wait = time_to_spare < 0 ? time_to_spare : 0 ; 
		SDL_Delay(wait); // wait until this loop has taken 1/60 second.
		printf("Time to Spare: %d\n", time_to_spare);
	}

}
