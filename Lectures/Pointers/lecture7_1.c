#include <stdlib.h>

int main() {
	int** x = (int *)malloc(sizeof(int) *5);
	for (int i = 0; i < 5; i++) {
		*(x+1) = (int *)calloc(sizeof(int) * 10);
	}
	
	//does stuff
	
	//free
	for (int i = 0; i < 5; i++) {
		free(*(x+i));
	}
	
	free(x);
}