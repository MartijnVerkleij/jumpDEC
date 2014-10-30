#include <SDL/SDL.h>
    
    SDL_Surface *IMG_Load(char[]);
    SDL_Surface *screen;
        SDL_Rect dest;
    /* Function Prototypes */
    void PrintKeyInfo( SDL_KeyboardEvent *key );

    /* Function to load img*/
    SDL_Surface *LoadImg(char *name);

    void drawImage(SDL_Surface *image, int x, int y);

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
        screen = SDL_SetVideoMode( 600, 300, 0, SDL_HWPALETTE |                 SDL_DOUBLEBUF); 
        if( !screen){
            fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
            SDL_Quit();
            exit( -1 );
        }
	    SDL_WM_SetCaption("KeyboardTest", NULL);
	
        SDL_Surface *plaatje = LoadImg("../../../Downloads/man.png");
        drawImage(plaatje, 50, 50);
        
        /* Enable Unicode translation */
        SDL_EnableUNICODE( 1 );

            /* Poll for events */
            while(SDL_WaitEvent(&event) && quit != 1){
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
        }else if (*SDL_GetKeyName( key->keysym.sym) == 'p'){
		printf("PAUSE\n");
	}
    }

    void drawImage(SDL_Surface *image, int x, int y){
        dest.x = x;
        dest.y = y;
        dest.w = image->w;
        dest.h = image->h;

        SDL_BlitSurface(image, NULL, screen, &dest);
    }

    SDL_Surface *LoadImg(char *name){
    	SDL_Surface *temp = IMG_Load(name);
	    SDL_Surface *image;
        
        if(temp == NULL) {
            printf("Failed to load image %s\n", name);        
        return NULL;       
        }
        
        SDL_SetColorKey(temp, (SDL_SRCCOLORKEY | SDL_RLEACCEL),
            SDL_MapRGB(temp -> format, 0, 0, 0));

        image = SDL_DisplayFormat(temp);
        SDL_FreeSurface(temp);
        if (image == NULL){
            printf("Failed to convert image %s to native format\n", name);
            return NULL;
        }
        return image;

    }



