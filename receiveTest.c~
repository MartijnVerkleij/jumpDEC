#include <wiringPi.h>
#include <stdio.h>

/* Input Pins */
DATA_1 // X1
DATA_2 // X2
DATA_3 // Y1
DATA_4 // Y2
DATA_5 // Block 1
DATA_6 // Block 2
DATA_7 // Block 3
DATA_8 // Block 4
DATA_9 // Block 5
FPGA_RDY

/* Output Pins */
INIT_RDY
PI_RDY

/* booleans */
int pi_init = 0;
int amount_rec = 0;

int amount_block = 0;

/* Counters */
int block_build = 0;
int co_count = 0;

/* Tijdelijke Coordinaten */
char x[10];
char y[10];

struct coordinate {
	int x;
	int y;
}

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
    for(int i=(n-1);i>=0;i--) 
    {
        dec=((int)(a[i] -48)*power(2,j))+dec;
        j++;
    }
    printf("binary number of decimal is %d\n",dec);
    return dec;
}

/* Initialize the pins and empty the system */
void init(){
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
	for(i, i < amount_block,i++){
		blocks[i].x = 0;
		blocks[i].y = 0;
	} 
	
}

/* Lees het aantal blokken en zet ze */
void blocks_rec(){
	/* Lees de data en plak ze in 1 array */
	char one[] ={(char)(digitalRead(DATA_5) + '0')}
	char two[] ={(char)(digitalRead(DATA_6) + '0')}
	char three[] ={(char)(digitalRead(DATA_7) + '0')}
	char four[] ={(char)(digitalRead(DATA_8) + '0')}
	char five[] ={(char)(digitalRead(DATA_9) + '0')}
	char all[5];
	memcpy(all, one, 1);
	memcpy(&all[1], two, 1);
	memcpy(&all[2], three, 1);
	memcpy(&all[3], four, 1);
	memcpy(&all[4], five, 1);

	/* Decimale weergave van binaire getal */
	int all_len = (int) (sizeof(all)/sizeof(*all)); 
	amount_block = fromBinary(all, all_len);

	/* Note that the amount of blocks is received */
	amount_rec = 1
}


void co_rec(){
	
	/***********************
	LEES DATA_1 tot DATA_?
	PLAK BIJ DE REST VAN
	COORDINATEN AAN
	************************/
	
	/* Als Coordinaat compleet en het is een block*/
	if(co_count == 10 && block_build < amount_block){

		/********************
		COORDINATEN ZIJN KLAAR
		LEES UIT, LEEG BUFFER
		SLA OP ALS X EN Y
		*******************/
		blocks[block_build].x = x;
		blocks[block_build].y = y;

		co_count = 0;
		block_build = block_build + /* AANTAL BLOCKEN */ ;
	}
	/* Als alle blokken gebouwd */
	if(co_count == 10 && block_build >= amount_block){
		
		/*******************
		Coordinaten zijn klaar
		lees uit, leeg buffer	
		en sla op als x en y
		*********************/
		
		/* set player coordinates */
		player.x = x;
		player.y = y;

		co_count = 0;
		/* Laat FPGA weten dat init rdy is */
		pi_init = 1;
		digitalWrite(INIT_RDY, 1);
	}
	


}

void move_player(){

	/**********
	MOVE PLAYER
	***********/
}

void main(){
	if(FPGA_RDY){	
		if(amount_rec == 0 && pi_init == 0){
			blocks_rec();
		} else if(pi_init == 0){
			co_rec();
		} else {
			move_player();
		}
		
		/* Send the Ack */
		digitalWrite(PI_RDY, 1);
		poll(0,0,1);
		digitalWrite(PI_RDY, 0);	

	}


