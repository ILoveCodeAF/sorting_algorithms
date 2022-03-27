#include "sort_algorithms.h"
#include <string.h> //strcmp()
#include "utils.h"


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


void quick_sort(char **str, int len) {
	real_quick_sort(str, 0, len-1);	
}

void real_quick_sort(char **str, int left, int right) {
	if (left >= right) {
		return;
	}


	int pivot = right;
	int left_partition_position = left;

	for(int i = left; i < pivot; i++) {
		if (strcmp(str[pivot], str[i]) > 0) {
			if (left_partition_position < i) {
				char *temp = str[left_partition_position];
				str[left_partition_position] = str[i];
				str[i] = temp;
			}
			left_partition_position  += 1;
		}
	}

	if (left_partition_position != pivot) {
		char *temp = str[left_partition_position];
		str[left_partition_position] = str[pivot];
		str[pivot] = temp;
	}
	pivot = left_partition_position;

	if (left < pivot)
		real_quick_sort(str, left, pivot-1);
	if (right > pivot)
		real_quick_sort(str, pivot+1, right);
}


void merge_sort(char **str, int len) {
	char **clone_str = to_clone(str, len);
	top_down_split_merge(clone_str, 0, len, str);
}

void top_down_split_merge(char **clone_str, int left, int right, char **str) {
	if (right - left <= 1)
		return;

	int mid = (left + right) / 2;
	top_down_split_merge(str, left, mid, clone_str);
	top_down_split_merge(str, mid, right, clone_str);

	top_down_merge(clone_str, left, mid, right, str);
}

void top_down_merge(char **str1, int left, int mid, int right, char **str2) {
	int i = left, j = mid;

	for (int k = left; k < right; k++) {
		if (i < mid && (j >= right || strcmp(str1[i], str1[j]) < 0 )) {
			str2[k] = str1[i];
			i += 1;
		}
		else {
			str2[k] = str1[j];
			j += 1;
		}
	}
}



void selection_sort(char **str, int len) {
	for(int i = 0; i < len; i++) {
		int min_position = i;

		for (int j = i+1; j < len; j++) {
			if (strcmp(str[min_position], str[j]) > 0) {
				min_position = j;
			}
		}

		if (i != min_position) {
			char *temp = str[i];
			str[i] = str[min_position];
			str[min_position] = temp;
		}
	}
}

