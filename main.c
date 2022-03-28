#include <stdio.h>
#include "sort_algorithms.h"
#include "utils.h"
#include <stdlib.h>

int main(int argc, char **argv) {
	int len = 20000;
	char **str = (char**)malloc(len*sizeof(char*));
	random_value_array(str, len);
	print_array(str, len);
	
	char **str3 = to_clone(str, len);
	//quick_sort(str3, len);
	printf("%s time taken: %f \n", "quick sort", time_taken(&quick_sort, str3, len));
	//print_array(str3, len);

	char **str4 = to_clone(str, len);
	//merge_sort(str4, len);
	printf("%s time taken: %f \n", "merge sort", time_taken(&merge_sort, str4, len));
	//print_array(str4, len);

	char **str5 = to_clone(str, len);
	//radix_sort(str5, len);
	printf("%s time taken: %f \n", "radix sort", time_taken(&radix_sort, str5, len));
	//print_array(str5, len);
	
	char **str1 = to_clone(str, len);
	bubble_sort(str1, len);
	printf("%s time taken: %f \n", "bubble sort", time_taken(&bubble_sort, str1, len));
	//print_array(str1, len);
	
	char **str2 = to_clone(str, len);
	selection_sort(str2, len);
	printf("%s time taken: %f \n", "selection sort", time_taken(&selection_sort, str2, len));
	//print_array(str2, len);


	return 0;
}
