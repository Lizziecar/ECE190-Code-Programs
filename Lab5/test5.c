#include "lab5.h"

int main(){
    //Building the graph in Figure 1
    Graph *gr = initialize_graph();
    add(gr, "Kipling");
    add(gr, "Spadina");
    add(gr, "Yorkdale");
    
    update(gr, "Kipling", "Spadina", 12); //no adds
    update(gr, "Spadina", "Yorkdale", 8); //no adds
    update(gr, "Spadina", "Bay", 2); //one add
    update(gr, "Spadina", "Union", 4); //one add
    update(gr, "Bay", "Bloor-Yonge", 1); //one add
    update(gr, "Union", "Bloor-Yonge", 3); // no adds
    update(gr, "Bloor-Yonge", "Kennedy", 14); //one add
    update(gr, "Bloor-Yonge", "Sheppard-Yonge", 11); // one add
    update(gr, "Sheppard-Yonge", "Finch", 3); //one add
    update(gr, "Sheppard-Yonge", "Don Mills", 6); //one add
	
	//kipling, spadina, yorkdale, bay, union, bloor younge, kennedy, sheppard younge, finch, don mills //10, 3 to start with, 7 to add
    
    print_gr(gr);
    char **r = plan_route(gr, "Kipling", "Don Mills");
    print_route(r, "Kipling");
	
    //Bye bye Bay!
	printf("Bye bye Bay!\n");
    disrupt(gr, "Bay");
    print_gr(gr);
    r = plan_route(gr, "Kipling", "Don Mills");
    print_route(r, "Kipling");

    //Hello new stations
    update(gr, "Yorkdale", "Sheppard West", 5);
    update(gr, "Sheppard West", "Sheppard-Yonge", 4);
    print_gr(gr);
    r = plan_route(gr, "Kipling", "Don Mills");
    print_route(r, "Kipling");
    
    free_gr(gr);
    return 0;
}