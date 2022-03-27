#include "utils.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void random_value_array(char **str, int len){
	srand(time(NULL));
	const char *letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";	
	int letters_len = strlen(letters);

	for (int i = 0; i < len; i++) {
		int rand_len = rand() % 5 + 2; // normally, +1 but C has an addition character at end of string '\0'
		char *rand_str = (char*)malloc(rand_len*sizeof(char));
		
		rand_str[rand_len-1] = '\0'; // end of string
		for (int j = 0; j < rand_len-1; j++) {
			rand_str[j] = letters[rand() % letters_len];
		}
		str[i] = rand_str;
	}
}

void print_array(char **str, int len) {
	for (int i = 0; i < len; i++) {
		printf("%s ", str[i]);
	}
	printf("\n");
}



