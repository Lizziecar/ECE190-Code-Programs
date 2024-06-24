#include "a2.h"

int bitwise_xor(int value){ //easy
    //add code here
	
	//find ASCII of key
	int key_ASCII = KEY;
	
	//xor value against key
	int result = value^key_ASCII;
	//return xor result
	return result;
}

char *xor_encrypt(char c){ //easy+
    //add code here
	
	//convert c to ASCII
	int c_ASCII = c;
	//xor the two
	int result = bitwise_xor(c_ASCII);
	
	//string stuff
	char* turing = (char*)malloc(sizeof(char)*8); //1 free DON'T FORGET
	//char turing[7]; -> doesn't work
	//convert to string

	for (int i = 6; i >= 0; i--) { //7 times total
		if (pow(2,i) <= result) {
			//set the string to one at that index
			turing[6-i] = '1';
			//subract from result
			result -= pow(2,i);
		} else {
			turing[6-i] = '0';
		}
	}
	
	turing[7] = '\0';
	
	//return string form
	return turing;
}

char xor_decrypt(char *s){//easy+
    //add code here
	
	//convert from string back into integer form
		//PANIC AND CRY
	int s_int = 0;
	for (int i = 0; i <= 6; i++) {
		if (s[i] == '1') {
			s_int += pow(2,6-i);
		} //else case don't increment anything at all
	}
	
	//free string
	//free(s);
	//xor new integer with KEY
	int result = bitwise_xor(s_int);
	//convert result into character
	char result_char = result;
	//return character form
	return result_char;
}

void default_squares(char *msg, int index) {
	//set default values (3 squares)
	//index is 0 pretend
	//x ... x+4 11111
	for (int i = index; i <= (index + 4); i++) {
		msg[i] = '1';
	}
	
	//x+16 ... x+20 10001
	for (int i = (index+16); i <= (index+20); i++) {
		if (i == (index+16) || i == (index+20)) {
			msg[i] = '1';
		} else {
			msg[i] = '0';
		}
	}
	
	//x+32 ... x+36 10101
	for (int i = (index+32); i <= (index+36); i++) {
		if (i == (index+33) || i == (index+35)) {
			msg[i] = '0';
		} else {
			msg[i] = '1';
		}
	}
	
	//x+48 ... x+52 10001
	for (int i = (index+48); i <= (index+52); i++) {
		if (i == (index+48) || i == (index+52)) {
			msg[i] = '1';
		} else {
			msg[i] = '0';
		}
	}
	//x+64 ... x+68 11111
	for (int i = (index+64); i <= (index + 68); i++) {
		msg[i] = '1';
	}

}

void print_sc_code(char* msg) {
	int char_counter = 0;
	for (int i = 0; i < 256; i++) {
		printf("%c", msg[i]);
		if (char_counter == 15) {
			printf("\n");
			char_counter = -1;
		}
		char_counter++;
	}
	printf("\n");
}

int* message_entry_indices() {
	int* possible_locations = (int*)malloc(sizeof(int)*180);
	int pos_loc_index = 0;
	
	//5 lines 6 spots BLOCK ONE
	int jndex = 5;
	for (int i = 0; i < 5; i++) { //per line
		for (int j = jndex; j <= (jndex+5); j++) {//goes from 5 to 10, 21 to 26... etc etc
			possible_locations[pos_loc_index] = j; //set location
			pos_loc_index++; //increment index
		}
		jndex += 16; //jumps index to next line
	}
	//6 lines 16 spots BLOCK TWO
	jndex = 80;
	for (int i = 0; i < 6; i++) { //per line
		for (int j = jndex; j <= (jndex+15); j++) {//goes from 5 to 10, 21 to 26... etc etc
			possible_locations[pos_loc_index] = j; //set location
			pos_loc_index++; //increment index
		}
		jndex += 16; //jumps index to next line
	}
	//4 lines 11 spots BLOCK THREE
	jndex = 181;
	for (int i = 0; i < 4; i++) { //per line
		for (int j = jndex; j <= (jndex+10); j++) {//goes from 5 to 10, 21 to 26... etc etc
			possible_locations[pos_loc_index] = j; //set location
			pos_loc_index++; //increment index
		}
		jndex += 16; //jumps index to next line
	}
	//1 line 10 spots BLOCK FOUR
	jndex = 245;
	for (int i = 0; i < 1; i++) { //per line //techincally useless
		for (int j = jndex; j <= (jndex+9); j++) {//goes from 5 to 10, 21 to 26... etc etc
			possible_locations[pos_loc_index] = j; //set location
			pos_loc_index++; //increment index
		}
		jndex += 16; //jumps index to next line
	}
	
	return possible_locations;
}

