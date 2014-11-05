#include <SDL/SDL.h>
#include <pthread.h>
#include "init.c"
#include "keyboardHandler.c"
#include "inputHandler.c"
#include "graphics.c"
#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


extern void *init(char *);
extern void *keyboardHandler();
extern void *render(struct game *);
extern void *renderInit();


/* Input Pins */
int DATA_1 = 8; // X1
int DATA_2 = 7; // X2
int DATA_3 = 10; // Y1
int DATA_4 = 11; // Y2
int DATA_5 = 27; // Block 1 && x1
int DATA_6 = 22; // Block 2 && x2
int DATA_7 = 23; // Block 3 && y1
int DATA_8 = 24; // Block 4 && y2
int DATA_9 = 25; // Block 5
int FPGA_RDY = 18;

/* Output Pins */
int INIT_RDY = 4;
int PI_RDY = 17;

/* booleans */
int pi_init = 0;
int amount_rec = 0;
int initSend = 0;


/* Counters */
int block_build = 0;
int co_count = 0;

/* Tijdelijke Coordinaten */
char temp_x[10];
char temp_y[10];

void initInput();
void do_something();
void blocks_rec();
void co_rec();
void move_player();

pthread_t keyboardThread;

struct game game;

int main( int argc, char *argv[] ) {
	
	init("The Endgame");
	pthread_create(&keyboardThread, NULL, &keyboardHandler, &game);

	/*
	game.blockCount = 2;
	game.blocks[1].x = 50;
        game.blocks[1].y = 50;
        game.blocks[2].x = 150;
        game.blocks[2].y = 150;
	game.player.x = 200;
	game.player.y = 200;
	*/

	renderInit();
	
	initInput();
	if(amount_rec == 0 && digitalRead(FPGA_RDY) == 1){
                blocks_rec();
        }
        wiringPiISR(FPGA_RDY, INT_EDGE_RISING, do_something);

	while(1){
		// Start frame
		long long frame = (long long) SDL_GetTicks();
		
		render(&game);

		/* ================== */
		/* FRAME FINALIZATION */
		/* ================== */
		long long time_to_spare = 1000/30 - (SDL_GetTicks() - frame);
		//Uint32 wait = 100;
		Uint32 wait = (time_to_spare > 0) ? (Uint32) time_to_spare : 0 ; 
		//printf("Time to Spare: %d\n", wait);
		SDL_Delay(wait); // wait until this loop has taken 1/60 second.
	}

}


/* INPUTHANDLER */


/* Used to calculate the decimal */
int power(int c, int d)
{
    int pow=1;
    int i=1;
    while(i<=d) 
    {
        pow=pow*c;
        i++;
    }
    return pow;
}
/* Calculate decimal from binary */
int fromBinary(char *a, int n)
{
    int dec=0;
    int j=0;
    int i = (n-1);
    for(i; i>=0; i--) 
    {
        dec=((int)(a[i] -48)*power(2,j))+dec;
        j++;
    }
    //printf("binary number of decimal is %d\n",dec);
    return dec;
}

/* Initialize the pins and empty the system */
void initInput(){
	game.blockCount = 0;

	/*wiringPiSetup();
	Initialize Input pins 
	pinMode(DATA_1, INPUT);
	pinMode(DATA_2, INPUT);
	pinMode(DATA_3, INPUT);
	pinMode(DATA_4, INPUT);
	pinMode(DATA_5, INPUT);
	pinMode(DATA_6, INPUT);
	pinMode(DATA_7, INPUT);
	pinMode(DATA_8, INPUT);
	pinMode(DATA_9, INPUT);
	pinMode(FPGA_RDY, INPUT);
	*/
	/* Initalize Output pins and set them to 0 */
	/*pinMode(INIT_RDY, OUTPUT);
	pinMode(PI_RDY, OUTPUT); */
	digitalWrite(INIT_RDY, 0);
	digitalWrite(PI_RDY, 0);

	/* Empty the coordinate arrays */
	game.player.x = 0;
	game.player.y = 0;
	int i = 0;
	for(i; i < game.blockCount; i++){
		game.blocks[i].x = 0;
		game.blocks[i].y = 0;
	} 
	
}

/* Lees het aantal blokken en zet ze */
void blocks_rec(){
	/* Lees de data en plak ze in 1 array */
	char one[] ={(char)(digitalRead(DATA_9) + '0')};
	char two[] ={(char)(digitalRead(DATA_8) + '0')};
	char three[] ={(char)(digitalRead(DATA_7) + '0')};
	char four[] ={(char)(digitalRead(DATA_6) + '0')};
	char five[] ={(char)(digitalRead(DATA_5) + '0')};
	char all[5];
	memcpy(all, one, 1);
	memcpy(&all[1], two, 1);
	memcpy(&all[2], three, 1);
	memcpy(&all[3], four, 1);
	memcpy(&all[4], five, 1);

	/* Decimale weergave van binaire getal */
	int all_len = (int) (sizeof(all)/sizeof(*all)); 
	game.blockCount = fromBinary(all, all_len);

	/* Note that the amount of blocks is received */
	amount_rec = 1;
	
	    /* Send the Ack */
	    digitalWrite(PI_RDY, 1);
	    poll(0,0,8);
	    //sleep(1);
	    digitalWrite(PI_RDY, 0);
	
}

