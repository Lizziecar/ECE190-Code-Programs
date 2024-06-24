#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
	int cargo;
	struct ListNode* next; // Q for the class: why not just an actual ListNode?
} ListNode;

void print_ll(ListNode* head){ //print the link list on stdout
	//will use null listnode
	ListNode* curr = head;
	while(curr != NULL) {
		fprintf(stdout,"%d " , curr->cargo); //(*curr).cargo also works
		curr = curr-> next;
	}	fprintf(stdout,"\n");
}

ListNode* create_ll(int* arr, int n){
	/**
	7 5 2 9
	n = 4
		arr is an arry representing the sequence of elements
		to construct a list from; it has n elements
		
		n is the length of the arr 
		you are guaranteed n >= 1
	*/
	//using dynamic memory to make sure it isn't static
	//refer to textbook
	
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	head->cargo = arr[0];
	head->next = NULL; //if n is 1, this takes care of the "end" of our LL
	
	//helper nodes
	ListNode* prev = head; //keeping track of two nodes at a time
	ListNode* curr = NULL; //
	
	for(int i = 1; i < n; i++) { //because arr[0] is already inserted
		curr = (ListNode*)malloc(sizeof(ListNode)); //sets curr as a new listnode
		curr->cargo = arr[i];
		curr->next = NULL; //preliminary book keeping
		
		prev->next = curr; //previous' next is now the current node //links this new node to the rest of the linkedlist
		prev = curr; //sets up for the next interation
	}
	
	return head;
	
	
}

void insert(ListNode* head, int idx, int val){
	//get a record of where I am going to start
	ListNode* curr = head;
	ListNode* prev = NULL;
	
	//increment to point in the list that you need
	for (int i=0; i < idx; i++) {
		prev = curr;
		curr = curr->next;
	}
	
	//slot the new node where it should go
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	new_node->cargo = val;
	new_node->next = NULL;
	
	//rewire nodes
	prev->next = new_node;
	new_node->next = curr;
}


void delete_ll(ListNode** head){
	/*
		Set *head to Null
	*/
	
	ListNode* prev = *head;
	ListNode* curr = (*head)->next;
	
	while (curr != NULL) {
		free(prev);
		prev = curr;
		curr = curr->next;
	}
	//final free
	free(prev);
	
	*head = NULL;
	
}


void main(){
	int arr[] = {1, 7, 100, 20};
	int n = 4;
	ListNode* head = create_ll(arr, n);
	print_ll(head);
	
	int val = 35;
	int i = 3;
	fprintf(stdout, "Now inserting value %d at index %d...\n", val, i);
	insert(head, i, val);
	print_ll(head);
	
	val = 2000;
	i = 5;
	
	fprintf(stdout, "Now inserting value %d at index %d...\n", val, i);
	insert(head, i, val);
	print_ll(head);
	
	delete_ll(&head);
}