char *gen_code(char *msg){//med -> do the other two but more times
    //add code here;
	//Note: msg is a string
	//return string:
	char* SC_code = (char*)malloc(sizeof(char)*257); //Don't you dare forget to free
	
	for (int i = 0; i < 256; i++) {
		SC_code[i] = '0';
	}
	
	default_squares(SC_code, 0);
	default_squares(SC_code, 11);
	default_squares(SC_code, 176);
	SC_code[255] = '1';
	
	//set the actual code (conduct insertion square by square)
	//create list of possible locations
	
	int* possible_locations = message_entry_indices();
	/*for (int i = 0; i < 180; i++) {
		printf("%d\n", possible_locations[i]);
	}*/
	
	//Encrypt msg
	int string_index = 0;
	int pos_loc_index = 0;
	
	char* code_to_be_encrypted;
	while (msg[string_index] != '\0') {
		code_to_be_encrypted = xor_encrypt(msg[string_index]);
		for (int i = 0; i < 7; i++) {
			SC_code[possible_locations[pos_loc_index]] = code_to_be_encrypted[i];
			pos_loc_index++;
		}
		string_index++;
		free(code_to_be_encrypted);
		code_to_be_encrypted = NULL;
	}
	//for null terminating character
	code_to_be_encrypted = xor_encrypt(msg[string_index]); //null char
		for (int i = 0; i < 7; i++) {
			SC_code[possible_locations[pos_loc_index]] = code_to_be_encrypted[i];
			pos_loc_index++;
		}
		string_index++;
		free(code_to_be_encrypted);
		code_to_be_encrypted = NULL;
	
	SC_code[256] = '\0';
	
	//return string (256)
	
	//print_sc_code(SC_code);
	free(possible_locations);
	return SC_code;
}

char *read_code(char *code){//med
    //add code here
	
	//initialize:
	int* possible_locations = message_entry_indices(); 
	int pos_loc_index = 0;
	int found_null_char = 0;
	//We have to over malloc? no we can realloc
	char* message = (char*)malloc(sizeof(char)); //final string that will be returned
	int message_idx = 0;
	char* message_pigeon = malloc(sizeof(char) * 8); //in between string
	message_pigeon[7] = '\0'; //for strcmp
	char* null_char = xor_encrypt('\0');
	
	//iterate through possible locations
	while (found_null_char != 1) {//message_pigeon != "00000000"
		for (int i = 0; i < 7; i++) {
			message = (char*)realloc(message, sizeof(char) * (message_idx + 1));
			message_pigeon[i] = code[possible_locations[pos_loc_index]];
			pos_loc_index++;
		}
		if (strcmp(message_pigeon, null_char) != 0) { //requires both strings to have \0
			//can decrypt
			message[message_idx] = xor_decrypt(message_pigeon);
			message_idx++;
		} else {
			found_null_char = 1;
		}
	}
	message = (char*)realloc(message, sizeof(char) * (message_idx + 1));
	message[message_idx] = '\0';
	
	//put it into a return string
	free(possible_locations);
	free(null_char);
	free(message_pigeon);
	//return the string
	return message;
}

