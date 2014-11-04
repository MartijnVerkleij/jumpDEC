#include <wiringPi.h>
#include <SDL/SDL.h>
#include <pthread.h>
#include "levelLoaded.h"

void handleKeys();

int PIN_A = 14;	//wPi 15
int PIN_D = 15;	//wPi 16
int PIN_W = 3;	//wPi 9
int PIN_P = 2;	//wPi 8




void *keyboardHandler() {

	puts("Keyboard Live");
	int quit = 0;
	SDL_Event event;
	
	/* Set Pins to output */
	pinMode(PIN_A, OUTPUT);
	pinMode(PIN_D, OUTPUT);
	pinMode(PIN_W, OUTPUT);
	pinMode(PIN_P, OUTPUT);
		
	while(quit != 1 && SDL_WaitEvent(&event)){
		//puts("event called");
		switch( event.type ){
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			//puts("Handling keypress/release");
			handleKeys( &event.key );
			break;
		case SDL_QUIT:
			puts("Handling Quit Message");
			quit = 1;
			break;
		default:
			break;
		}
	}

	SDL_Quit();
	exit(0);
}

void handleKeys( SDL_KeyboardEvent *key ) {
	if(*SDL_GetKeyName( key->keysym.sym) == 'a') {
		if( key->type == SDL_KEYUP ){
			digitalWrite(PIN_A,0);
			printf("A keyup %d\n",digitalRead(PIN_A));
		}
		else{
			digitalWrite(PIN_A,1);
                        printf("A keydown %d\n",digitalRead(PIN_A));
		}
	} else if(*SDL_GetKeyName( key->keysym.sym) == 'd') {
		if( key->type == SDL_KEYUP ){
                        digitalWrite(PIN_D,0);
                        printf("D keyup %d\n",digitalRead(PIN_D));
                }
                else{
                        digitalWrite(PIN_D,1);
                        printf("D keydown %d\n",digitalRead(PIN_D));
                }
	} else if(*SDL_GetKeyName( key->keysym.sym) == 'w') {
		if( key->type == SDL_KEYUP ){
                        digitalWrite(PIN_W,0);
                        printf("W keyup %d\n",digitalRead(PIN_W));
                }
                else{
                        digitalWrite(PIN_W,1);
                        printf("W keydown %d\n",digitalRead(PIN_W));
                }
	} else if (*SDL_GetKeyName( key->keysym.sym) == 'p') {
		int pause = digitalRead(PIN_P);

		if( key->type == SDL_KEYUP ){
			/* flip pause between 0 and 1 */
                        if (pause) { pause = 0; } else { pause = 1; }
			digitalWrite(PIN_P,pause);
			printf("Pause: %d\n",digitalRead(PIN_P));
			
                }
	}
}
