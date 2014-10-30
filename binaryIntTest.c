#include <stdio.h>
#include <string.h>


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

int main(){
	int input = 0;
	char one[1] = {(char)(input + '0')};
	char two[] ={'1'};
	char three[] ={'0'};
	char four[] ={'1'};
	char five[] ={'1'};
	char all[5];
	memcpy(all, one, 1);
	memcpy(&all[1], two, 1);
	memcpy(&all[2], three, 1);
	memcpy(&all[3], four, 1);
	memcpy(&all[4], five, 1);
    int n =(int) (sizeof(all)/sizeof(*all)); 
    printf("%d\n", fromBinary(all, n));
    //printf("%d\n", fromBinary(d, n));
}


