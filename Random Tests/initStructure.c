#include <stdio.h>
#include <stdlib.h>

int** initStructure(int r, int* a) {
	int** matrix = (int**)malloc(sizeof(int*)*r);
	for (int i = 0; i < r; i++) {
		matrix[i] = (int*)calloc(sizeof(int) * a[i], 0);
	}
	return matrix;
}

int main() {
	int r = 3;
	int* a = {3,4,2};
	int** my_matrix = initStructure(r,a);
	
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < a[i]; j++) {
			printf("%d, ", my_matrix[i][j]);
		}
		printf("\n");
	}
}