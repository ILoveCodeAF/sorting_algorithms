#ifndef __UTILS_H__
#define __UTILS_H__

void random_value_array(char **str, int len); 
void print_array(char **str, int len);
char** to_clone(char **str, int len);
double time_taken(void (*function_ptr)(char**, int), char** str, int len);

struct _NODE {
	char *str;
	struct _NODE *next;
	struct _NODE *tail;
};

typedef struct _NODE Node;

Node* new(char *str);
Node* add(Node *head, char *str);
Node* del(Node *head);

#endif
