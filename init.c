#include <SDL/SDL.h>


void *init(char *title) {
	/* Initialise SDL */
        if( SDL_Init( SDL_INIT_VIDEO ) < 0){
            fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
            exit( -1 );
        }

        /* Set a video mode */
        if( !SDL_SetVideoMode( 1200, 1000, 0, 0 ) ){
            fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
            SDL_Quit();
            exit( -1 );
        }

        /* Enable Unicode translation */
        SDL_EnableUNICODE( 1 );

	SDL_WM_SetCaption(title, NULL);
	
	
	system("for i in {0..15}; do gpio edge $i both; done");
	wiringPiSetupSys();
	puts("setup done\n");
}