char *compress(char *code){//med ->as long as you can convert to hex
    //add code here
	
	//take 4 digit chunks of the string and convert to hexademical
	//256 is 16 lines of 16 so the hexademical will become 16 hex #s
	//guaranteed to have groups of 4 so just take the code in 4s and convert
	
	//malloc the compress string
	char* compress_str = (char*)malloc(sizeof(char)); //final string
	int comp_str_idx = 0; //index of the compressed string
	int code_idx = 0; //index of the code parameter
	int dec_hex = 0;
	//create static string of 4 char
	char* comp_pigeon = malloc(sizeof(char) * 4); //pigeon string
	//loop until null terminating character
	while (code[code_idx] != '\0') {
		//take 4 digit chunks from code into the static string
		dec_hex = 0;
		for (int i = 0; i < 4; i++) {
			//printf("%c", code[code_idx]);
			comp_pigeon[i] = code[code_idx];
			code_idx++;
		}
		//convert the 4 digits into hex
			//convert into decimal
			for (int i = 0; i < 4; i++) {
				if (comp_pigeon[i] == '1') {
					dec_hex += pow(2, 3-i); //adds the corresponding power of 2
				}
			}
			
			compress_str = realloc(compress_str, sizeof(char) * (comp_str_idx + 1));
			
			//Decimal to Hexadecimal
			if (dec_hex == 0) {
				compress_str[comp_str_idx] = '0';
			}
			if (dec_hex == 1) {
				compress_str[comp_str_idx] = '1';
			}
			if (dec_hex == 2) {
				compress_str[comp_str_idx] = '2';
			}
			if (dec_hex == 3) {
				compress_str[comp_str_idx] = '3';
			}
			if (dec_hex == 4) {
				compress_str[comp_str_idx] = '4';
			}
			if (dec_hex == 5) {
				compress_str[comp_str_idx] = '5';
			}
			if (dec_hex == 6) {
				compress_str[comp_str_idx] = '6';
			}
			if (dec_hex == 7) {
				compress_str[comp_str_idx] = '7';
			}
			if (dec_hex == 8) {
				compress_str[comp_str_idx] = '8';
			}
			if (dec_hex == 9) {
				compress_str[comp_str_idx] = '9';
			}
			if (dec_hex == 10) {
				compress_str[comp_str_idx] = 'A';
			}
			if (dec_hex == 11) {
				compress_str[comp_str_idx] = 'B';
			}
			if (dec_hex == 12) {
				compress_str[comp_str_idx] = 'C';
			}
			if (dec_hex == 13) {
				compress_str[comp_str_idx] = 'D';
			}
			if (dec_hex == 14) {
				compress_str[comp_str_idx] = 'E';
			}
			if (dec_hex == 15) {
				compress_str[comp_str_idx] = 'F';
			}
			comp_str_idx++;
	}
	//add deliminating character 
	compress_str = realloc(compress_str, sizeof(char) * (comp_str_idx + 1));
	compress_str[comp_str_idx] = '\0';
	free(comp_pigeon);
	return compress_str;
	
}

