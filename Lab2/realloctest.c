#include <stdlib.h>
#include <stdio.h>

void append(int** x, int* n, int val) {
	printf("n = %d\n", *n);
	*x = realloc(*x,sizeof(int) * *n + 1);
	*(*x + *n) = val;
	*n += 1;
	
	printf("Test: %d\n", **(x+*n-1));
	printf("x = %p\n", x);
	printf("*x = %p\n", *x);
	printf("**x = %d\n", *x[5]);
}

int main() {
	int n = 5;
	int* array1 = (int*)malloc(sizeof(int) * n);
	
	for (int i = 0; i < 5; i++) {
		*(array1 + i) = i*2;
	}
	
	for (int j = 0; j < 5; j++) {
		printf("Old Array: At location %d, the value is %d\n", j, *(array1+j));
	}
	
	append(&array1, &n, 100);
	for (int j = 0; j < 6; j++) {
		printf("New Array: At location %d, the value is %d\n", j, array1[j]	);
	}
	free(array1);
	
}