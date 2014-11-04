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
	screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWPALETTE|SDL_DOUBLEBUF );
        if( !screen){
            fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
            SDL_Quit();
            exit( -1 );
        }

        /* Enable Unicode translation */
        SDL_EnableUNICODE( 1 );

	SDL_WM_SetCaption(title, NULL);
	

	int i;
	for (i = 27; i >= 0; i--) {
		char str[20];
		switch(i) {
		case 6:
		case 21:
		case 20:
		case 19:
		case 26:	
		case 16:
			break;
		case 17:
		case 4:
		case 2:
		case 3:
		case 14:
		case 15:
			snprintf(str, sizeof(str), "%s%d%s",
                                "gpio export ", i, " out");
                        system(str);
                        puts(str);
                        break;
		default:
			snprintf(str, sizeof(str), "%s%d%s", 
				"gpio export ", i, " in");
			system(str);
			puts(str);
			break;
		}
	}
	wiringPiSetupSys();
	puts("setup done\n");
}
