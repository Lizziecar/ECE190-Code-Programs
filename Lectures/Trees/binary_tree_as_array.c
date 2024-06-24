#include <stdio.h>
#include <stdlib.h>
#include "fancylist.h"

typedef FancyList BinaryTree;

BinaryTree* initialize_tree(int root){
	BinaryTree* bt = (BinaryTree*)malloc(sizeof(BinaryTree));;
	init_fancylist(bt, 1);
	append(bt,root);
	
	return bt;
}

void insert(BinaryTree* bt, int val){
	append(bt, val);
}

int search(BinaryTree* bt, int val){
	for (int i = 0; i < bt->count_el; i++) {
		if (bt->ptr[i] == val) {
			return 1;
		}
	}
	return 0;
}

void print_binary_tree(BinaryTree* bt){
	print_fancy_list(*bt);
}

int get_parent(BinaryTree* bt, int idx){
	//left child of i --> 2 * i + 1
	//right child of i --> 2 * i + 2
	if (idx % 2 != 0) { //odd
		return *(bt->ptr + (idx-1)/2);
	} else { //even
		return *(bt->ptr + (idx-2)/2);
	}
}

int main(){
	int x;
	
	x = 10;
	BinaryTree* bt = initialize_tree(x);

	x = 50;
	insert(bt, x);
	
	x = 19;
	insert(bt, x);
	
	x = 45;
	insert(bt, x);
	
	x = 60;
	insert(bt, x);
	
	x = 18;
	insert(bt, x);
	
	x = 2;
	insert(bt, x);
	
	x = 65;
	insert(bt, x);
	
	x = 15;
	insert(bt, x);
	
	print_binary_tree(bt);
	fprintf(stdout, "Parent of %d is %d\n", 15, get_parent(bt, 8));
	
}