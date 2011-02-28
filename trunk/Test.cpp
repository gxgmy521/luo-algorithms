// Test.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SortAlgorithms.h"

typedef void (*sort_function)(int* array, int length);

void print_array(int* a, int length, const char* prefix)
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

void test(sort_function func)
{
	const int length = 10;
	int array[length] = {5, 2, 9, 10, 23, 15, 27, 1, 16, 9};
	//int array[length] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	//int array[length] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	
	print_array(array, length, "original: ");
	
	func(array, length);

	print_array(array, length, "  sorted: ");
}

int main(int argc, const char* argv[])
{
	printf("\n=== insert sort ===\n");
	test(insert_sort);

	printf("\n=== shell sort ===\n");
	test(shell_sort);

	printf("\n=== bubble sort ===\n");
	test(bubble_sort);

	printf("\n=== bubble sort optimize ===\n");
	test(bubble_sort_opt);

	printf("\n=== quick sort ===\n");
	test(quick_sort);

	getchar();
	return 0;
}