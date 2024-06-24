#include "lab3.h"
#include <stdio.h>

//helper functions: from teaching team. Changing sort to go big->small
void merge(double result[], double arr1[], double arr2[], int n1, int n2){
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

void mergesort(double sorted[], double unsorted[], int n){
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
	double l[n_l];
	double r[n_r];
		
	//copy over arrays into l and r
	for (int i=0; i<n_l; i++){
		l[i] = unsorted[i];
	}
	for (int j=0; j<n_r; j++){
		r[j] = unsorted[n_l + j];
	}
	
	// create a new arrays to store the sorted left and
	// right subpartitions
	double sorted_l[n_l];
	double sorted_r[n_r];
	
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

void reverse_list(double reversed[], double unreversed[], int n) {
	for (int i = 0; i < n; i++) {
		reversed[i] = unreversed[n-i-1];
	}
}
//end of helper functions


//Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta){
	//for IDE check
	char* IDEcheck = "IDE";
	char* idecheck = "ide";
	if (*item == *IDEcheck || *item == *idecheck) { 
		return -1;
	}
	//Create request
	struct party_node* new_request = (struct party_node*)malloc(sizeof(struct party_node));
	//save information
	char* Item_in_party = (char*)malloc(sizeof(char)*100); //strlen()
	char* Ta_in_party = (char*)malloc(sizeof(char)*50);
	strcpy(Item_in_party, item);
	strcpy(Ta_in_party, ta);
	
	new_request->item = Item_in_party;
	new_request->price = price;
	new_request->ta = Ta_in_party;
	
	//Add request to stack
	new_request->next = *head;
	
	//change head
	*head = new_request;
	
	return 0;
}

//Remove the last item added
void remove_request(struct party_node **head){
	//check for NULL
	if (*head == NULL) {
		return;
	}
	//save next item on stack
	struct party_node* new_head = (*head)->next;
    //free top of stack
	free((*head)->ta);
	free((*head)->item);
	free(*head);
	
	//rewire
	*head = new_head;
}

//Sort party item requests - in place?
void make_sorted(struct party_node **head){
	//set an array size
	int max_size = 100;
    //turn linked list into array
	double request_prices[max_size]; //array declaration
	int j = 0; //index variable
	struct party_node* arrayCurr = *head; //the array we will getting the data from
	
	while (arrayCurr != NULL) { //copy values into array
		request_prices[j] = arrayCurr->price; //transfer price to array
		j++;
		arrayCurr = arrayCurr->next; //look at next node
	}
	int arraySize = j; //save array size
	
	//sort array (big to small)
	double smtobgsorted_prices[arraySize];
	mergesort(smtobgsorted_prices, request_prices, arraySize);
	double bgtosmsorted_prices[arraySize];
	reverse_list(bgtosmsorted_prices,smtobgsorted_prices,arraySize);
	
	//create new list based on array
	struct party_node* curr = NULL;
	struct party_node* prev = NULL;
	struct party_node* new_head = NULL;

	//locate needed node
	int found;
	struct party_node* indicated = NULL;
	
	//first instance
	found = 0;
	indicated = *head;
	while (found == 0) {
		if (indicated->price == bgtosmsorted_prices[0]) {
			found = 1;
		} 
		else {
			indicated = indicated->next;
		}
	}
	//migrate information into new stack
	new_head = (struct party_node*)malloc(sizeof(struct party_node));
	new_head->item = indicated->item;
	new_head->price = indicated->price;
	new_head->ta = indicated->ta;
	//save location for later
	prev = new_head;
	
	for (int i = 1; i < arraySize; i++) {
		found = 0;
		indicated = *head;
		while (found == 0) {
			if (indicated->price == bgtosmsorted_prices[i]) {
				found = 1;
			} 
			else {
				indicated = indicated->next;
			}
		}
		//migrate information into new stack
		curr = (struct party_node*)malloc(sizeof(struct party_node));
		curr->item = indicated->item;
		curr->price = indicated->price;
		curr->ta = indicated->ta;
		//connect nodes
		prev->next = curr;

		//save location for later
		prev = curr;
	}
	//Bottom of stack
	curr->next = NULL;
	
	//free old list
	struct party_node* freeCurr = *head;
	struct party_node* freeNext;
	while (freeCurr != NULL) {
		freeNext = freeCurr->next;
		free(freeCurr);
		freeCurr = freeNext;
	}
	
	//attatch head
	*head = new_head;

}

//Trim list to fit the budget
double finalize_list(struct party_node **head, double budget){
	//Add code here
	double budget_left = budget;
	struct party_node* curr = *head;
	struct party_node* prev = curr;
	struct party_node* head_check = *head;
	struct party_node* next = NULL;
	
	while (head_check->price > budget) {
		head_check = head_check->next;
	}
	*head = head_check;
	
	int passed_head = 0;
	while(curr != NULL) {//iterates through the whole list
		next = curr->next;
		if (curr == head_check) {
			passed_head = 1;
		}
		if (curr->price > budget_left) {
			//free curr
			free(curr->item);
			free(curr->ta);
			free(curr);
			
			if (passed_head == 1) {
				prev->next = next;
			}
		}
		else {
			budget_left -= curr->price;
			prev = curr;
		}
		curr = next;
	}
	
	return budget_left;
	
}

//Print the current list - hope this is helpful!	
void print_list(struct party_node *head){
    int count = 1;
    printf("The current list contains:\n");
    while(head != NULL){
        printf("Item %d: %s, %.2lf, requested by %s\n",
            count, head->item, head->price, head->ta);
        count++;
        head = head->next;
    }
    printf("\n\n");
    return;
}