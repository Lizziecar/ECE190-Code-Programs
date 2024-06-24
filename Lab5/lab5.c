#include "lab5.h"

//queue stuff for Dijkstra
typedef struct QueueNode {
	Vnode* station; // node's index
	struct QueueNode* next;
} QueueNode;

typedef struct Queue {
	QueueNode* top;
	QueueNode* end;
	int num_el;
} Queue;

Queue* initialize_Queue(){
	Queue* new_Queue = (Queue*)malloc(sizeof(Queue));
	new_Queue->top = NULL;
	new_Queue->end = NULL;
	new_Queue->num_el = 0;
	return new_Queue;
}

//for testing
void print_queue(Queue* s) {
	QueueNode* curr_node = s->top;
	printf("Queue:\n");
	while (curr_node != NULL) {
		printf("%s\n", curr_node->station->station);
		curr_node = curr_node->next;
	}
}

//Queue Functions
void enqueue(Queue* s, Vnode* val){
	QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
	new_node->station = val;
	new_node->next = NULL;
	if (s->top == NULL) { //FIFO
		s->top = new_node;
		s->end = new_node;
	} else {
		s->end->next = new_node;
		s->end = new_node;
	}
	s->num_el++;
}

Vnode* dequeue(Queue* s){
	/** Assume non-empty Queue*/
	QueueNode* node_to_free = s->top;
	Vnode* result = s->top->station;
	
	s->top = s->top->next; //remove top and replace the top pointer
	s->num_el--;
	
	free(node_to_free);
	return result;
}

//sub functions for diejkstra

//function to search for a node based on a string //Do I want to implement this in all the functions?
Vnode* VnodeFromString(Graph *gr, char *station) {
	//assuming exists
	for (int i = 0; i < gr->count; i++) {
		if (strcmp(gr->adj_list[i]->station, station) == 0) {
			return gr->adj_list[i];
		}
	}
	return NULL;
}

//problems: incrementing Num_el but not actually adding BAY DAMNIT //Update: Problem has been solved, 

char **plan_route(Graph *gr, char *start, char *dest){ //hardest
    //Add code here
	
	//Dijkstra's Formula from lecture for BFS
	
	/* 
	function bfs(starting_node):
		starting_node.level = 0;
		queue := new queue
		queue.enqueue(starting_node)
		while (queue not empty):
			node := queue.dequeue()
			if node is visited:
				skip
			else if node = target:
				return True
			else:
				for all unvisited neighbors of node:
					neighbor.prev = node
					queue.enqueue(neighbor)
			node.visited = True
		return False


	Dijkstra
		-> Expand Node (if not visited)
		-> Label costs per Node (at this point) 
			-> Only if cost is less than present cost
			-> Initial costs of every Node should be max + 1 (5001)
		-> Mark visited (0 or 1)
		-> RepeatC:\Users\Owner\Documents\School_Files\ECE190\Programs\Lab5
		
		Keeping track:
		-> 	What edge you will be keeping in the updated
		-> Linked list or Array or something
		
		
	*/
	
	//house keeping,initalizing stuff cause I'm lazy to use the gr->yadayadayada
	Vnode* start_node = VnodeFromString(gr, start);
	Vnode* dest_node = VnodeFromString(gr, dest);
	Vnode* curr_node;
	Enode* curr_edge;
	Vnode* neighbor;
	int new_cost;
	
	//set values for the 3 optional variables we do not set in add()
	for (int i = 0; i < gr->count; i++) {
		if (gr->adj_list[i] != start_node) { //all the non-start_nodes
			gr->adj_list[i]->cost = 5001 * gr->count; //because all values will be equal to or less than 5000 per node
		} else { //the start Node
			gr->adj_list[i]->cost = 0;
		}
		//for all the nodes
		gr->adj_list[i]->prev = NULL;
		gr->adj_list[i]->visited = 0;
	}
	
	
	//Algorithm
	Queue* dij_queue = initialize_Queue(); //create Queue
	enqueue(dij_queue, start_node); //first enqueue
	while (dij_queue->num_el != 0) {//runs until queue empties
		//printf("\nHIT1\n");
		//print_queue(dij_queue);
		
		//dequeue
		curr_node = dequeue(dij_queue);
		//printf("Station: %s, visited: %d\n", curr_node->station, curr_node->visited);
		if (curr_node->visited == 1) { //fix this and do hittify ->Abdullah TM
			//printf("HIT2\n");
			
			//do nothing. Literally do nothing
		} else { //if not visited
			//printf("HIT5\n");
			
			curr_edge = curr_node->edges;
			while (curr_edge != NULL) {//goes through all the edges
				//printf("HIT6\n");
				
				//house keeping
				neighbor = VnodeFromString(gr,curr_edge->vertex);
				//printf("Neighbor: %s\n", neighbor->station);
				
				//set shortest distance
				new_cost = curr_node->cost + curr_edge->weight;
				//printf("Current Cost: %d\n", neighbor->cost);
				if (new_cost < neighbor->cost) { //checks if cost will change
					neighbor->cost = new_cost;
					//set prev
					neighbor->prev = curr_node;
					//printf("%s\n",neighbor->prev->station);
				}
				//printf("New Cost: %d\n", neighbor->cost);
				
				//enqueue the node
				enqueue(dij_queue, neighbor); //enqueues all neighbors
				//printf("Number in Queue %d\n", dij_queue->num_el);
				curr_edge = curr_edge->next;
			}
			curr_node->visited = 1;
		}
	}
	//once dijekstra finishes
	//printf("HIT3\n");
	char** path = NULL; //returned string
	int size_of_path = 0;
	//printf("Path: \n");
	curr_node = dest_node;
	while (curr_node != NULL) { //goes through the path backwards
		//printf("HIT4\n");
		path = realloc(path, sizeof(char*) * (size_of_path + 1)); //this gets freed in the print_path
		path[size_of_path] = (char*)malloc(sizeof(char) * MAX_LEN); //also gets freed in print_path
		strcpy(path[size_of_path], curr_node->station);
		size_of_path++;
		//printf("%s\n", curr_node->station);
		curr_node = curr_node->prev;
	}
	free(dij_queue); //free queue
	return path;	
}

