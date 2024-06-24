#include "a2.h"

int main(){
    // Task 1
    printf("%d\n", bitwise_xor(67));
    char *bin_string = xor_encrypt('C');
	printf("%s\n", bin_string);
    printf("%c\n", xor_decrypt(bin_string));
    free(bin_string);
    
    // Task 2
    char *code = gen_code("Program in C!"); //25
	//char* test_code = "1111100000111111100011010001000110101010111101011000110001110001111110100011111100001011001001111101110011011101001111011110011001000011100101010011000000000000000000000000000011111000000000001000100000000000101010000000000010001000000000001111100000000001";
    //printf("%s\n\n", code);
    //printf("%s", test_code);
    /*for (int i = 0; i < 256; i++) {
		if (code[i] != test_code[i]) {
			printf("Error at %d", i);
		}
	}*/
	char *msg = read_code(code);
    printf("%s\n", msg);
    free(msg);

    // Task 3
    char *hexcode = compress(code);
    printf("%s\n", hexcode);
    free(code);
    
    code = decompress(hexcode);
	//printf("%s\n", code);
    free(hexcode);
    char *samehexcode = compress(code);
    printf("%s\n", samehexcode);
    free(code);
    free(samehexcode);

    
    // Task 4
    printf("%d\n", calc_ld("COMMENCE", "CODING"));
    printf("%d\n", calc_ld("COMMENCE", "PROCRASTINATING"));
    return 0;
}