#include <stdlib.h>
#include <stdio.h>
#include "fancylist.h"

void init_fancylist(FancyList* fl, int starting_size){
	fl->ptr = (int *)malloc(sizeof(int) * starting_size);
	fl->max_el = starting_size;
	fl->count_el = 0;
}

void append(FancyList* fl, int val){
	if (fl->count_el != fl->max_el){
		fl->ptr[fl->count_el] = val;
		fl->count_el++;
	} else {
		fl->ptr = realloc(fl->ptr, (sizeof(int) * fl->max_el * 2));
		fl->ptr[fl->count_el] = val;
		fl->max_el = fl->max_el * 2;
		fl->count_el++;
	}
}

void print_fancy_list(FancyList fl){
	for (int i=0; i< fl.count_el; i++){
		fprintf(stdout, "%d ", fl.ptr[i]);
	} fprintf(stdout, "\n");
}

void clear_fancy_list(FancyList* fl){
	free(fl->ptr);
	fl->ptr = NULL;
}
