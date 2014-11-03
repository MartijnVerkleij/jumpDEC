#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Input Pins */
int DATA_1 = 10; // X1
int DATA_2 = 11; // X2
int DATA_3 = 12; // Y1
int DATA_4 = 14; // Y2
int DATA_5 = 2; // Block 1 && x1
int DATA_6 = 3; // Block 2 && x2
int DATA_7 = 4; // Block 3 && y1
int DATA_8 = 5; // Block 4 && y2
int DATA_9 = 6; // Block 5
int FPGA_RDY = 1;

/* Output Pins */
int INIT_RDY = 7;
int PI_RDY = 0;

/* booleans */
int pi_init = 0;
int amount_rec = 0;
int initSend = 0;

int blockCount = 0;

/* Counters */
int block_build = 0;
int co_count = 0;

/* Tijdelijke Coordinaten */
char temp_x[10];
char temp_y[10];

struct coordinate {
	int x;
	int y;
};

struct coordinate blocks[32];
struct coordinate player; 



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
	blockCount = 0;

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
	player.x = 0;
	player.y = 0;
	int i = 0;
	for(i; i < blockCount; i++){
		blocks[i].x = 0;
		blocks[i].y = 0;
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
	char x_temp[1] = {(char)(digitalRead(DATA_5) + '0')};
	memcpy(&temp_x[co_count], x_temp, 1);
	char x_temp2[1] = {(char)(digitalRead(DATA_6) + '0')};
	memcpy(&temp_x[co_count + 1], x_temp2, 1);
	char y_temp[1] = {(char)(digitalRead(DATA_7) + '0')};
	memcpy(&temp_y[co_count], y_temp, 1);
	char y_temp2[1] = {(char)(digitalRead(DATA_8) + '0')};
	memcpy(&temp_y[co_count + 1], y_temp2, 1);
	co_count += 2;
	/* Als Coordinaat compleet en het is een block*/
	if(co_count == 10 && block_build < blockCount){

		/********************
		COORDINATEN ZIJN KLAAR
		LEES UIT, LEEG BUFFER
		SLA OP ALS X EN Y
		*******************/
   		int n =(int) (sizeof(temp_x)/sizeof(*temp_x)); 
		blocks[block_build].x = fromBinary(temp_x,n);
		blocks[block_build].y = fromBinary(temp_y,n);
		puts("Block build");
		printf("%d , %d\n",blocks[block_build].x,
                        blocks  [block_build].y);
		memset(&temp_x[0], 0, sizeof(temp_x));
		memset(&temp_y[0], 0, sizeof(temp_y));		
		//temp_x = char[10];
		//temp_y = char[10];
		co_count = 0;
		block_build = block_build + /* AANTAL BLOKKEN */ 1;
	} 
	if(initSend != 1 && block_build >= blockCount){
                digitalWrite(INIT_RDY, 1);
		initSend ==1;
		pi_init = 1;
	}
	


}

void move_player(){

	/* Lees data uit en sla de coordinate bits op */
	char x_temp[1] = {(char)(digitalRead(DATA_1) + '0')};
	memcpy(&temp_x[co_count], x_temp, 1);
	char x_temp2[1] = {(char)(digitalRead(DATA_2) + '0')};
	memcpy(&temp_x[co_count + 1], x_temp2, 1);
	char y_temp[1] = {(char)(digitalRead(DATA_3) + '0')};
	memcpy(&temp_y[co_count], y_temp, 1);
	char y_temp2[1] = {(char)(digitalRead(DATA_4) + '0')};
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
		player.x = fromBinary(temp_x,n);
		player.y = fromBinary(temp_y,n);
		puts("MOVE player");
		printf("%d, %d\n",player.x, player.y);
		memset(&temp_x[0], 0, sizeof(temp_x));
		memset(&temp_y[0], 0, sizeof(temp_y));		

		co_count = 0;
	}
}

void do_something(){
    printf("In de if");
    if(amount_rec == 0 && pi_init == 0){
        puts("INIT");
	blocks_rec();
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

void main(){
	init();
	wiringPiISR(FPGA_RDY, INT_EDGE_RISING, &do_something);
	while(1){
		sched_yield();
	}
}

