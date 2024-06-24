#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a1.h"

/**
	Add your functions to this file.
	Make sure to review a1.h.
	Do NOT include a main() function in this file
	when you submit.
*/


//build restaurant
Restaurant* initialize_restaurant(char* name) { //easy
	Restaurant* AJ = (Restaurant*)malloc(sizeof(Restaurant));
	
	AJ->name = (char*)malloc(sizeof(char) * strlen(name));
	strcpy(AJ->name, name);
	AJ->menu = load_menu(MENU_FNAME);
	AJ->num_completed_orders = 0;
	AJ->num_pending_orders = 0;
	AJ->pending_orders = (Queue*)malloc(sizeof(Queue));
	AJ->pending_orders->head = NULL; //((AJ*).pending_orders*).head = NULL
	AJ->pending_orders->tail = NULL; //((AJ*).pending_orders*).head = NULL
	
	return AJ;
}

Menu* load_menu(char* fname) { //hard unless you know files
	//Initialize Menu
	Menu* menu = (Menu*)malloc(sizeof(Menu));
	
	//read line by line
	FILE* my_file = fopen(MENU_FNAME,"r");
	char* file_line = NULL;
	size_t line_len = 0;
		
	//create counter
	int num_of_lines = 0;
	while (getline(&file_line, &line_len, my_file) != -1) {
		num_of_lines++;
	}
	
	fclose(my_file);
	
	//Initialize Menu components
	menu->item_codes = (char**)malloc(sizeof(char*) * num_of_lines);
	menu->item_names = (char**)malloc(sizeof(char*) * num_of_lines);
	menu->item_cost_per_unit = (double*)malloc(sizeof(double) * num_of_lines);
	
	my_file = fopen(MENU_FNAME,"r");
	file_line = NULL;
	line_len = 0;
	
	int file_line_num = 0;
	int file_line_idx_comma;
	
	char* double_string = (char*)malloc(sizeof(char) * 7); //purley for testing purposes //if gradescope fails, try this
	char* ptr;
	
	while (getline(&file_line, &line_len, my_file) != -1) {
		file_line_idx_comma = 0;
		
		//Codes
		//first 2 charater is code
		menu->item_codes[file_line_num] = (char*)calloc(sizeof(char*) * ITEM_CODE_LENGTH,'a'); 		
		for (int i = 0; i < 2; i++) {
			menu->item_codes[file_line_num][i] = file_line[i];
		}
		menu->item_codes[file_line_num][ITEM_CODE_LENGTH] = '\0';
		
		//Names
		//between two commas is name
			//starting index of name is ITEM_CODE_LENGTH
		menu->item_names[file_line_num] = (char*)calloc(sizeof(char*) * MAX_ITEM_NAME_LENGTH,'a'); 		
		for (int i = ITEM_CODE_LENGTH; file_line[i] != MENU_DELIM[0]; i++) { //go from one comma to the next
			menu->item_names[file_line_num][i - ITEM_CODE_LENGTH] = file_line[i];
			file_line_idx_comma = i + 2; //saving the index of every traversal until it becomes the 2nd comma
		}
		menu->item_names[file_line_num][strlen(menu->item_names[file_line_num])] = '\0'; //error prone
		
		//Prices
		for (int i = file_line_idx_comma+1; file_line[i] != '\0'; i++) {
			double_string[i - (file_line_idx_comma + 1)] = file_line[i];
		}
		menu->item_cost_per_unit[file_line_num] = strtod(double_string,&ptr);
		
		
		//after comma, and dollar sign, rest of charcters gets atoi
		
		file_line_num++;
	}
	
	free(double_string);
	fclose(my_file);
	menu->num_items = num_of_lines;
	
	return menu;
}
Order* build_order(char* items, char* quantities) { //medium requires the string manipulation
	//initialize order
	Order* order = (Order*)malloc(sizeof(Order));
	
	//initialize num_items
	order->num_items = strlen(items) / (ITEM_CODE_LENGTH - 1);
	
	//initialize item_codes
	order->item_codes = (char**)malloc(sizeof(char*) * (order->num_items+1));
	
	//for loop to malloc all indicies in item_codes array, dynamically allocating all characters
	for (int i = 0; i < order->num_items; i++){
		order->item_codes[i] = (char*)malloc(sizeof(char) * ITEM_CODE_LENGTH);
	}
	order->item_codes[order->num_items] = '\0';
	
	//set values to item_codes
	int items_index = 0;
	for (int i = 0; i < order->num_items; i++) {
		for (int j = 0; j < ITEM_CODE_LENGTH-1; j++) {
			order->item_codes[i][j] = items[items_index];
			items_index++;
		}
		order->item_codes[i][ITEM_CODE_LENGTH-1] = '\0';
	}
	
	//set item_quantities
	order->item_quantities = (int*)malloc(sizeof(int) *  order->num_items + 1);
	int quantities_index = 0;
	int i = 0;
	char* small_string = (char*)calloc(sizeof(char) * ITEM_CODE_LENGTH, '\0');
	
	
	for (int j = 0; j < order->num_items; j++) {
		while (*(quantities+quantities_index) != MENU_DELIM[0] && quantities_index < strlen(quantities)) {
			*(small_string+i) = *(quantities+quantities_index);
			i++;
			quantities_index++;
		}
		order->item_quantities[j] = atoi(small_string);
		i = 0;
		quantities_index++;
	}
	free(small_string);
	
	return order;
}

