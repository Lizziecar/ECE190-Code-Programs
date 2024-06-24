#include <stdio.h>

void merge(int result[], int arr1[], int arr2[], int n1, int n2){
	/*
	Merge two arrays, <arr1> and <arr2>, that are both
	sorted in ascending order. Store the resulting
	sorted array in <result>.
	
	<arr1> and <arr2> have lengths <n1> and <n2>, 
	respectively.
	
	<result> has length <n1> + <n2>
	*/
	
	// i1 is a counter for arr1
	// i2 is a counter for arr2
	int i1 = 0, i2 = 0;
	int i = 0; // counter for result

	while (i1 < n1 && i2 < n2) {
		if (arr1[i1] <= arr2[i2]){
			result[i++] = arr1[i1++];
		} else {
			result[i++] = arr2[i2++];
		}
	}
	
	// pick off the remaining array
	while (i1 < n1){
		result[i++] = arr1[i1++];
	}
	while (i2 < n2){
		result[i++] = arr2[i2++];
	}
}

void mergesort(int sorted[], int unsorted[], int n){
	/*
	Recursive implementation of Mergesort.
	
	Note: this implementation is _not_ in place.
	*/
	
	// determine the lengths of the left and
	// right halves of the unsorted array
	int n_l = n / 2;
	int n_r = n - n_l;
	
	// create arrays to store the left and right
	// partititions of the unsorted array
	int l[n_l];
	int r[n_r];
		
	//copy over arrays into l and r
	for (int i=0; i<n_l; i++){
		l[i] = unsorted[i];
	}
	for (int j=0; j<n_r; j++){
		r[j] = unsorted[n_l + j];
	}
	
	// create a new arrays to store the sorted left and
	// right subpartitions
	int sorted_l[n_l];
	int sorted_r[n_r];
	
	// first, check if we have degenerate cases
	// where there is no sorting needed to be done
	if (n_l == 0){
		sorted[0] = r[0];
	} else if (n_r == 0) {
		sorted[0] = l[0];
	} else if (n_l == 1 && n_r == 1){
		// merge them, they are sorted
		merge(sorted, l, r, n_l, n_r);
	} else {
		// recursive call to further subdivide
		// into left and right
		mergesort(sorted_l, l, n_l);
		mergesort(sorted_r, r, n_r);
		
		// now have l and r sorted into sorted_l and sorted_r
		// merge them into our final result
		merge(sorted, sorted_l, sorted_r, n_l, n_r);
	}
}

void reverse_list(int reversed[], int unreversed[], int n) {
	for (int i = 0; i < n; i++) {
		reversed[i] = unreversed[n-i-1];
	}
}

int main(){
	int x[] = {10, 4, 3, 2, 1, 100, 4, 65, 42, 51};
	int n = 10;
	int sorted[n];
	int reversed[n];
	
	fprintf(stdout, "Now sorting the array ... ");
	
		
	fprintf(stdout, "Array is sorted ... ");
	mergesort(sorted, x, n);
	for (int i=0; i<n; i++){
		fprintf(stdout, "%d ", sorted[i]);
	}
	fprintf(stdout, "\n");
	
	fprintf(stdout, "Array is reversed ... ");
	reverse_list(reversed,sorted,n);
	for (int i=0; i<n; i++){
		fprintf(stdout, "%d ", reversed[i]);
	}
	fprintf(stdout, "\n");
}