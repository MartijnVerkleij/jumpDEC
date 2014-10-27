#include <SDL/SDL.h>

    /* Function Prototypes */
    void PrintKeyInfo( SDL_KeyboardEvent *key );
    void PrintModifiers( SDLMod mod );

    /* main */
    int main( int argc, char *argv[] ){

        SDL_Event event;
        int quit = 0;

        /* Initialise SDL */
        if( SDL_Init( SDL_INIT_VIDEO ) < 0){
            fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
            exit( -1 );
        }

        /* Set a video mode */
        if( !SDL_SetVideoMode( 320, 200, 0, 0 ) ){
            fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
            SDL_Quit();
            exit( -1 );
        }

        /* Enable Unicode translation */
        SDL_EnableUNICODE( 1 );

        /* Loop until an SDL_QUIT event is found */
        while( !quit ){

            /* Poll for events */
            while( SDL_PollEvent( &event ) ){

            switch( event.type ){
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    PrintKeyInfo( &event.key );
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;

                default:
                    break;
                }
            }

        }

        /* Clean up */
        SDL_Quit();
        exit( 0 );
    }
    /* Print all information about a key event */
    void PrintKeyInfo( SDL_KeyboardEvent *key ){
        if(*SDL_GetKeyName( key->keysym.sym) == 'a' ||
           *SDL_GetKeyName( key->keysym.sym) == 'd'){
                if( key->type == SDL_KEYUP )
                    printf( "Up: " );
                else
                    printf( "Down: " );
                printf("%s", SDL_GetKeyName( key->keysym.sym ));
                printf( "\n" );
        }else if(*SDL_GetKeyName( key->keysym.sym) == 'w'){
                printf("JUMP");
                printf( "\n" );
        }
    }