/**
	Structure:
	
	Restaurant
		-> Queue "Pending Order"
			-> QueueNode
				-> Order
				->next
*/

//managing order
void enqueue_order(Order* order, Restaurant* restaurant) { //easy I think if you assume menu is correct
	//create new QueueNode and have order->order
	QueueNode* new_order = (QueueNode*)malloc(sizeof(QueueNode));
	new_order->order = order;
	new_order->next = NULL;
	
	if (restaurant->num_pending_orders == 0) { //empty Queue
		//set head to this node
		restaurant->pending_orders->head = new_order;
		restaurant->pending_orders->tail = new_order;
	} else { //Queue is not empty
		//put order into the queue on the tail
		QueueNode* old_tail = restaurant->pending_orders->tail;
		
		//next of old tail becomes new tail
		restaurant->pending_orders->tail = new_order;
		
		//rewire
		old_tail->next = new_order;
	}
	//update pending order amount
	restaurant->num_pending_orders++;
	
}
Order* dequeue_order(Restaurant* restaurant) { //easy if you assume menu is correct
	//remove head
	QueueNode* old_head = restaurant->pending_orders->head;
	
	//relink head
	restaurant->pending_orders->head = restaurant->pending_orders->head->next;
	
	//decrement pending orders
	restaurant->num_pending_orders--;
	//increment completed orders
	restaurant->num_completed_orders++;
	
	//if now empty
	if (restaurant->num_pending_orders == 0) {
		restaurant->pending_orders->head = NULL;
		restaurant->pending_orders->tail = NULL;
	}
	
	//return the head
	Order* dequeued_order = old_head->order;
	free(old_head);
	return dequeued_order;
}

//get functions
double get_item_cost(char* item_code, Menu* menu) { //easy??? reads from Menu
	//search for item_code within menu
	int index = 0;
	for (int i = 0; i < menu->num_items; i++) {
		if (strcmp(menu->item_codes[i],item_code) == 0) {
			index = i;
		}
	}
	return menu->item_cost_per_unit[index];
}

double get_order_subtotal(Order* order, Menu* menu) { //medium??? reads from menu and order
	double subtotal = 0;
	for (int i = 0; i < order->num_items; i++) {
		subtotal += get_item_cost(order->item_codes[i],menu) * order->item_quantities[i];
	}
	return subtotal;
}

