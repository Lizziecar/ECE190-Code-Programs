#include <stdio.h>
#include <stdlib.h>

#include "fancylist.h"

typedef FancyList BinaryTree;
typedef FancyList Heap;

Heap* initialize_heap(int root){
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	init_fancylist(heap, 1);
	append(heap, root);
	return heap;
}

int peek(Heap* heap){

}

void bubble_down(Heap* heap, int idx){
/** left as an exercise */
	return;
}

void bubble_up(Heap* heap, int idx){

}

void insert(Heap* heap, int val){
	append(heap, val);
	bubble_up(heap, heap->count_el - 1);
}

int pop(Heap* heap){
/** left as an exercise*/
	return;
}

void print_binary_tree(BinaryTree* bt){
	print_fancy_list(*bt);
}

int main(){
	int arr[] = {10, 12, 21, 15, 30, 18, 3, 40, 31, 22};
	int n = 10;
	int tmp;
	
	Heap* heap = initialize_heap(1);
	
	for(int i=0; i<n; i++){
		print_binary_tree(heap);	
		insert(heap, arr[i]);
	}
	print_binary_tree(heap);	
	
	/** 
	// uncomment once completed exercises
	while (heap->count_el > 0){
		tmp = pop(heap);
		fprintf(stdout, "Popped: %d\n\n", tmp);
		print_binary_tree(heap);
	}
	fprintf(stdout, "Heap is now empty.\n");
	*/
}