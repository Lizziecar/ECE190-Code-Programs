#include "lab5.h"

int main () {
	Graph *gr = initialize_graph();
	add(gr, "Kipling");
    add(gr, "Spadina");
	add(gr, "Spadina");
    add(gr, "Yorkdale");
	
	for (int i=0; i<gr->count; i++){
		printf("%s station: ", gr->adj_list[i]->station);
	}
	
    return 0;
}