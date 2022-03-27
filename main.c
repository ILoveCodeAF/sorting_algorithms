#include <stdio.h>
#include "sort_algorithms.h"
#include "utils.h"
#include <stdlib.h>

int main(int argc, char **argv) {
	int len = 1000;
	char **str = (char**)malloc(len*sizeof(char*));
	random_value_array(str, len);
	bubble_sort(str, len);
	print_array(str, len);

	return 0;
}
