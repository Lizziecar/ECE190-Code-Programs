#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
	int cargo;
	struct ListNode* next;
} ListNode;

ListNode* init_list(int cargo) {
	ListNode* ll = (ListNode*)malloc(sizeof(ListNode));
	ll->cargo = cargo;
	ll->next = NULL;
	
	return ll;
}

void add_node(ListNode* ll, int cargo) {
	ListNode* curr = ll;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = malloc(sizeof(ListNode));
	curr->next->cargo = cargo;
	curr->next->next = NULL;
}

void print_ll(ListNode* ll) {
	ListNode* curr = ll;
	while (curr != NULL) {
		printf("%d ", curr->cargo);
		curr = curr->next;
	}
	printf("\n");
}

ListNode* reverse_ll(ListNode* ll) {
	ListNode* curr = ll;
	int size = 0;
	
	while (curr != NULL) {
		size++;
		curr = curr->next;
	}
	
	int values[size];
	curr = ll;
	for (int i = 0; i < size; i++) {
		values[i] = curr->cargo;
		curr = curr->next;
	}
	
	curr = ll;
	for (int i = 0; i < size; i++) {
		curr->cargo = values[size-i-1];
		curr = curr->next;
	}
	
	return ll;
}

int main() {
	ListNode* ll = init_list(5);
	add_node(ll,6);
	add_node(ll,7);
	add_node(ll,8);
	
	print_ll(ll);
		
	ListNode* new_ll = reverse_ll(ll);
	print_ll(new_ll);
}