#include <stdio.h>

int main() {
	int y[2] = {1,5};
	int x[3];
	
	for (int i = 0; i < 3; i++) {
		x[i] = y[i];
	}
	
	x[2] = 9;
	
	fprintf(stdout,
		"Addresses of x 0: %p, 1: %p, 2: %p\n" ,
		x, x + 1, x + 2
	);
	fprintf(stdout, 
		"Values of x through dereferencing 0: %d, 1: %d, 2: %d\n",
		*x, *(x+1), *(x+2)
	);
	fprintf(stdout,
		"Values of x through indexing 0: %d, 1: %d, 2: %d\n",
		x[0], x[1], x[2]
	);
	fprintf(stdout,
		"Indexing out of range: %d\n", x[3]
	);
}