#include <stdio.h>

/**
void print_bit_representation(char x){
	// What is wrong here?
	// using signed types (which is the default) can
	// produce unexpected results because
	// of the way the highest bit is used for encoding
	char tmp = x;
	char mask = 0b01;
	while (tmp != 0){
		fprintf(stdout, "%d", mask & tmp);
		tmp >>= 1;
	} fprintf(stdout, "\n");
} 

void print_bit_representation(unsigned char x){
	// To be safe, case to an unsigned type.
	// Here, we are implicitly casting. There is no
	// problem because an unsigned and signed char 
	// have the same number of bits, so we are not worried
	// about data loss.
	// however, we are printing in the reverse order.
	unsigned char tmp = x;
	unsigned char mask = 0b01;
	while (tmp != 0){
		fprintf(stdout, "%d", mask & tmp);
		tmp >>= 1;
	} fprintf(stdout, "\n");
}

*/

void print_bit_representation(unsigned char x){
	unsigned char tmp = x;
	// note -- the left shift **does** rely on casting to an unsigned type
	// Efe will be happy!
	unsigned char mask = (~0b0) ^ ((unsigned char)(~0b0) >> 1); // left shift here after casting
	unsigned char width = (~0b0);
	
	fprintf(stdout, "%x\n", mask);
	
	while (width != 0){
		if ((mask & tmp) == 0){ // that bit is 0
			fprintf(stdout, "0");
		} else{fprintf(stdout, "1");}
		tmp <<= 1;
		width <<= 1;
	} fprintf(stdout, "\n");
}

int main(){
	char x = 0b10101011; // has exactly 8 bits, which should be ok.
	char y = 0x0A;
	
	//fprintf(stdout, "%x\n", x);
	//fprintf(stdout, "%x\n", y);
	
	// here, we see that x is a negative number
	// fprintf(stdout, "%d\n", x);
	// fprintf(stdout, "%d\n", y);
	
	print_bit_representation(x);
}