#include <SDL/SDL.h>
#include <stdio.h>
#include "game.h"
#include "levelLoaded.h"

SDL_Surface *IMG_Load(char[]);

void drawImage(SDL_Surface *image, int x, int y);

SDL_Surface *LoadImg(char *name);

SDL_Surface IMG_LOAD(char *name);


//Constant objects
SDL_Surface *room_floorimg;
SDL_Surface *playerImg;
SDL_Surface *blockImg;
SDL_Surface *loadingImg;

int SCREEN_HEIGHT;
int SCREEN_WIDTH;

void *renderInit(struct game *game) {
	
	/* Create floor 
	room_floor = SDL_CreateRGBSurface(0, SCREEN_WIDTH, 20, 32, 0, 0, 0, 0);
	SDL_FillRect(room_floor, NULL, SDL_MapRGB(room_floor->format, 255, 255, 255));
	*/

	/* Load sprites */
	room_floorimg = LoadImg("floor.png");
	playerImg = LoadImg("man.png");
	blockImg = LoadImg("test.png");
	loadingImg = LoadImg("loading.png");

	while(levelLoaded != 1) {
		drawImage(loadingImg, 512 - 100 , 256 - 50);
		SDL_Flip(screen);
		SDL_Delay(100);
	}
}


void *render(struct game *game){
	int i = game->blockCount;
	
	SDL_FillRect(screen, NULL, 0);
	
	for ( i ; i > 0 ; i--) {
		int block_x = game->blocks[i].x;
		int block_y = game->blocks[i].y;
		drawImage(blockImg, block_x, block_y); 
	}
	int player_x = game->player.x;
        int player_y = game->player.y;
	drawImage(playerImg, player_x, player_y);
	
	drawImage(room_floorimg, 0, WINDOW_HEIGHT - 6); 
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
