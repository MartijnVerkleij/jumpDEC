#include <SDL/SDL.h>
#include <pthread.h>
#include "init.c"
#include "keyboardHandler.c"

extern void *init(char *);
extern void *keyboardHandler();

pthread_t keyboardThread;

int main( int argc, char *argv[] ) {
	
	init("The Endgame");
	int targ = 0;
	pthread_create(&keyboardThread, NULL, &keyboardHandler, &targ);
	
	while(1){
		poll(0,0,200);
	}

}