void co_rec(){
	
	/***********************
	LEES DATA_1 tot DATA_?
	PLAK BIJ DE REST VAN
	COORDINATEN AAN
	************************/
	
	int x1 = digitalRead(DATA_5); 
        int x2 = digitalRead(DATA_6);
        int y1 = digitalRead(DATA_7);
        int y2 = digitalRead(DATA_8);




	if (digitalRead(DATA_1) &&digitalRead(DATA_2) && digitalRead(DATA_3) &&
                digitalRead(DATA_4)) {
                if(co_count == 0) {puts(" Omdat martijn");}
		co_count = 0;
                //puts("overriding invalid block count");
                memset(&temp_x[0], 0, sizeof(temp_x));
                memset(&temp_y[0], 0, sizeof(temp_y));
        }

	/* lees data uit en sla de coordinate bits op */
	char x_temp[1] = {(char)x1 + '0'};
	memcpy(&temp_x[co_count], x_temp, 1);
	char x_temp2[1] = {(char)x2 + '0'};
	memcpy(&temp_x[co_count + 1], x_temp2, 1);
	char y_temp[1] = {(char)y1 + '0'};
	memcpy(&temp_y[co_count], y_temp, 1);
	char y_temp2[1] = {(char)y2 + '0'};
	memcpy(&temp_y[co_count + 1], y_temp2, 1);
	co_count += 2;
	//printf(temp_x);
	//printf(temp_y);
	/* Als Coordinaat compleet en het is een block*/
	if(co_count == 10 /*&& block_build < game.blockCount*/){

		/********************
		COORDINATEN ZIJN KLAAR
		LEES UIT, LEEG BUFFER
		SLA OP ALS X EN Y
		*******************/
   		int n =(int) (sizeof(temp_x)/sizeof(*temp_x)); 
		game.blocks[block_build].x = fromBinary(temp_x,n);
		game.blocks[block_build].y = fromBinary(temp_y,n);
		//puts("Block build");
		//printf("%d , %d\n",game.blocks[block_build].x,
                       // game.blocks[block_build].y);
		memset(&temp_x[0], 0, sizeof(temp_x));
		memset(&temp_y[0], 0, sizeof(temp_y));		
		//temp_x = char[10];
		//temp_y = char[10];
		co_count = 0;
		block_build = block_build + /* AANTAL BLOKKEN */ 1;
	} 
	if(initSend != 1 && block_build >= game.blockCount){
                digitalWrite(INIT_RDY, 1);
		initSend ==1;
		pi_init = 1;
	}
	


}

void move_player(){
	
	int x1 = digitalRead(DATA_1);
        int x2 = digitalRead(DATA_2);
        int y1 = digitalRead(DATA_3);
        int y2 = digitalRead(DATA_4);

	if (digitalRead(DATA_5) && digitalRead(DATA_6) && digitalRead(DATA_7) && 
		digitalRead(DATA_8) && digitalRead(DATA_9)) {
		
		if(co_count != 0){ printf(" overriding invalid block count %d\n", co_count );}
		co_count = 0;
		
		//puts("overriding invalid block count");
		memset(&temp_x[0], 0, sizeof(temp_x));
                memset(&temp_y[0], 0, sizeof(temp_y));
	}

	/* Lees data uit en sla de coordinate bits op */
	char x_temp[1] = {(char)x1 + '0'};
	memcpy(&temp_x[co_count], x_temp, 1);
	char x_temp2[1] = {(char)x2 + '0'};
	memcpy(&temp_x[co_count + 1], x_temp2, 1);
	char y_temp[1] = {(char)y1 + '0'};
	memcpy(&temp_y[co_count], y_temp, 1);
	char y_temp2[1] = {(char)y2 + '0'};
	memcpy(&temp_y[co_count + 1], y_temp2, 1);
	co_count += 2;
	if(co_count == 10){
		
		/*******************
		Coordinaten zijn klaar
		lees uit, leeg buffer	
		en sla op als x en y
		*********************/
		
		/* set player coordinates */
   		int n =(int) (sizeof(temp_x)/sizeof(*temp_x)); 
		game.player.x = fromBinary(temp_x,n);
		game.player.y = fromBinary(temp_y,n);
		//puts("MOVE player");
		//printf("%d, %d\n", game.player.x, game.player.y);
		memset(&temp_x[0], 0, sizeof(temp_x));
		memset(&temp_y[0], 0, sizeof(temp_y));		

		co_count = 0;
	}
}
void do_something(){
    //printf("In de if");
    if(pi_init == 0){
	//printf("BLOCKS ");
	co_rec();
    } else {
	//printf("player ");
	move_player();
    }


    /* Send the Ack */
    digitalWrite(PI_RDY, 1);
    poll(0,0,8);
    //sleep(1);
    digitalWrite(PI_RDY, 0);
}
