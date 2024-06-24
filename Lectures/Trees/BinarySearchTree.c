#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int cargo;
	struct TreeNode* left_child;
	struct TreeNode* right_child;
	
	//struct TreeNode* parent
} TreeNode;

void search_recursive(TreeNode* root, int val) {
	/*
		Return if the value is in the tree, and 0 otherwise
	*/	
	
	//base case:
	if (root == NULL) { //immediate leave
		return 0;
	} else if (val = root->cargo) { //immediate there
		return 1;
	} else if (val < root->cargo) {
		//go left, val is smaler than where we are
		return search_recursive(root->left_child, val);
	} else { //go right
		return search_recursive(root->right_child, val);
	}
	
}

int search_iterative(TreeNode* root, int val) {
	/*
		Return if the value is in the tree, and 0 otherwise
	*/
	
	TreeNode* curr = root;
	while(curr != NULL) {
		if (curr->cargo == val) {
			return 1;
		} else if (val < curr->cargo) {
			curr = curr->left_child;
		} else {
			curr = curr->right_child;
		}
	}
	return 0;
	
	/* Saima ver
	if (root == NULL) {
		return 0;
	}
	
	TreeNode* curr = root;
	while (curr != NULL && curr-cargo-> != val) {
		if (val < curr->cargo) {
			curr = curr->left_child;
		} else {
			curr = curr->right_child;
		}
	}
	
	if (cargo == NULL) {
		return 0;
	} else {
		return 1;
	}	
	*/
}

TreeNode* init_bst(int root_val) {
	TreeNode* bst = (TreeNode*)malloc(sizeof(TreeNode));
	bst->cargo = root_val;
	bst->left_child = NULL:
	bst->right_child = NULL;
	return bst;
}

void insert_helper(TreeNode* node_to_insert, TreeNode* curr) {
	if (node_to_insert->cargo < curr->cargo && curr->left_child == NULL) {
		//go ahead and insert at the left
	} else if (node_to_insert->cargo > curr-cargo && curr->right_child == NULL) {
		// go ahead and insert at the right
	} else {
		if (node_to_insert->cargo > curr->cargo) {
			insert_helper(node_to_insert, curr->left); //recurses to the left
		} else {
			insert_helper(node_to_insert, curr->right); //recurses to the right
		}
	}
}

void insert(TreeNode** root, int new_val) {
	/**
	assume new_val does not appear in the tree given by (*root)
	*/
	
	TreeNode* new_node = init_bst(new_val);
	if ((*root) == NULL) { //if tree is empty
		(*root) = init_bst(new_val);
	} else if (new_val < (*root)->cargo) {
		//go left
		insert_helper((*root)->left_child);
	} else if (new_val > (*root->cargo) {
		//go right
		insert_helper((*root)->right_child);
	}
}

void delete() {
	
}

void print_inorder(TreeNode* root) {
	//base case
	if (root == NULL) {
		return;
	} else {
		print_inorder(root->left_child);
		fprintf(stdout, "%d", root->cargo);
		print_inorder(root->right_child);
	}
}

void print_postorder(TreeNode* root) {
	//base case
	if (root == NULL) {
		return;
	} else {
		print_inorder(root->left_child);
		print_inorder(root->right_child);
		fprintf(stdout, "%d", root->cargo);
	}
}

void print_preorder(TreeNode* root) {
	//base case
	if (root == NULL) {
		return;
	} else {
		fprintf(stdout, "%d", root->cargo);
		print_inorder(root->left_child);
		print_inorder(root->right_child);
	}
}

int main() {
	TreeNode* bst = NULL;
	insert(&bst, 9);
	insert(&bst, 1);
	insert(&bst, 50);
	insert(&bst, 25);
	insert(&bst, 19);
	insert(&bst, 30);
	insert(&bst, 100);
	insert(&bst, 60);
	insert(&bst, 55);
	insert(&bst, 80);
	insert(&bst, 110);
	
	printf("Inorder: ");
	print_inorder(bst);
	printf("\n");
	
	printf("Postorder: ");
	print_postorder(bst);
	printf("\n");
	
	printf("Prerder: ");
	print_preorder(bst);
	printf("\n");
	
	
	
	//how to print out trees:
	//Traversals 
}