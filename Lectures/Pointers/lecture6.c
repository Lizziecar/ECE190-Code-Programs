#include <stdio.h>
#include <stdlib.h>

//sample of ptr and dynamic memory

void change_int(int* ptr_x) {
	*ptr_x = 50;
}

void change_array_size(char** ptr_y) {
	*ptr_y = (char*)realloc(*ptr_y,sizeof(char) * 100);
}

int main() {
	int x = 100;
	printf("%d\n",x);
	
	change_int(&x);
	//x is 50
	printf("%d\n",x);
	
	char* y = (char*)malloc(sizeof(char) * 10);
	printf("%d\n", y);
	change_array_size(&y);
	// y is of size sizeof(char) * 100
	printf("%d\n", y);
	
	free(y);
}