#ifndef __SORT_ALGORITHMS_H__
#define __SORT_ALGORITHMS_H__

void bubble_sort(char **str, int len);
void radix_sort(char **str, int len);
void quick_sort(char **str, int len);
void merge_sort(char **str, int len);
void selection_sort(char **str, int len);

void real_quick_sort(char **str, int left, int right);
void top_down_split_merge(char **clone_str, int left, int right, char **str);
void top_down_merge(char **str1, int left, int mid, int right, char **str2);

#endif
