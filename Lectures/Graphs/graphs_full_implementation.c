#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_LEN 100

/**
Struct definitions for Stack implementation as Linked List
*/

typedef struct StackNode {
	int cargo; // node's index
	struct StackNode* next;
} StackNode;

typedef struct Stack {
	StackNode* top;
	int num_el;
} Stack;

/**
Struct definitions for Graph implementation as Adj Mtx
*/
typedef struct GraphNode {
	char cargo[MAX_NAME_LEN]; 
	int idx;
	struct GraphNode* prev;
	int explored;
} GraphNode;

typedef struct Graph {
	GraphNode** nodes; // dynamically allocated array of size num_nodes * sizeof(GraphNode*)
	int** adj_mtx; // dynamically allocated array of size num_nodes * sizeof(int*)
	int num_nodes;
} Graph;

/**
Stack operations
*/
Stack* initialize_stack(){
	Stack* new_stack = (Stack*)malloc(sizeof(Stack));
	new_stack->top = NULL;
	new_stack->num_el = 0;
	return new_stack;
}

void push(Stack* s, int val){
	StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
	new_node->cargo = val;
	new_node->next = s->top;
	s->top = new_node;
	s->num_el++;
}

int pop(Stack* s){
	/** Assume non-empty stack*/
	StackNode* node_to_free = s->top;
	int result = s->top->cargo;
	
	s->top = s->top->next;
	s->num_el--;
	
	free(node_to_free);
	return result;
}

/**
Graph operations
*/

void print_graph(Graph* graph){
	fprintf(stdout, "Printing graph elements...\n");
	for (int i=0; i<graph->num_nodes; i++){
		fprintf(stdout, "Index %d is: %s \n", i, graph->nodes[i]->cargo);
	}
	
	fprintf(stdout, "Printing adjacency matrix...\n");
	for (int i=0; i<graph->num_nodes; i++){
		for (int j=0; j<graph->num_nodes; j++) {
			fprintf(stdout, "%d ", graph->adj_mtx[i][j]);
		} fprintf(stdout, "\n");
	} fprintf(stdout, "\n\n");
}

void add_node(Graph* graph, GraphNode* new_node){
	/** require that the node is not present in the graph
	and that the graph's adjacency matrix
	*/
	// first, make more room in the nodes array
	graph->nodes = realloc(
		graph->nodes, 
		(graph->num_nodes + 1) * sizeof(GraphNode*)
	);
	// add the node to the nodes array
	graph->nodes[graph->num_nodes] = new_node;
	
	//add space in the adjacency matrix
	// add a row
	graph->adj_mtx = realloc(
		graph->adj_mtx, 
		(graph->num_nodes + 1) * sizeof(int*)
	);
	graph->adj_mtx[graph->num_nodes] = calloc(
		graph->num_nodes + 1, sizeof(int)
	);
	// modify existing rows to have additional column
	for (int i=0; i < graph->num_nodes; i++){
		graph->adj_mtx[i] = realloc(
			graph->adj_mtx[i], graph->num_nodes + 1 * sizeof(int)
		);
		graph->adj_mtx[i][graph->num_nodes] = 0;
	}
	
		// modify the graphnode's idx
	new_node->idx = graph->num_nodes;
	
	// increment the count of number of nodes
	graph->num_nodes++;
}

void add_edge(Graph* graph, GraphNode* node1, GraphNode* node2){
	// require that node 1 and node 2 are already in the graph
	graph->adj_mtx[node1->idx][node2->idx] = 1;
	graph->adj_mtx[node2->idx][node1->idx] = 1;
}

GraphNode* initialize_graph_node(char name[]){
	GraphNode* gn = (GraphNode*)malloc(sizeof(GraphNode));
	gn->idx = -1;
	strcpy(gn->cargo, name);
	gn->prev = NULL;
	gn->explored = 0; // not explored 
	return gn;
}

Graph* initialize_graph(){
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->nodes = NULL;
	graph->adj_mtx = NULL;
	graph->num_nodes = 0;
	return graph;
}


void delete_graph(Graph** graph){
	for (int i=0; i<(*graph)->num_nodes; i++){
		free((*graph)->nodes[i]); // remove the individual nodes
		free((*graph)->adj_mtx[i]); // remove the rows
	}	
	
	free((*graph)->nodes);
	free((*graph)->adj_mtx);
	free(*graph);
	*graph = NULL;
}
/**
DFS
*/


void reset_graph_post_dfs(Graph* graph){
	for (int i=0; i<graph->num_nodes; i++){
		graph->nodes[i]->explored = 0;
		graph->nodes[i]->prev = NULL;
	}
}


int dfs(Graph* graph, int start_idx, int end_idx){	
	/**
	Assumption: start_idx and end_idx are both valid indices in the 
	Graph
	*/
	Stack *s = initialize_stack();
	
	// stores whatever node we pop from the stack
	int curr_idx = -1;
	
	push(s, start_idx);
	while (s->num_el != 0 && curr_idx != end_idx) {
		// pop a new node
		curr_idx = pop(s);
		fprintf(stdout, "Now expanding node ... %s\n", graph->nodes[curr_idx]->cargo);
		// expand the new node by adding its neighbors to the stack
		// make sure you are not adding nodes that are already explored!!
		for (int i=0; i<graph->num_nodes; i++){
			if (graph->adj_mtx[curr_idx][i] == 1 && curr_idx != i){
				// found a valid edge, i.e. a neighbor
				// the node here is the node at index i of the nodes array
				if (graph->nodes[i]->explored == 0 && graph->nodes[i]->prev == NULL) {
					// 0 means not yet explored
					fprintf(stdout, "\tFound neighbor %s\n", graph->nodes[i]->cargo);
					push(s, i);
					graph->nodes[i]->prev = graph->nodes[curr_idx];
				}
			}
		}
		// set the explored field of the explored node
		graph->nodes[curr_idx]->explored = 1;
	}
	
	// dfs is done
	if (curr_idx == end_idx){
		fprintf(stdout, "A path was found!\n");
		// print the path
		while (curr_idx != start_idx){
			fprintf(stdout, "\t %s\n",  graph->nodes[curr_idx]->cargo);
			curr_idx = graph->nodes[curr_idx]->prev->idx;
		} fprintf(stdout, "\t %s\n",  graph->nodes[curr_idx]->cargo);
	} else {
		fprintf(stdout, "A path was not found.\n");
	}	
	
	// print out the path that i get
}


int main(){
	Graph* graph = initialize_graph();
	
	GraphNode* node0 = initialize_graph_node("Will Cluett");
	GraphNode* node1 = initialize_graph_node("Jim Davis");
	GraphNode* node2 = initialize_graph_node("Justina Lee");
	GraphNode* node3 = initialize_graph_node("Stephen Johns");
	GraphNode* node4 = initialize_graph_node("Saima Ali");
	GraphNode* node5 = initialize_graph_node("Cindy Bui");

	add_node(graph, node0);
	add_node(graph, node1);
	add_node(graph, node2);
	add_node(graph, node3);
	add_node(graph, node4);
	add_node(graph, node5);
	
	print_graph(graph);
	
	add_edge(graph, node0, node1);
	print_graph(graph);
	
	add_edge(graph, node4, node5);
	print_graph(graph);
	
	add_edge(graph, node3, node4);
	add_edge(graph, node3, node5);
	
	add_edge(graph, node3, node0);
	print_graph(graph);
	
	dfs(graph, 4, 1);

	delete_graph(&graph);
}