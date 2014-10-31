#include <SDL/SDL.h>
#include "graphics.h"

//SDL_Surface *screen

void *init(char *title) {
	/* Initialise SDL */
        if( SDL_Init( SDL_INIT_VIDEO ) < 0){
            fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
            exit( -1 );
        }

        /* Set a video mode */
	screen = SDL_SetVideoMode( 1200, 1000, 0, 0 );
        if( !screen){
            fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
            SDL_Quit();
            exit( -1 );
        }

        /* Enable Unicode translation */
        SDL_EnableUNICODE( 1 );

	SDL_WM_SetCaption(title, NULL);
	

	int i;
	for (i = 23; i >= 0; i--) {
		char str[20];
		switch(i) {
		case 6:
			break;
		case 16:
			break;
		default:
			snprintf(str, sizeof(str), "%s%d%s", 
				"gpio export ", i, " out");
			system(str);
			puts(str);
			break;
		}
	}
	wiringPiSetupSys();
	puts("setup done\n");
}
