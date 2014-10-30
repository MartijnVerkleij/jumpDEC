#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


        int random_number(int min_num, int max_num)
        {
            int result=0,low_num=0,hi_num=0;
            if(min_num<max_num)
            {
                low_num=min_num;
                hi_num=max_num+1; // this is done to include max_num in output.
            }else{
                low_num=max_num+1;// this is done to include max_num in output.
                hi_num=min_num;
            }
            srand(time(NULL));
            result = (rand()%(hi_num-low_num))+low_num;
            return result;
        }

int main(int argc, char *argv[]){
    wiringPiSetup();
    pinMode(15, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    puts("HOI"); 
    int arr[4] = {15,16,8,9};
    //Random rnd = new Random();
    while(1){

	int pos = random_number(0,3);
	//putchar(4);
	printf("Change %d ", arr[pos]);
	//fflush(stdout);
	if (digitalRead(arr[pos]) == 0){
	    //puts("In de if");
	    digitalWrite(arr[pos], 1);
	    printf("to 1\n");

	} else {
	    //puts("in de else");
	    digitalWrite(arr[pos], 0);
	    printf("to 0\n");

	}
	sleep(1);
    }      
    return 0;
}


