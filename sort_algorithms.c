#include "sort_algorithms.h"
#include "string.h" //strcmp()


void bubble_sort(char **str, int len) {
	int result_cmp_strs = 0;
	
	for(int i = 0; i < len; i++) {
		for(int j = len-1; j > i; j--) {
			result_cmp_strs = strcmp(str[j], str[j-1]);
			
			// result_cmp_strs < 0 <=> str[j] < str[j-1]
			if (result_cmp_strs < 0) {
				char *temp = str[j-1];
				str[j-1] = str[j];
				str[j] = temp;
			}
		}
	}
}


void radix_sort(char **str, int len) {}
void quick_sort(char **str, int len) {}
void merge_sort(char **str, int len) {}
void selection_sort(char **str, int len) {}