void add(Graph *gr, char *station){ //should be easy
    //Add code here
	
	//Check if Vnode exists
	//create Vnode with station
	//Add it to Graph -> adj_list
	//Enode is null
	
	//Check if Vnode exists
	for (int i = 0; i < gr->count; i++) {
		if (strcmp(gr->adj_list[i]->station, station) == 0) {
			return;
		}
	}
	
	//Create Vnode
	Vnode* stouffville = (Vnode*)malloc(sizeof(Vnode));
	strcpy(stouffville->station,station);
	stouffville->edges = NULL;
	
	//Adj-List
	//if never been malloced
	gr->adj_list = (Vnode**)realloc(gr->adj_list, sizeof(Vnode*) * (gr->count + 1));
	gr->adj_list[gr->count] = stouffville;
	gr->count++;
}

void update(Graph *gr, char *start, char *dest, int weight) { //medium... 
	//Check if start and dest exists
		//If not exist create them
	//Check if Enode between the two exists
		//If weight is 0, remove the Enode
			//Rewire Enodes
		//Else change the weight
	//Else Create Enode
		//set Enode dest 
		//Rewiring
		//If Enode of Vnode exists (!= NULL)
			//Link Enode to the last Enode of the Vnode (Linked list)
		//Else Set Vnode -> edges to new Enode
		
	//Weight
	Enode* curr;
	Enode* prev;
	Enode* delete;
	Enode* delete_prev;
	int will_delete = 0;
	
	if (weight == 0) {
		//printf("In Update:\nStart: %s Dest: %s\n",start, dest);
		for (int i = 0; i < gr->count; i++) {
			//printf("What?\n");
			if (strcmp(gr->adj_list[i]->station, start) == 0) {
				curr = gr->adj_list[i]->edges;
				//printf("HIT\n");
				//printf("We got to %s\n",gr->adj_list[i]->station);
				while (curr != NULL) {
					//printf("We got to this point");
					if (strcmp(curr->vertex, dest) == 0) {
						//delete
						//check if curr == head
						delete = curr;
						delete_prev = prev;
						will_delete = 1;
						//printf("FOUND");
					}
					prev = curr;
					curr = curr->next;
				}
				if (will_delete == 1) {
					if (delete == gr->adj_list[i]->edges) {
						gr->adj_list[i]->edges = delete->next; //set new head
						free(delete); //free curr
					} else { //curr is not head
						//printf("HITTING");
						delete_prev->next = delete->next;
						free(delete); 
					}
				}
			} 
			
		} 
		return; //do nothing because start doesn't exist
	}
	else { //weight is not zero 
		//check if start exists
		int start_exists = 0; //boolean operator
		int start_index = 0; //tracking start Index
		for (int i = 0; i < gr->count; i++) {
			if (strcmp(gr->adj_list[i]->station, start) == 0) {

				start_exists = 1;
				start_index = i;
			}
		}
		if (start_exists == 0) { //if not then create start
			add(gr,start);
			start_index = (gr->count - 1);
		} 
		
		//printf("%s\n", gr->adj_list[start_index]->station); //kipling
			
		//check if dest exists
		int dest_exists = 0; //boolean operator
		for (int i = 0; i < gr->count; i++) {
			if (strcmp(gr->adj_list[i]->station,dest) == 0) {
				dest_exists = 1;
			}
		}
		if (dest_exists == 0) { //if not then create dest
			add(gr,dest);
		} 
		
		//printf("%s\n", gr->adj_list[gr->count - 1]->station);
		
		//check if edge exists
		Enode* curr = gr->adj_list[start_index]->edges; //NULL
		Enode* tail = NULL;
		Enode* edge_to_be_modified = NULL;
		int edge_exists = 0;
		while (curr != NULL) {
			//printf("HIT");
			if (strcmp(curr->vertex, dest) == 0) {
				//edge exists
				//printf("IT EXISTS");
				edge_exists = 1;
				edge_to_be_modified = curr;
			}
			tail = curr;
			curr = curr->next;
		}
		if (edge_exists == 0) {
			//Create Enode
			Enode* go_train = (Enode*)malloc(sizeof(Enode));
			//Set dest string
			strcpy(go_train->vertex,dest);
			//Set weight
			go_train->weight = weight;
			//Set nexts
			//check if tail is NULL
			if (tail == NULL) {
				gr->adj_list[start_index]->edges = go_train; //sets go_train as the head of the new linked list
			} else {
				tail->next = go_train;
			}
			go_train->next = NULL;
			edge_to_be_modified = go_train;
		}
		
		//printf("%d", edge_to_be_modified->weight);
		
		//change weight value on edge between start and dest
		//edge that we are modifying
		//no search rerquired
		//no if statements required
		edge_to_be_modified->weight = weight; //actual point of the function
	}
		
}

