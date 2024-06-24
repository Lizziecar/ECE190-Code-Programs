#include <stdio.h>

int findLargestSum(int* array, int n) {
	int largestSum = 0;
	for (int i = 0; i < n; i++) { //start
		for (int j = i+1; j < n; j++) { //end
			int sum = 0;
			for (int k = i; k < j+1; k++) {
				sum += array[k];
			}
			if (sum > largestSum) {
				largestSum = sum;
			}
		}
	}
	return largestSum;
}

int main() {
	int array[] = {3,4,5,-2,3,4,5,-10,3,4};
	int largestSum = findLargestSum(array,10);
	
	printf("Largest Sum: %d", largestSum);
}