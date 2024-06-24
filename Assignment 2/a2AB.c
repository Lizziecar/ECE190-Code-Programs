#include "a2.h"

int bitwise_xor(int value){ //EASY 
	int key_ASCII = KEY;
	int XOR_result_decimal = value ^ key_ASCII;

	return XOR_result_decimal;
}
//find ASCII of key
//perform a bit-wise XOR operation on <value> with the ASCII value of the KEY character defined in a2.h.

char *xor_encrypt(char c){
    //convert c ASCII
	int c_ASCII = c;
	//convert KEY to ASCII
	int key_ASCII = KEY;
	//XOR the two
	int encryption_result = c_ASCII ^ key_ASCII;
	
	char *Turing = (char*)malloc(sizeof(char) * 8);
	//char Turing[7]; static array;  DOES NOT WORK APPARENTLY



	for (int i = 6; i >= 0 ; i-- ){
		if (pow(2,i) <= encryption_result){
			Turing[6-i] = '1';
			//subtract from result
			encryption_result -= pow(2,i);
		}else {
			Turing[6-i] = '0';
		}
	}
	Turing[7] = '\0';
	//return string form
	return Turing;
}
//return a pointer to the binary result of a bit-wise XOR operation on the ASCII value of <c> with the ASCII value of KEY

char xor_decrypt(char *s){    //where *s is *Turing
	//convert from string back into integer form ----PANIC AND CRY
	
	int s_int = 0;  //is going to take on the decimal integer value corresponding to the binary string s;

	
	for(int i = 0; i <= 6; i++){
		if (s[i] == '1'){
			s_int += pow(2,6-i);
		}//else case, increment s_int by 0 * something
	}
		
	
	//XOR new integer with KEY
	int result = bitwise_xor(s_int);
	//convert result into character
	char char_result = result;
	//return character form;
	return char_result;
}
/*Return the character obtained after evaluating the ASCII value resulting from
performing a bit-wise XOR operation on the value represented by <s> with the ASCII value
of KEY*/


void default_sqaures(char *msg, int index){
	//set default larger three subsqaures
	// 5 sets of 5 entires that form the square, hard coded, and can be passed on for different starting indicies 
	
	//from x = 0 to 4
	for (int i = index; i <= (index + 4); i++){
		msg[i] = '1';
	}	
	
	for (int i = (index + 16); i <= (index + 20); i++){
		if (i == index + 16 || i == index + 20){
			msg[i] = '1';
		}else{
			msg[i] = '0';
		}
	}
	
	for (int i = (index + 32); i <= (index + 36); i++){
		if (i == (index + 32) || i == (index + 34) || i == (index + 36)){
			msg[i] = '1';
		}else{
			msg[i] = '0';
		}
	}
	
	for (int i = (index + 48); i <= (index + 52); i++){
		if (i == (index + 48) || i == (index + 52)){
			msg[i] = '1';
		}else{
			msg[i] = '0';
		}
	}
	
	for (int i = index + 64; i <= (index + 68); i++){
		msg[i] = '1';
	}
}

int* message_entry_indicies(){
	//set the actual code, conduct insertion square by sqaure
	//create list of possible locations, sqaures not occupied by 'default' entries
	
	int* possible_locations  = (int*)malloc(sizeof(int) * 180);
	int possible_locations_indicies = 0;
	
	
	/*BLOCK 1 */
	int jndex = 5; //starting point for encrypted entries in the rows of block 1
	for (int i = 0; i < 5; i++){ //per line 
		for (int j = jndex; j <= (jndex + 5); j++){ //successive elements in each row of block, 5-10, 21-26, 37-42
			possible_locations[possible_locations_indicies] = j;  //set 5th entry to index 5......
			possible_locations_indicies++;
		} 
		jndex += 16;
	}
	
	
	/*BLOCK 2*/
	jndex = 80; //starting point for encrypted entries in the rows of block 2
	for (int i = 0; i < 6; i++){ //per line 
		for (int j = jndex; j <= (jndex + 15); j++){ //successive elements in each row of block, 80-95, 96-111, ....144-159
			possible_locations[possible_locations_indicies] = j;  //set 80th entry to index 80......
			possible_locations_indicies++;
		} 
		jndex += 16;
	}
	
	/*BLOCK 3*/
	jndex = 181; //starting point for encrypted entries in the rows of block 3
	for (int i = 0; i <4 ; i++){ //per line 
		for (int j = jndex; j <= (jndex + 10); j++){ //successive elements in each row of block, 165-175, 181-191, ... 229-239
			possible_locations[possible_locations_indicies] = j;  //set 165th entry to index 165......
			possible_locations_indicies++;
		} 
		jndex += 16;
	}
	
	/*BLOCK 4*/
	jndex = 245;  //remaining last line
	for (int j = jndex; j <= (jndex + 9); j++){
			possible_locations[possible_locations_indicies] = j;  //set 165th entry to index 165......
			possible_locations_indicies++;
		}
		
	return possible_locations;
}