void disrupt(Graph *gr, char *station){ //medium
    //Add code here
	
	//search graph to find the Vnode with name station
	int station_exists = 0;
	int station_index;
	for (int i = 0; i < gr->count; i++) {
		if (strcmp(gr->adj_list[i]->station, station) == 0) {
			station_exists = 1;
			station_index = i;
		}
	}
	//If exists:
	if (station_exists == 1) {
		//free Enodes of Vnode
		Enode* prev = gr->adj_list[station_index]->edges;
		if (prev != NULL) {
			Enode* curr = prev->next;
			while (curr != NULL) {
				free(prev);
				prev = curr;
				curr = curr->next;
			}
			free(prev);
			gr->adj_list[station_index]->edges = NULL;
		}
		
		//Search through every Vnode -> Enode for Enodes with Station as destination
		for (int i = 0; i < gr->count; i++) {
			//Set those weights to 0 through update function
			update(gr, gr->adj_list[i]->station, station, 0);
		}
		
		//adjust adjlist?
		Vnode* disrupt_Vnode = gr->adj_list[station_index];
		for (int i = station_index; i < (gr->count-1); i++) {
			gr->adj_list[i] = gr->adj_list[i+1]; //shift the array over
		}
		gr->adj_list = realloc(gr->adj_list, sizeof(Vnode*) * (gr->count - 1));
		//free the Vnode
		free(disrupt_Vnode); //arcilla2@remote.ecf.utoronto.ca
		
		gr->count--;
		
	} else {
	//If not exists:
		//return;
		return;
	}
}