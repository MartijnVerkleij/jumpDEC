#include <SDL/SDL.h>
#include <stdio.h>
#include "game.h"
#include "graphics.h"


void drawImage(SDL_Surface *image, int x, int y);

SDL_Surface *LoadImg(char *name);


void *renderInit(struct game game) {
	int i = game.blockCount;
	SDL_Surface blockImg = LoadImg("test.png");
	for ( i ; i >= 0 ; i--) {
		struct coordinate block = game.blocks[i];
		
		drawImage(&blockImg, block.x, block.y); 
	}
}

SDL_Rect dest;
void drawImage(SDL_Surface *image, int x, int y){
        dest.x = x;
        dest.y = y;
        dest.w = image->w;
        dest.h = image->h;

        SDL_BlitSurface(image, NULL, screen, &dest);
    }



SDL_Surface IMG_LOAD(char *name);

SDL_Surface *LoadImg(char *name) {
	SDL_Surface *temp = IMG_Load(name);
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
