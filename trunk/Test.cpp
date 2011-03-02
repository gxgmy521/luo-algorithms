// Test.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SortAlgorithms.h"
#include "SearchAlgorithms.h"

//#define SORT_TEST
#define SEARCH_TEST

typedef void (*Sort_Function)(int* array, int length);
typedef int (*Search_Function)(const int* array, int length, int key);

struct SortFucntionInfo {
	char * name;
	Sort_Function func;
};

struct SearchFucntionInfo {
	char * name;
	Search_Function func;
};

SortFucntionInfo sort_function_list[] = {
	{"ֱ�Ӳ�������",			insert_sort},
	{"ϣ������",				shell_sort},
	{"ð������",				bubble_sort},
	{"ð�������Ż���",			bubble_sort_opt},
	{"��������",				quick_sort},
	{"ֱ��ѡ������",			select_sort},
	{"������",					heap_sort},
	{"�ϲ������������Ϸ���",	merge_sort},
	{"�ϲ������������·���",	merge_sort_dc},
	{"Ͱ/������",				bucket_sort},
	{"��������",				radix_sort},
	{"", NULL}
};

SearchFucntionInfo search_function_list[] = {
	{"���Բ���",				sequential_search},
	{"���ֲ���",				binary_search},
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

void test_search()
{
	const int length = 10;
	const int count = 3;
	int array[count][length] = {
		{65, 32, 49, 10, 8, 72, 27, 42, 18, 58},

		// ���ֲ���Ҫ����������
		{8, 10, 18, 27, 32, 43, 49, 58, 65, 72},
		
		// �ֿ����Ҫ�����зֿ�����: �鳤Ϊ 3���� 4 �� 
		{10, 8, 18, 43, 27, 32, 58, 49, 65, 72},
	};


	int pos, key1, key2;
	int* testArray;

	// ����˳�����
	
	testArray = array[0];
	key1 = 72;
	key2 = 55;

	printf("\n=== ˳����� ===\n");
	print_array(testArray, length, " data: ");
	pos = sequential_search(testArray, length, key1);
	printf(" try searching %d, index is %d\n", key1, pos);
	pos = sequential_search(testArray, length, key2);
	printf(" try searching %d, index is %d\n", key2, pos);

	// ���Զ��ֲ���
	testArray = array[1];
	key1 = 27;
	key2 = 55;

	printf("\n=== ���ֲ��� ===\n");
	print_array(testArray, length, " data: ");
	pos = binary_search(testArray, length, key1);
	printf(" try searching %d, index is %d\n", key1, pos);
	pos = binary_search(testArray, length, key2);
	printf(" try searching %d, index is %d\n", key2, pos);

	// ���Էֿ����
	testArray = array[2];
	key1 = 49;
	key2 = 55;
	
	//{10, 8, 18, 43, 27, 32, 58, 49, 65, 72},
	IndexNode indexNode[4];
	indexNode[0].key = 18;
	indexNode[0].index = 2;
	indexNode[0].next = &indexNode[1];
	indexNode[1].key = 43;
	indexNode[1].index = 3;
	indexNode[1].next = &indexNode[2];
	indexNode[2].key = 65;
	indexNode[2].index = 8;
	indexNode[2].next = &indexNode[3];
	indexNode[3].key = 72;
	indexNode[3].index = 9;
	indexNode[3].next = NULL;

	printf("\n=== �ֿ���� ===\n");
	print_array(testArray, length, " data: ");
	pos = blocking_search(testArray, length, &indexNode[0], key1);
	printf(" try searching %d, index is %d\n", key1, pos);
	pos = blocking_search(testArray, length, &indexNode[0],  key2);
	printf(" try searching %d, index is %d\n", key2, pos);
}

int main(int argc, const char* argv[])
{
#ifdef SORT_TEST
	for (int i = 0; sort_function_list[i].func != NULL; i++) {
		printf("\n=== %s ===\n", sort_function_list[i].name);
		test_sort(sort_function_list[i].func);
	}
#endif

#ifdef SEARCH_TEST
	test_search();
#endif

	system("pause");
	return 0;
}