char *gen_code(char *msg){
	//set the largest square first, smaller subsqaures as well
	//note msg is a string
	//conduct the insertion, while iterating through the array manually, (square by sqaure);
	//return the string;
	
	char* SC_code = (char*)malloc(sizeof(char) * 257); //Joaquinism: FREE
	
	for (int i = 0; i < 256 ; i++){
		SC_code[i] = '0';
	}
	
	//SET DFEAULT/TEMPLATE VALUES
	
	default_sqaures(SC_code , 0);
	default_sqaures(SC_code, 11);
	default_sqaures(SC_code, 176);
	
	SC_code[255] = '1';	
	
	//set the actual code, conduct insertion square by sqaure
	//create list of possible locations, sqaures not occupied by 'default' entries
	//CALL UP UPON message_entry_indicies
	
	int* possible_locations = message_entry_indicies();
	int possible_locations_indicies = 0;
	
	//ENCRYPT THE MESSAGE, CALL UPON xor_encrypt
	
	int string_index = 0;
	char* code_to_be_encrypted;
	while (msg[string_index] != '\0'){
		code_to_be_encrypted = xor_encrypt(msg[string_index]);
		for (int i = 0 ; i < 7 ; i++){
			SC_code[possible_locations[possible_locations_indicies]] = code_to_be_encrypted[i];
			possible_locations_indicies++;
		}
		string_index++;
		free(code_to_be_encrypted);
		code_to_be_encrypted = NULL;
	}
	
	//for null terminating character
	code_to_be_encrypted = xor_encrypt(msg[string_index]);
		for (int i = 0 ; i < 7 ; i++){
			SC_code[possible_locations[possible_locations_indicies]] = code_to_be_encrypted[i];
			possible_locations_indicies++;
		}
		string_index++;
		free(code_to_be_encrypted);
		code_to_be_encrypted = NULL;
	
	SC_code[256] = '\0';
	
	free(possible_locations);
	return SC_code;
}


char *read_code(char *code){
    //initialize
	int* possible_locations = message_entry_indicies();
	int possible_locations_indicies = 0;
	int found_null_terminating_character = 0;
	
	char* message = (char*)malloc(sizeof(char)); //pointer/ string that will be returned
	char* message_pigeon; //checking whether null terminating character is present in 7 char batch
	int message_index = 0;
	
	//iterate through possible locations
	while(found_null_terminating_character != 1){
		//every 7 characters decrypt
		for (int i = 0 ; i < 7 ; i++){
				message = (char*)realloc(message, sizeof(char) * (message_index + 1));
				message_pigeon[i] = code[possible_locations[possible_locations_indicies]];
				possible_locations_indicies++;
			}
			if (strcmp(message_pigeon, "0000000") != 0){
				//decrypt message piegon
				message[message_index] = xor_decrypt(message_pigeon);
				message_index++;
			}//until the null terminating character is found
			else{
				found_null_terminating_character = 1;	
			}
		}
	message = (char*)realloc(message, sizeof(char) * (message_index + 1));
	message[message_index] = '\0';
	
	//put it into a return string
	
	free(possible_locations);
	//return the string
	return message;
}

char *compress(char *code){
	char* compress_str = (char*)malloc(sizeof(char)); //final string of hexadecimal
	
	//convert every successive 4 bits of binary into a decimal first, and then into hexadecimal
	char* compress_pigeon = malloc(sizeof(char) *4);
	int decimal_intermediate = 0;
	int compress_str_idx = 0;
	
	int code_idx = 0;
	
	while(code[code_idx] != '\0'){
		decimal_intermediate = 0;
		for(int i = 0; i < 4; i++){
			compress_pigeon[i] = code[code_idx];
			code_idx++;
		}
		//convert the 4 digits into decimal
	
		for (int i = 0 ; i < 4; i++){
			if (compress_pigeon[i] == '1'){      //WHAT A SHAME
				decimal_intermediate += pow(2, 3 - i);
			}
		}
		
		//convert decimal to hexadecimal	
			compress_str = (char*)realloc(compress_str, sizeof(char) * (compress_str_idx + 1));
		    if (decimal_intermediate == 0) {
                compress_str[compress_str_idx] = '0';
            }
            if (decimal_intermediate == 1) {
                compress_str[compress_str_idx] = '1';
            }
            if (decimal_intermediate == 2) {
                compress_str[compress_str_idx] = '2';
            }
            if (decimal_intermediate == 3) {
                compress_str[compress_str_idx] = '3';
            }
            if (decimal_intermediate == 4) {
                compress_str[compress_str_idx] = '4';
            }
            if (decimal_intermediate == 5) {
                compress_str[compress_str_idx] = '5';
            }
            if (decimal_intermediate == 6) {
                compress_str[compress_str_idx] = '6';
            }
            if (decimal_intermediate == 7) {
                compress_str[compress_str_idx] = '7';
            }
            if (decimal_intermediate == 8) {
                compress_str[compress_str_idx] = '8';
            }
            if (decimal_intermediate == 9) {
                compress_str[compress_str_idx] = '9';
            }
            if (decimal_intermediate == 10) {
                compress_str[compress_str_idx] = 'A';
            }
            if (decimal_intermediate == 11) {
                compress_str[compress_str_idx] = 'B';
            }
            if (decimal_intermediate == 12) {
                compress_str[compress_str_idx] = 'C';
            }
            if (decimal_intermediate == 13) {
                compress_str[compress_str_idx] = 'D';
            }
            if (decimal_intermediate == 14) {
                compress_str[compress_str_idx] = 'E';
            }
            if (decimal_intermediate == 15) {
                compress_str[compress_str_idx] = 'F';
            }
            compress_str_idx++;
	}
	compress_str = (char*)realloc(compress_str, sizeof(char) * (compress_str_idx + 1));
	compress_str[compress_str_idx] = '\0';
	
	//printf("%s", compress_str);
	
	free(compress_pigeon);
	return compress_str;
}

char *decompress(char *code){
    //add code here
}

int calc_ld(char *sandy, char *cima){
    //add code here
}