char *decompress(char *code){ //med
    //add code here
	char* decomp_str = (char*)malloc(sizeof(char));
	int code_idx = 0;
	int decomp_idx = 0;
	char hex_char;
	
	//Go through the code char by char
	while (code[code_idx] != '\0') {
		hex_char = code[code_idx];
		decomp_str = realloc(decomp_str, sizeof(char) * (decomp_idx + 4));
		if (hex_char == '0') {
			decomp_str[decomp_idx] = '0';
			decomp_str[decomp_idx+1] = '0';
			decomp_str[decomp_idx+2] = '0';
			decomp_str[decomp_idx+3] = '0';
		}
		if (hex_char == '1') {
			decomp_str[decomp_idx] = '0';
			decomp_str[decomp_idx+1] = '0';
			decomp_str[decomp_idx+2] = '0';
			decomp_str[decomp_idx+3] = '1';
		}
		if (hex_char == '2') {
			decomp_str[decomp_idx] = '0';
			decomp_str[decomp_idx+1] = '0';
			decomp_str[decomp_idx+2] = '1';
			decomp_str[decomp_idx+3] = '0';
		}
		if (hex_char == '3') {
			decomp_str[decomp_idx] = '0';
			decomp_str[decomp_idx+1] = '0';
			decomp_str[decomp_idx+2] = '1';
			decomp_str[decomp_idx+3] = '1';
		}
		if (hex_char == '4') {
			decomp_str[decomp_idx] = '0';
			decomp_str[decomp_idx+1] = '1';
			decomp_str[decomp_idx+2] = '0';
			decomp_str[decomp_idx+3] = '0';
		}
		if (hex_char == '5') {
			decomp_str[decomp_idx] = '0';
			decomp_str[decomp_idx+1] = '1';
			decomp_str[decomp_idx+2] = '0';
			decomp_str[decomp_idx+3] = '1';
		}
		if (hex_char == '6') {
			decomp_str[decomp_idx] = '0';
			decomp_str[decomp_idx+1] = '1';
			decomp_str[decomp_idx+2] = '1';
			decomp_str[decomp_idx+3] = '0';
		}
		if (hex_char == '7') {
			decomp_str[decomp_idx] = '0';
			decomp_str[decomp_idx+1] = '1';
			decomp_str[decomp_idx+2] = '1';
			decomp_str[decomp_idx+3] = '1';
		}
		if (hex_char == '8') {
			decomp_str[decomp_idx] = '1';
			decomp_str[decomp_idx+1] = '0';
			decomp_str[decomp_idx+2] = '0';
			decomp_str[decomp_idx+3] = '0';
		}
		if (hex_char == '9') {
			decomp_str[decomp_idx] = '1';
			decomp_str[decomp_idx+1] = '0';
			decomp_str[decomp_idx+2] = '0';
			decomp_str[decomp_idx+3] = '1';
		}
		if (hex_char == 'A') {
			decomp_str[decomp_idx] = '1';
			decomp_str[decomp_idx+1] = '0';
			decomp_str[decomp_idx+2] = '1';
			decomp_str[decomp_idx+3] = '0';
		}
		if (hex_char == 'B') {
			decomp_str[decomp_idx] = '1';
			decomp_str[decomp_idx+1] = '0';
			decomp_str[decomp_idx+2] = '1';
			decomp_str[decomp_idx+3] = '1';
		}
		if (hex_char == 'C') {
			decomp_str[decomp_idx] = '1';
			decomp_str[decomp_idx+1] = '1';
			decomp_str[decomp_idx+2] = '0';
			decomp_str[decomp_idx+3] = '0';
		}
		if (hex_char == 'D') {
			decomp_str[decomp_idx] = '1';
			decomp_str[decomp_idx+1] = '1';
			decomp_str[decomp_idx+2] = '0';
			decomp_str[decomp_idx+3] = '1';
		}
		if (hex_char == 'E') {
			decomp_str[decomp_idx] = '1';
			decomp_str[decomp_idx+1] = '1';
			decomp_str[decomp_idx+2] = '1';
			decomp_str[decomp_idx+3] = '0';
		}
		if (hex_char == 'F') {
			decomp_str[decomp_idx] = '1';
			decomp_str[decomp_idx+1] = '1';
			decomp_str[decomp_idx+2] = '1';
			decomp_str[decomp_idx+3] = '1';
		}
		
		decomp_idx += 4;
		code_idx++;
	}
	decomp_str = realloc(decomp_str, sizeof(char) * (decomp_idx + 1));
	decomp_str[decomp_idx] = '\0';	
	return decomp_str;
}

//find minimum of 3 values
int min (int a, int b, int c) {
	if (a <= b && a <= c) {
		return a;
	}
	if (b <= a && b <= c) {
		return b;
	}
	if (c <= b && c <= a) {
		return c;
	}
}

int calc_ld(char *sandy, char *cima){//hard
    //add code here
	
	//create 2d array
	//calculate the LD left to right up to down
	//return the bottom right most value (m and n)
	
	int n = strlen(sandy);
	int m = strlen(cima);
	
	//printf("%d\n", n);
	//printf("%d\n", m);
	
	//set up array
	int** LD = (int**)malloc(sizeof(int*) * (n+1));
	for (int i = 0; i < n+1; i++) {
		LD[i] = (int*)malloc(sizeof(int) * (m+1));
	}
	
	//fill out the first bits
	for (int i = 0; i < n+1; i++) {
		LD[i][0] = i;
		//printf("%d",i);
	}
	for (int j = 0; j < m+1; j++) {
		LD[0][j] = j;
		//printf("%d",j);
	}
	
	//fill out the rest using min
	for (int i = 1; i < n+1; i++) {
		for (int j = 1; j < m+1; j++) {
			if (sandy[i-1] == cima[j-1]) {
				LD[i][j] = LD[i-1][j-1];
			} else {
				LD[i][j] = 1 + min(LD[i-1][j-1], LD[i-1][j], LD[i][j-1]);
			}
		}
	}
	
	/*for (int i = 0; i < n+1; i++) {
		//printf("%d\n", i);
		for (int j = 0; j < m+1; j++) {
			printf("%d", LD[i][j]);
		}
		printf("\n");
	}*/
	
	//set final value
	int LD_val = LD[n][m];
	
	//free
	for (int i = 0; i < (n+1); i++) {
		free(LD[i]);
	}
	free(LD);
	
	return LD_val;
	
}