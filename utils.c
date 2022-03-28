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


char** to_clone(char **str, int len) {
	char **clone_str = (char**) malloc(len*sizeof(char*));
	
	for (int i = 0; i < len; i++) {
		int clone_element_len = strlen(str[i])+1;
		clone_str[i] = (char*) malloc(clone_element_len*sizeof(char));
		strcpy(clone_str[i], str[i]);
	}
	return clone_str;
}

double time_taken(void (*function_ptr)(char**, int), char** str, int len) {
	clock_t t = clock();
	function_ptr(str, len);
	t = clock() - t;
	return (double)t/CLOCKS_PER_SEC;
}

Node* new(char *str) {
	Node *temp = (Node*) malloc(sizeof(Node));
	temp->str = str;
	temp->next = NULL;
	temp->tail = temp;
	return temp;
}

Node* add(Node *head, char *str) {
	if (head == NULL) {
		head = new(str);
		return head;
	}

	head->tail->next = new(str);
	head->tail = head->tail->next;
	return head;
}

Node* del(Node *head) {
	if (head == NULL) {
		return NULL;
	}
	Node *temp = head;
	if (head->next != NULL) {
		head->next->tail = head->tail;
	}

	head = head->next;
	free(temp);
	return head;
}

char* array_to_json_string(char **str, int len) {
	int json_str_len = 0;
	for (int i = 0; i < len; i++) {
		json_str_len = json_str_len + strlen(str[i]) + 3;
	}
	json_str_len += 5;

	char* json_str = (char*)malloc(json_str_len*sizeof(char));
	json_str[0] = '[';
	
	int k = 1;
	for (int i = 0; i < len; i++) {
		json_str[k] = '"';
		k += 1;
		for(int j = 0; j < strlen(str[i]); j++) {
			json_str[k] = str[i][j];
			k += 1;
		}
		json_str[k] = '"';
		k += 1;
		if (i < len-1){
			json_str[k] = ',';
			k += 1;
		}
	}
	json_str[k] = ']';
	json_str[k+1] = '\0';
	return json_str;
}

char* double_to_string(double d) {
	double num = 123412341234.123456789;
	char* output = (char*) malloc(50*sizeof(char));

	snprintf(output, 50, "%f", num);
	return output;
}
//not correct for all cases
char* pair_to_json_string(char* key, char* value) {
	int json_len = strlen(key) + strlen(value) + 4;
	char* json_str = (char*)malloc(json_len*sizeof(char));

	int k = 0;
	json_str[k] = '"';
	k += 1;
	for (int i = 0; i < strlen(key); i++) {
		json_str[k] = key[i];
		k+=1;
	}
	json_str[k] = '"';
	k+=1;
	json_str[k] = ':';
	k+=1;

	for (int i = 0; i < strlen(value); i++) {
		json_str[k] = value[i];
		k+=1;
	}
	json_str[k] = '\0';
	return json_str;
}



