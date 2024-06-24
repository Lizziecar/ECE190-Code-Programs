typedef struct FancyList {
	int* ptr;
	int max_el;
	int count_el;
} FancyList;

void init_fancylist(FancyList* fl, int starting_size);
void resize(FancyList* fl, int new_size);
void append(FancyList* fl, int val);
void print_fancy_list(FancyList fl);
void clear_fancy_list(FancyList* fl);