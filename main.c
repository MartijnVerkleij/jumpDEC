#include <SDL/SDL.h>
#include <pthread.h>
#include "init.c"
#include "keyboardHandler.c"
#include "inputHandler.c"

extern void *init(char *);
extern void *keyboardHandler();
extern void *inputHandler();
int tick();

pthread_t keyboardThread;
pthread_t inputThread;

int main( int argc, char *argv[] ) {
	
	init("The Endgame");
	int targ = 0;
	Game game;
	pthread_create(&keyboardThread, NULL, &keyboardHandler, &targ);
	pthread_create(&inputThread, NULL, &inputHandler, &game);
	while(1){
		SDL_AddTimer(10, 


		puts("====Tick====");
		SDL_Delay((Uint32) 1000/60);
	}

}

int tick() {
	
}
