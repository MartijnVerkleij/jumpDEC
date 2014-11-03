#include <SDL/SDL.h>
#include <stdio.h>
#include "game.h"
#include "graphics.h"

SDL_Surface *IMG_Load(char[]);

void drawImage(SDL_Surface *image, int x, int y);

SDL_Surface *LoadImg(char *name);

SDL_Surface *playerImg;

//struct game agame;

void *render(struct game *game){
	//game = &ingame;
	//printf("%p",game);
	int i = game->blockCount;
	printf("Blockcount: %d",i);
	
	SDL_FillRect(screen, NULL, 0);
	
	SDL_Surface *blockImg = LoadImg("test.png");
	for ( i ; i > 0 ; i--) {
		int block_x = game->blocks[i].x;
		int block_y = game->blocks[i].y;
		drawImage(blockImg, block_x, block_y); 
	}
	playerImg = LoadImg("man.png");
	int player_x = game->player.x;
        int player_y = game->player.y;
	drawImage(playerImg, player_x, player_y);
	SDL_Flip(screen);
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
