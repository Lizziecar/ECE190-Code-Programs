#include <stdio.h>
#include <stdlib.h>

typedef struct FancyList {
	int* ptr; //pointer to array
	int max_el; //capacity of array
	int count_el; //currently used
} FancyList;

void init_fancylist(FancyList* fl, int starting_size) {
	fl->ptr = (int*)malloc(sizeof(int) * starting_size);
	fl->max_el = starting_size;
	fl->count_el = 0;
}

void append(FancyList* fl, int val) {
	if (fl->count_el != fl->max_el) {
		fl->ptr[fl->count_el] = val;
		fl->count_el++;
	} else {
		fl->ptr = realloc(fl->ptr, (sizeof(int) * fl->max_el * 2)); //multipled by two because python documentation
		fl->ptr[fl->count_el] = val;
		fl->max_el = fl->max_el * 2;
		fl->count_el++;
	}
}

void print_fancy_list(FancyList fl) { //by value because read-only
	for (int i = 0; i < fl.count_el; i++) {
		fprintf(stdout, "%d ", fl.ptr[i]);
	} fprintf(stdout, "\n");
}

void clear_fancy_list(FancyList* fl) { //free the dynamic memory
	free(fl->ptr);
	fl->ptr = NULL;
}

int main() {
	FILE* fp = fopen("fl_input.txt", "r");
	char* line = NULL;
	size_t line_len = 0;
	
	FancyList fl;
	init_fancylist(&fl, 1);
	
	while(getline(&line, &line_len, fp) != -1) {
			printf("HIT");
			append(&fl, atoi(line)); //atoi("4)
			//atof("1.22") 1.22
			fprintf(stdout, "Now storing %d\n",  atoi(line));
			fprintf(stdout, "FancyList with size %d of %d\n", fl.count_el, fl.max_el);
			print_fancy_list(fl);
	}
	
	fclose(fp);
	clear_fancy_list(&fl);
}

//lol something is going on rip