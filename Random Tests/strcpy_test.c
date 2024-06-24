#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char* name = "12345";
	printf("%d", strlen(name));
	char* res_name = (char*)malloc(sizeof(char) * (strlen(name)+1));
	strcpy(res_name, name);
	
	printf("%s",res_name);
	free(res_name);
}

//sftp arcilla2@remote.ecf.utoronto.ca
//ssh arcilla2@remote.ecf.utoronto.ca