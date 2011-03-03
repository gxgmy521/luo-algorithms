#ifndef __SORT_ALGORITHMS_H__
#define __SORT_ALGORITHMS_H__

// 直接插入排序
void insert_sort(int* array, int length);

// 希尔排序
void shell_sort(int* array, int length);

// 冒泡排序
void bubble_sort(int* array, int length);

// 冒泡排序改进版
void bubble_sort_opt(int* array, int length);

// 快速排序
void quick_sort(int* array, int length);

// 直接选择排序
void select_sort(int* array, int length);

// 堆排序
void heap_sort(int* array, int length);

// 用分治法自下向上进行二路归并排序
void merge_sort(int* array, int length);

// 用分治法自上向下进行二路归并排序
void merge_sort_dc(int* array, int length);

// 箱/桶排序：以空间换时间
// 在这里只对正数排序
void bucket_sort(int* array, int length);

// 基数排序：以空间换时间
// 在这里只对正数排序
void radix_sort(int* array, int length);

#endif // __SORT_ALGORITHMS_H__