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

struct SortFucntionInfo {
	char * name;
	Sort_Function func;
};

SortFucntionInfo sort_function_list[] = {
	{"ֱ�Ӳ�������",			insert_sort},
	{"ϣ������",				shell_sort},
	{"ð������",				bubble_sort},
	{"ð�������Ż���",		bubble_sort_opt},
	{"��������",				quick_sort},
	{"ֱ��ѡ������",			select_sort},
	{"������",				heap_sort},
	{"�ϲ������������Ϸ���",	merge_sort},
	{"�ϲ������������·���",	merge_sort_dc},
	{"Ͱ/������",			bucket_sort},
	{"��������",				radix_sort},
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
	const int length = 11;
	const int count = 2;
	int array[count][length] = {
		{65, 32, 49, 10, 8, 72, 27, 42, 18, 58, 91},
		{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
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
	const int length = 11;
	const int count = 3;
	int array[count][length] = {
		{65, 32, 49, 10, 8, 72, 27, 42, 18, 58, 91},

		// ���ֲ���Ҫ����������
		{8, 10, 18, 27, 32, 43, 49, 58, 65, 72, 96},
		
		// �ֿ����Ҫ�����зֿ�����: �鳤Ϊ 3���� 4 �� 
		{10, 8, 18, 43, 27, 32, 58, 49, 65, 72, 69},
	};


	int pos, key1, key2;
	int* testArray;

	//////////////////////////////////////////////////////////
	// ����˳�����
	//////////////////////////////////////////////////////////
	testArray = array[0];
	key1 = 72;
	key2 = 55;

	printf("\n=== ˳����� ===\n");
	print_array(testArray, length, " data: ");
	pos = sequential_search(testArray, length, key1);
	printf(" try searching %d, index is %d\n", key1, pos);
	pos = sequential_search(testArray, length, key2);
	printf(" try searching %d, index is %d\n", key2, pos);

	//////////////////////////////////////////////////////////
	// ���Զ��ֲ���
	//////////////////////////////////////////////////////////
	testArray = array[1];
	key1 = 27;
	key2 = 55;

	printf("\n=== ���ֲ��� ===\n");
	print_array(testArray, length, " data: ");
	pos = binary_search(testArray, length, key1);
	printf(" try searching %d, index is %d\n", key1, pos);
	pos = binary_search(testArray, length, key2);
	printf(" try searching %d, index is %d\n", key2, pos);

	//////////////////////////////////////////////////////////
	// ���Էֿ����
	//////////////////////////////////////////////////////////
	testArray = array[2];
	key1 = 72;
	key2 = 55;
	
	// ����������
	//{10, 8, 18, 43, 27, 32, 58, 49, 65, 72},
	IndexNode indexNode[4];
	indexNode[0].key = 18;
	indexNode[0].index = 2;
	indexNode[1].key = 43;
	indexNode[1].index = 3;
	indexNode[2].key = 65;
	indexNode[2].index = 8;
	indexNode[3].key = 72;
	indexNode[3].index = 9;

	printf("\n=== �ֿ���� ===\n");
	print_array(testArray, length, " data: ");
	pos = blocking_search(testArray, length, indexNode, 4, key1);
	printf(" try searching %d, index is %d\n", key1, pos);
	pos = blocking_search(testArray, length, indexNode, 4,  key2);
	printf(" try searching %d, index is %d\n", key2, pos);

	//////////////////////////////////////////////////////////
	// ���Բ��ÿ��ŵ�ַ����ɢ�в���
	//////////////////////////////////////////////////////////
	testArray = array[2];
	key1 = 72;
	key2 = 55;

	// ���ɱ�� hash ��������
	Hash_Function hashFunc = hash_remiander;	
	//hashFunc = hash_multi_round_off;	

	// ���ɱ��̽�鷽ʽ����
	Conflict_Resolution conflictResolution = Conflict_Resolution_Linear;
	conflictResolution = Conflict_Resolution_Quadratic;
	//conflictResolution = Conflict_Resolution_Double_Hash;

	printf("\n=== ���ŵ�ַ��ɢ�в��� ===\n");
	print_array(testArray, length, " data: ");

	// �������ŵ�ַ��ɢ�б�
	int tableLength = 17;	// ���ڶ���̽��ɢ�з���ɢ�б�ȡ����������Ϊ��
	int* hashTable = (int*)malloc(tableLength * sizeof(int));
	create_open_address_hash_table(
		hashTable, tableLength, 
		testArray, length, 
		hashFunc, conflictResolution);

	pos = open_address_hash_search(key1, hashTable, tableLength, 
				hashFunc, conflictResolution);
	printf(" try searching %d, index at hash is table %d\n", key1, pos);
	pos = open_address_hash_search(key2, hashTable, tableLength,
				hashFunc, conflictResolution);
	printf(" try searching %d, index at hash is table %d\n", key2, pos);

	// ɾ�����ŵ�ַ��ɢ�б�
	free(hashTable);
	hashTable = NULL;

	//////////////////////////////////////////////////////////
	// ���Բ�����������ɢ�в���
	//////////////////////////////////////////////////////////
	testArray = array[2];
	key1 = 72;
	key2 = 55;

	// ���ɱ�� hash ��������
	hashFunc = hash_remiander;	
	//hashFunc = hash_multi_round_off;	

	printf("\n=== ������ɢ�в��� ===\n");
	print_array(testArray, length, " data: ");

	// ����������ɢ�б�
	tableLength = 7;
	Hash_Node* linkHashTable = NULL;
	create_link_hash_table(
		&linkHashTable, tableLength, testArray, length, hashFunc);

	pos = link_hash_search(key1, linkHashTable, tableLength, hashFunc);
	printf(" try searching %d, index at hash table is %d\n", key1, pos);
	pos = link_hash_search(key2, linkHashTable, tableLength, hashFunc);
	printf(" try searching %d, index at hash table is %d\n", key2, pos);

	destroy_link_hash_table(linkHashTable, tableLength);


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