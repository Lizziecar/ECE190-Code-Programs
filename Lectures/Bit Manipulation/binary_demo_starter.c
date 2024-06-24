#include <stdio.h>

void print_bit_representation(char x){
	// What is wrong here?
	/*
		char tmp = x; //this is signed so the first bit will always be one
		char mask = 0b01; //same as above
	*/
	unsigned char tmp = x; //fixed
	unsigned char mask = 0b01; //fixed
	while (tmp != 0){
		fprintf(stdout, "%d", mask & tmp);
		tmp >>= 1;
	} fprintf(stdout, "\n");
} 


int main(){
	char x = 0b10101011; // has exactly 8 bits, which should be ok.
	char y = 0x0A; //ten in hexadecmial
	
	fprintf(stdout, "%x\n", x);
	fprintf(stdout, "%x\n", y);

	// fprintf(stdout, "%d\n", x);
	// fprintf(stdout, "%d\n", y);
	
	// comment the below out to run line 22-23
	print_bit_representation(x);
}