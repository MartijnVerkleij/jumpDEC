#include <wiringPi.h>
#include <stdio.h>

int count = 0;
int write = 0;
void mom(){
    //printf("MOM");
    if(count ==0){
        digitalWrite(write,1);
	count++;
	printf("1");
    } else if (count == 1){
	digitalWrite(write,1);
	count++;
        printf("0");
    } else if (count == 2){
        digitalWrite(write,1);
        count++;
        printf("0");
    } else if (count == 3){
        digitalWrite(write,1);
        count++;
        printf("0");
    }  else {
        digitalWrite(write,1);
        count = 0;
        printf("0\n");
    }
    fflush(stdout);
}

void dad(){
    digitalWrite(write,0);
}

int main(int argc, char *argv[]){
    if(argc > 1) write = (int)(argv[1][0] - '0'); 
    wiringPiSetup();
    pinMode(15, INPUT);
    pinMode(write, OUTPUT);
    printf("%d", argc);
    printf("%d\n", write);
    wiringPiISR(15, INT_EDGE_RISING, &mom);
    //wiringPiISR(15, INT_EDGE_FALLING, &dad);
    while(1){
    }      
    return 0;
}


