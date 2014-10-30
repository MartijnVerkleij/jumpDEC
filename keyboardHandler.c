#include <wiringPi.h>
#include <SDL/SDL.h>
#include <pthread.h>

void handleKeys();

int PIN_A = 15;
int PIN_D = 9;
int PIN_W = 8;
int PIN_P = 16;




void *keyboardHandler() {

	int quit = 0;
	SDL_Event event;
	wiringPiSetup();
	
	/* Set Pins to output */
	pinMode(PIN_A, OUTPUT);
	pinMode(PIN_D, OUTPUT);
	pinMode(PIN_W, OUTPUT);
	pinMode(PIN_P, OUTPUT);
	
	while(SDL_WaitEvent(&event) && quit != 1){
		switch( event.type ){
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			handleKeys( &event.key );
			break;
		case SDL_QUIT:
			quit = 1;
			break;
		default:
			break;
		}
	}
}

void handleKeys( SDL_KeyboardEvent *key ) {
	if(*SDL_GetKeyName( key->keysym.sym) == 'a') {
		if( key->type == SDL_KEYUP ){
			digitalWrite(PIN_A,1);
		}
		else{
			digitalWrite(PIN_A,0);
		}
	} else if(*SDL_GetKeyName( key->keysym.sym) == 'd') {
		if( key->type == SDL_KEYUP ){
                        digitalWrite(PIN_D,1);
                }
                else{
                        digitalWrite(PIN_D,0);
                }
	} else if(*SDL_GetKeyName( key->keysym.sym) == 'w') {
		if( key->type == SDL_KEYUP ){
                        digitalWrite(PIN_W,1);
                }
                else{
                        digitalWrite(PIN_W,0);
                }
	} else if (*SDL_GetKeyName( key->keysym.sym) == 'p') {
		int pause = digitalRead(PIN_P);

		if( key->type == SDL_KEYUP ){
			/* flip pause between 0 and 1 */
                        if (pause) { pause = 0; } else { pause = 1; }
			digitalWrite(PIN_P,pause);
			
                }
	}
}
