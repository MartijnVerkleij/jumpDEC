#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "game.h"

/* Input Pins */
int DATA_1 = 0; // X1
int DATA_2 = 1; // X2
int DATA_3 = 2; // Y1
int DATA_4 = 3; // Y2
int DATA_5 = 4; // Block 1
int DATA_6 = 5; // Block 2
int DATA_7 = 6; // Block 3
int DATA_8 = 7; // Block 4
int DATA_9 = 10; // Block 5
int FPGA_RDY = 11;

/* Output Pins */
int INIT_RDY = 13;
int PI_RDY = 14;

/* booleans */
int pi_init = 0;
int amount_rec = 0;

/* Counters */
int block_build = 0;
int co_count = 0;

/* Tijdelijke Coordinaten */
char temp_x[10];
char temp_y[10];

Game game; 

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
    printf("binary number of decimal is %d\n",dec);
    return dec;
}

/* Initialize the pins and empty the system */
void init(){
	game.blockCount = 0;

	wiringPiSetup();
	/* Initialize Input pins */
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
	
	/* Initalize Output pins and set them to 0 */
	pinMode(INIT_RDY, OUTPUT);
	pinMode(PI_RDY, OUTPUT);
	digitalWrite(INIT_RDY, 0);
	digitalWrite(PI_RDY, 0);

	/* Empty the coordinate arrays */
	game.player.x = 0;
	game.player.y = 0;
	int i = 0;
	for(i; i < blockCount; i++){
		game.blocks[i].x = 0;
		game.blocks[i].y = 0;
	} 
	
}

/* Lees het aantal blokken en zet ze */
void blocks_rec(){
	/* Lees de data en plak ze in 1 array */
	char one[] ={(char)(digitalRead(DATA_5) + '0')};
	char two[] ={(char)(digitalRead(DATA_6) + '0')};
	char three[] ={(char)(digitalRead(DATA_7) + '0')};
	char four[] ={(char)(digitalRead(DATA_8) + '0')};
	char five[] ={(char)(digitalRead(DATA_9) + '0')};
	char all[5];
	memcpy(all, one, 1);
	memcpy(&all[1], two, 1);
	memcpy(&all[2], three, 1);
	memcpy(&all[3], four, 1);
	memcpy(&all[4], five, 1);

	/* Decimale weergave van binaire getal */
	int all_len = (int) (sizeof(all)/sizeof(*all)); 
	blockCount = fromBinary(all, all_len);

	/* Note that the amount of blocks is received */
	amount_rec = 1;
}

void co_rec(){
	
	/***********************
	LEES DATA_1 tot DATA_?
	PLAK BIJ DE REST VAN
	COORDINATEN AAN
	************************/
	/* Lees data uit en sla de coordinate bits op */
	char x_temp[1] = {(char)(digitalRead(DATA_1) + '0')};
	memcpy(&temp_x[co_count], x_temp, 1);
	char y_temp[1] = {(char)(digitalRead(DATA_3) + '0')};
	memcpy(&temp_y[co_count], y_temp, 1);
	co_count++;
	/* Als Coordinaat compleet en het is een block*/
	if(co_count == 10 && block_build < blockCount){

		/********************
		COORDINATEN ZIJN KLAAR
		LEES UIT, LEEG BUFFER
		SLA OP ALS X EN Y
		*******************/
   		int n =(int) (sizeof(temp_x)/sizeof(*temp_x)); 
		game.blocks[block_build].x = fromBinary(temp_x,n);
		game.blocks[block_build].y = fromBinary(temp_y,n);
		puts("Block build");
		printf("%d , %d\n",game.blocks[block_build].x,
                        game.blocks  [block_build].y);
		memset(&temp_x[0], 0, sizeof(temp_x));
		memset(&temp_y[0], 0, sizeof(temp_y));		
		//temp_x = char[10];
		//temp_y = char[10];
		co_count = 0;
		block_build = block_build + /* AANTAL BLOKKEN */ 1;
	}
	/* Als alle blokken gebouwd */
	if(co_count == 10 && block_build >= blockCount){
		
		/*******************
		Coordinaten zijn klaar
		lees uit, leeg buffer	
		en sla op als x en y
		*********************/
		
		/* set player coordinates */
   		int n =(int) (sizeof(temp_x)/sizeof(*temp_x)); 
		game.player.x = fromBinary(temp_x,n);
		game.player.y = fromBinary(temp_y,n);
		puts("player build");
		printf("%d, %d\n", game.player.x, game.player.y);
		memset(&temp_x[0], 0, sizeof(temp_x));
		memset(&temp_y[0], 0, sizeof(temp_y));		
		//temp_x = char[10];
		//temp_y = char[10];
		co_count = 0;
		/* Laat FPGA weten dat init rdy is */
		pi_init = 1;
		digitalWrite(INIT_RDY, 1);
	}
	


}

void move_player(){

	/* Lees data uit en sla de coordinate bits op */
	char x_temp[1] = {(char)(digitalRead(DATA_1) + '0')};
	memcpy(&temp_x[co_count], x_temp, 1);
	char y_temp[1] = {(char)(digitalRead(DATA_3) + '0')};
	memcpy(&temp_y[co_count], y_temp, 1);
	co_count++;
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
		puts("MOVE player");
		printf("%d, %d\n",game.player.x, game.player.y);
		memset(&temp_x[0], 0, sizeof(temp_x));
		memset(&temp_y[0], 0, sizeof(temp_y));		

		co_count = 0;
	}
}

void do_something(){
    //printf("In de if");
    if(amount_rec == 0 && pi_init == 0){
        puts("INIT");
	game.blocks_rec();
    } else if(pi_init == 0){
	puts("BLOCKS");
	co_rec();
    } else {
	puts("player");
	move_player();
    }

    /* Send the Ack */
    digitalWrite(PI_RDY, 1);
    poll(0,0,1);
    digitalWrite(PI_RDY, 0);

}

void *inputHandler(Game in_game){
	game = in_game;
	init();
	wiringPiISR(FPGA_RDY, INT_EDGE_RISING, &do_something);
	while(1){
		sched_yield();
	}
}

void main(){
	init();
	wiringPiISR(FPGA_RDY, INT_EDGE_RISING, &do_something);
	while(1){
		sched_yield();
	}
}

