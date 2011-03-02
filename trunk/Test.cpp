// Test.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SortAlgorithms.h"

typedef void (*Sort_Function)(int* array, int length);

struct FucntionInfo {
	char * name;
	Sort_Function func;
};

FucntionInfo sort_function_list[] = {
	{"insert sort",	insert_sort},
	{"shell sort", shell_sort},
	{"bubble sort", bubble_sort},
	{"bubble sort optimize", bubble_sort_opt},
	{"quick sort", quick_sort},
	{"straight selection sort", select_sort},
	{"heap sort", heap_sort},
	{"merge sort 自下向上分治", merge_sort},
	{"merge sort 自上向下分治", merge_sort_dc},
	{"bucket sort", bucket_sort},
	{"radix sort", radix_sort},
	{"", NULL}
};

void print_array(const int* a, int length, const char* prefix)
{
	assert(a && length >= 0);

	if (prefix) {
		printf("%s", prefix);
	}

	for (int i = 0; i < length; i++) {
		printf("%d ", a[i]);
	}

	printf("\n");
}

void test_sort(Sort_Function func)
{
	const int length = 10;
	const int count = 1;
	int array[count][length] = {
		//{5, 2, 9, 10, 23, 15, 27, 1, 16, 9},
		{65, 32, 49, 10, 8, 72, 27, 42, 18, 58},
		//{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
		//{10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	};
	
	for (int i = 0; i < count; i++) {
		print_array(array[i], length, " original: ");

		func(array[i], length);

		print_array(array[i], length, "   sorted: ");

		printf("\n");
	}
}

int main(int argc, const char* argv[])
{
	for (int i = 0; sort_function_list[i].func != NULL; i++) {
		printf("\n=== %s ===\n", sort_function_list[i].name);
		test_sort(sort_function_list[i].func);
	}

	system("pause");
	return 0;
}