#include <stdio.h>
#include <string.h>

int main() {
	char teststring[30] = "Hello";
	char fish[5] = "fishh";
	char* resultstring = strstr(teststring,"fish");
	
	if (resultstring == fish) {
		printf("Hit");
	}
}