#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    char* string = "405Quio in the middle0.0Abdullah is having fun";
    char* remaining_string;
    double number = strtod(string, &remaining_string);
    printf("%f\n", number);
	printf("%s\n", remaining_string);
}