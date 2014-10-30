#include <SDL/SDL.h>
#include <pthread.h>
#include "init.c"
#include "keyboardHandler.c"
#include "inputHandler.c"

extern void *init(char *);
extern void *keyboardHandler();
extern void *inputHandler();

pthread_t keyboardThread;
pthread_t inputThread;

int main( int argc, char *argv[] ) {
	
	init("The Endgame");
	int targ = 0;
	pthread_create(&keyboardThread, NULL, &keyboardHandler, &targ);
	pthread_create(&inputThread, NULL, &inputHandler, &targ);
	while(1){
		puts("====Tick====");
		SDL_Delay((Uint32) 1000/60);
	}

}

