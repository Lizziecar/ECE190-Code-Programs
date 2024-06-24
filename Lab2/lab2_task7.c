#include <stdlib.h>

void append(int** x, int* n, int val) {
	/**
	<*x> refers to a dynamically allocated integer array
	of size <*n> * sizeof(int).
	Modifies <*x> such that it has val added to the end.
	The modified array should be of length <*n> + 1.
	Modifies <*n> such that it is updated to be the value
	of the new length of the array <*x>.
	HINT: you may find the function realloc (...) helpful
	*/
	
	//no malloc or free
	
	//realloc to increase the size of the array:
	*x = realloc(*x,sizeof(int) * *n + 1);
	*(*x+*n) = val;
	*n += 1;
}