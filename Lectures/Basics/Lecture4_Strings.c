#include <stdio.h>
#include <string.h>

void modify_str(char s[]) {
	s[0] = 'l';
}

int main() {
	char s[100] = "dogs are cute!"; //unused array elements are assigned null '\0'
	fprintf(stdout, "My string before modification: %s\n",s);
	modify_str(s);
	fprintf(stdout, "My string after modification: %s\n", s);
	return 0;
}