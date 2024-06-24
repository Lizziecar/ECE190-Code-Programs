#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double split_bill(double base_amount, double tax_rate, double tip_rate, int num_people){
	
	double final_bill;
	
	final_bill = ((ceil((((base_amount + base_amount * tax_rate) + (base_amount + base_amount * tax_rate) * tip_rate) / num_people) * 100)))/ 100;
	
	
	
	return final_bill;
}
	

double adjust_price(double original_price) {
	
	double adjusted_price;
	
	adjusted_price = 10 * pow(original_price , 0.5);
	
	
	return adjusted_price;
}
	

int sandy_eats(char menu_item[]){
	
		for (int i = 0; i < strlen(menu_item); i++){
			if (menu_item[i] == 'j' 	|| menu_item[i] == 'k' || menu_item[i] == 'l'){
				return 0;
			}
						
	}

	if (strlen(menu_item) % 2 == 1 ){
				return 0;
	}

	
	char* fishCheck = strstr(menu_item,"fish");
	char fish[5] = "fish";
 	if (fishCheck == fish) {
		return 0;
	}	
	
	return 1;
	
}	

void imagine_fish(char thing[]){
	thing = strcat(thing,"fish");
}