double get_order_total(Order* order, Menu* menu) { //medium like the above one but with tax?
	double tax = (double)TAX_RATE / 100;
	return (get_order_subtotal(order,menu) * (1.00+tax));
}
int get_num_completed_orders(Restaurant* restaurant) { //easy?
	return restaurant->num_completed_orders;
}
int get_num_pending_orders(Restaurant* restaurant) { //easy?
	return restaurant->num_pending_orders;
}

//close functions
void clear_order(Order** order) {
	//free item codes:
	for (int i = 0; i < (*order)->num_items; i++){
		free((*order)->item_codes[i]);
	}
	free((*order)->item_codes);
	
	//free item_quantities
	free((*order)->item_quantities);
	
	//free order itself
	free(*order);
}

void clear_menu(Menu** menu) {
	/*
		menu->item_codes = (char**)malloc(sizeof(char*) * num_of_lines);
		menu->item_names = (char**)malloc(sizeof(char*) * num_of_lines);
		menu->item_cost_per_unit = (double*)malloc(sizeof(double) * num_of_lines);
		
			menu->item_codes[file_line_num] = (char*)calloc(sizeof(char*) * ITEM_CODE_LENGTH,'a');
			menu->item_names[file_line_num] = (char*)calloc(sizeof(char*) * MAX_ITEM_NAME_LENGTH,'a'); 
			
		
		Menu* menu = (Menu*)malloc(sizeof(Menu));
	*/
	
	for (int i = 0; i < (*menu)->num_items; i++) {
		free((*menu)->item_codes[i]);
		free((*menu)->item_names[i]);
	}
	free((*menu)->item_codes);
	free((*menu)->item_names);
	free((*menu)->item_cost_per_unit);
	free((*menu));
}
void close_restaurant(Restaurant** restaurant) {
	/*
	Restaurant* AJ = (Restaurant*)malloc(sizeof(Restaurant));
	AJ->name = (char*)malloc(sizeof(char) * strlen(name));
	AJ->pending_orders = (Queue*)malloc(sizeof(Queue));
	*/
	
	QueueNode* curr = (*restaurant)->pending_orders->head; 
	QueueNode* next = curr->next;
	
	//free linked list
	while (curr != NULL) {
		clear_order(&(curr->order));
		free(curr);
		
		curr = next;
		next = curr->next;
	}
	free((*restaurant)->pending_orders);
	clear_menu(&(*restaurant)->menu);
	free((*restaurant)->name);
	
	free(*restaurant);
	
	//free pending orders
	//free pendinerg order pointer
	//free name
	//free menu
	//free restaurant
}


//given functions
void print_menu(Menu* menu){
	fprintf(stdout, "--- Menu ---\n");
	for (int i = 0; i < menu->num_items; i++){
		fprintf(stdout, "(%s) %s: %.2f\n", 
			menu->item_codes[i], 
			menu->item_names[i], 
			menu->item_cost_per_unit[i]	
		);
	}
}


void print_order(Order* order){
	for (int i = 0; i < order->num_items; i++){
		fprintf(
			stdout, 
			"%d x (%s)\n", 
			order->item_quantities[i], 
			order->item_codes[i]
		);
	}
}


void print_receipt(Order* order, Menu* menu){
	for (int i = 0; i < order->num_items; i++){
		double item_cost = get_item_cost(order->item_codes[i], menu);
		fprintf(
			stdout, 
			"%d x (%s)\n @$%.2f ea \t %.2f\n", 
			order->item_quantities[i],
			order->item_codes[i], 
			item_cost,
			item_cost * order->item_quantities[i]
		);
	}
	double order_subtotal = get_order_subtotal(order, menu);
	double order_total = get_order_total(order, menu);
	
	fprintf(stdout, "Subtotal: \t %.2f\n", order_subtotal);
	fprintf(stdout, "               -------\n");
	fprintf(stdout, "Tax %d%%: \t$%.2f\n", TAX_RATE, order_total);
	fprintf(stdout, "              ========\n");
}