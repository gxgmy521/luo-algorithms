// Test.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SortAlgorithms.h"
#include "SearchAlgorithms.h"
#include "BinaryTree.h"
#include "BTree.h"
#include "RedBlackTree.h"

//==================================================================
//					���ߺ���
//==================================================================

// ��ӡ����
// 
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

//==================================================================
//					���Ը��������㷨
//==================================================================

typedef void (*Sort_Function)(int* array, int length);

struct SortFucntionInfo {
	char * name;
	Sort_Function func;
};

SortFucntionInfo sort_function_list[] = {
	{"ֱ�Ӳ�������",				insert_sort},
	{"ϣ������",					shell_sort},
	{"ð������",					bubble_sort},
	{"ð�������Ż���",			bubble_sort_opt},
	{"��������",					quick_sort},
	{"ֱ��ѡ������",				selection_sort},
	{"������",					heap_sort},
	{"�ϲ������������϶�·�鲢",	merge_sort},
	{"�ϲ������������·���",		merge_sort_dc},
	{"Ͱ/������",				bucket_sort},
	{"��������",					radix_sort},
	{"", NULL}
};

// ����ĳ�������㷨
//
void test_sort_function(Sort_Function func)
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

// ���Ը��������㷨
//
void test_sort()
{
	for (int i = 0; sort_function_list[i].func != NULL; ++i) {
		printf("\n=== %s ===\n", sort_function_list[i].name);
		test_sort_function(sort_function_list[i].func);
	}

	const int length = 11;
	printf("\n=== �������� ===\n");
	int array2[11] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};

	print_array(array2, length, " data: ");

	counting_sort(array2, length, 100);

	print_array(array2, length, " data: ");
}

//==================================================================
//					���Ը��ֲ����㷨
//==================================================================

void test_sequential_search();
void test_binary_search();
void test_blocking_search();
void test_open_address_hash_search();
void test_link_hash_search();
void test_binary_tree_search();

typedef void (*Test_Search_Function)();

struct TestSearchFucntionInfo {
	char * name;
	Test_Search_Function func;
};

TestSearchFucntionInfo test_search_function_list[] = {
	{"˳�����",					test_sequential_search},
	{"���ֲ���",					test_binary_search},
	{"�ֿ����",					test_blocking_search},
	{"���ŵ�ַ����ϣ/ɢ�в���",	test_open_address_hash_search},
	{"��������ϣ/ɢ�в���",		test_link_hash_search},
	{"�������������",			test_binary_tree_search},
	{"", NULL},
};

// ���Ը��ֲ����㷨
//
void test_search()
{
	for (int i = 0; test_search_function_list[i].func != NULL; ++i) {
		printf("\n=== %s ===\n", test_search_function_list[i].name);
		(test_search_function_list[i].func)();
	}
}

// ����˳�����
//
void test_sequential_search()
{
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};

	int key1 = 72;
	int key2 = 55;
	int pos;

	print_array(array, length, " data: ");

	pos = sequential_search(array, length, key1);
	printf(" try searching %d, index is %d\n", key1, pos);

	pos = sequential_search(array, length, key2);
	printf(" try searching %d, index is %d\n", key2, pos);
}

// ���Զ��ֲ���
//
void test_binary_search()
{
	// ���ֲ���Ҫ����������
	const int length = 11;
	int array[length] = {8, 10, 18, 27, 32, 43, 49, 58, 65, 72, 96};

	int key1 = 72;
	int key2 = 55;
	int pos;

	print_array(array, length, " data: ");

	pos = binary_search(array, length, key1);
	printf(" try searching %d, index is %d\n", key1, pos);

	pos = binary_search(array, length, key2);
	printf(" try searching %d, index is %d\n", key2, pos);
}

// ���Էֿ����
//
void test_blocking_search()
{
	// �ֿ����Ҫ�����зֿ�����: �鳤Ϊ 3���� 4 ��
	const int length = 11;
	int array[length] = {10, 8, 18, 43, 27, 32, 58, 49, 65, 72, 69};

	int key1 = 72;
	int key2 = 55;
	int pos;

	// �����ֿ��������鳤Ϊ 3���� 4 �顣
	const int indexTableLength = 4;
	IndexNode indexNode[indexTableLength];
	indexNode[0].key = 18;
	indexNode[0].index = 2;
	indexNode[1].key = 43;
	indexNode[1].index = 3;
	indexNode[2].key = 65;
	indexNode[2].index = 8;
	indexNode[3].key = 72;
	indexNode[3].index = 9;

	print_array(array, length, " data: ");

	pos = blocking_search(array, length, indexNode, indexTableLength, key1);
	printf(" try searching %d, index is %d\n", key1, pos);

	pos = blocking_search(array, length, indexNode, indexTableLength,  key2);
	printf(" try searching %d, index is %d\n", key2, pos);
}

// ���Բ��ÿ��ŵ�ַ���Ĺ�ϣ����
// 
void test_open_address_hash_search()
{
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};

	int pos;
	int key1 = 72;
	int key2 = 55;

	print_array(array, length, " data: ");

	// ���ɱ�� hash ��������
	Hash_Function hashFunc = hash_remiander;	
	//hashFunc = hash_multi_round_off;	

	// ���ɱ��̽�鷽ʽ����
	Conflict_Resolution conflictResolution = Conflict_Resolution_Linear;
	conflictResolution = Conflict_Resolution_Quadratic;
	//conflictResolution = Conflict_Resolution_Double_Hash;
	
	// �������ŵ�ַ��ɢ�б�
	int tableLength = 17;	// ���ڶ���̽��ɢ�з���ɢ�б�ȡ����������Ϊ��
	int* hashTable = (int*)malloc(tableLength * sizeof(int));
	if (!hashTable) {
		printf("Error: out of memory!\n");
		return;
	}

	create_open_address_hash_table(
		hashTable, tableLength, array, length, 
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
}

// ���Բ����������Ĺ�ϣ����
//
void test_link_hash_search()
{
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};

	int key1 = 72;
	int key2 = 55;
	int pos;

	print_array(array, length, " data: ");

	// ���ɱ�� hash ��������
	Hash_Function hashFunc = hash_remiander;	
	//hashFunc = hash_multi_round_off;		

	// ����������ɢ�б�
	int tableLength = 7;
	Hash_Node* linkHashTable = NULL;

	create_link_hash_table(
		&linkHashTable, tableLength, array, length, hashFunc);
	if (!linkHashTable){
		printf("Failed to create link hash table!\n");
		return;
	}
	
	pos = link_hash_search(key1, linkHashTable, tableLength, hashFunc);
	printf(" try searching %d, index at hash table is %d\n", key1, pos);
	
	pos = link_hash_search(key2, linkHashTable, tableLength, hashFunc);
	printf(" try searching %d, index at hash table is %d\n", key2, pos);

	// ����������ɢ�б�
	destroy_link_hash_table(linkHashTable, tableLength);
}

//==================================================================
//					���Զ��������
//==================================================================

void test_binary_tree_search()
{
	// ���������Ҫ���¼�Ĺؼ���Ψһ�����Բ�������ͬ�ļ�¼
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 8, 72, 27, 42, 18, 58, 91};

	int key1 = 72;
	int key2 = 55;

	print_array(array, length, " data: ");

	BSTree tree = NULL;
	BSTNode* node = NULL;

	// ����������
	BST_create(&tree, array, length);
	if (!tree) {
		printf("Failed to create binary search tree!\n");
		return;
	}
	
	// ����
	node = BST_search(tree, key1);
	printf("  %s %d in binary search tree.\n",
		(NULL == node) ? "Could not find" : "Yeah! Found", key1);

	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		(NULL == node) ? "Could not find" : "Found", key2);

	// ����ڵ�
	printf(" Insert %d to binary search tree.\n", key2);
	BST_insert(&tree, key2);

	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		(NULL == node) ? "Could not find" : "Yeah! Found", key2);

	// ɾ���ڵ�
	key2 = 27;
	printf(" Remove %d from binary search tree.\n", key2);
	BST_remove(&tree, key2);

	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		(NULL == node) ? "Could not find" : "Yeah! Found", key2);

	// ���ٶ�����
	BST_destory(&tree);

	assert(NULL == tree);
}

//==================================================================
//					���� B- ��
//==================================================================
void test_BTree_search(BTree tree, int key)
{
	int pos = -1;
	BTNode*	node = BTree_search(tree, key, &pos);
	if (node) {
		printf("��%s�ڵ㣨���� %d ���ؼ��֣����ҵ��ؼ��� %c��������Ϊ %d\n",
			node->isLeaf ? "Ҷ��" : "��Ҷ��",
			node->keynum, key, pos);
	}
	else {
		printf("�������Ҳ����ؼ��� %c\n", key);
	}
}

void test_BTree_remove(BTree* tree, int key)
{
	printf("\n�Ƴ��ؼ��� %c \n", key);
	BTree_remove(tree, key);
	BTree_print(*tree);
	printf("\n");
}

void test_btree()
{
	const int length = 10;
	int array[length] = {
		'G', 'M', 'P', 'X', 'A', 'C', 'D', 'E', 'J', 'K',
		//'N', 'O', 'R', 'S', 'T', 'U', 'V', 'Y', 'Z', 'F'
	};

	BTree tree = NULL;
	BTNode* node = NULL;
	int pos = -1;
	int key1 = 'R';		// in the tree.
	int key2 = 'B';		// not in the tree.

	// ����
	BTree_create(&tree, array, length);

	printf("\n=== ���� B- �� ===\n");
	BTree_print(tree);
	printf("\n");

	// ����
	test_BTree_search(tree, key1);
	printf("\n");
	test_BTree_search(tree, key2);

	// ����ؼ���
	printf("\n����ؼ��� %c \n", key2);
	BTree_insert(&tree, key2);
	BTree_print(tree);
	printf("\n");

	test_BTree_search(tree, key2);

	// �Ƴ��ؼ���
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'M';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'E';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'G';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'A';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'D';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'K';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'P';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'J';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'C';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'X';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	// ����
	BTree_destory(&tree);
}

//==================================================================
//					���Ժ����
//==================================================================
void test_redblacktree_delete(RBTree* tree, int key)
{
	RBNode* node = RBTree_search(*tree, key);
	assert(node != RBTree_nil());

	printf("\nɾ���ڵ� %d \n", node->key);
	
	node = RBTree_delete(tree, node);
	free(node);
	
	RBTree_print(*tree);
}

void test_redblacktree()
{
	const int length = 14;
	int array[length] = {
		2, 3, 4, 6, 7, 11, 9, 18, 12, 14, 19, 17, 22, 20
	};

	int i;
	RBTree tree = RBTree_nil();
	RBNode* node = NULL;

	// ����ڵ�������
	for (i = 0; i < length; i++) {
		node = (RBNode*)malloc(sizeof(RBNode));
		node->key = array[i];
		node->color = RB_Red;
		node->parent = RBTree_nil();
		node->leftChild = RBTree_nil();
		node->rightChild = RBTree_nil();

		RBTree_insert(&tree, node);	
	}

	RBTree_print(tree);

	// �������
	node = (RBNode*)malloc(sizeof(RBNode));
	node->key = 21;

	printf("\n����ڵ� %d\n", node->key);

	RBTree_insert(&tree, node);
	RBTree_print(tree);

	// ���Ҳ���
	i = 6;
	node = RBTree_search(tree, i);

	if (node != RBTree_nil()) {
		printf("\n�ں�������ҵ��ڵ� %d\n", node->key);
	}
	else {
		printf("\n�ں�������Ҳ����ڵ� %d\n", i);
	}

	// ɾ������
	// 
	i = 4;// ȡֵ 1, 2, 3, 4���ֱ��Ӧ case 1, 2, 3, 4

	switch (i)
	{
	case 1:	// �ֵ�Ϊ��ɫ
		test_redblacktree_delete(&tree, 3);
		break;

	case 2:	// �ֵ�Ϊ��ɫ�����ֵܵ������Ӿ�Ϊ��ɫ
		test_redblacktree_delete(&tree, 12);
		break;

	case 3:	// �ֵ�Ϊ��ɫ�����ֵܵ�����Ϊ��ɫ���Һ��Ӿ�Ϊ��ɫ
		test_redblacktree_delete(&tree, 19);
		break;

	case 4:	// �ֵ�Ϊ��ɫ�����ֵܵ��Һ���Ϊ��ɫ
		test_redblacktree_delete(&tree, 9);
		break;
	}

	test_redblacktree_delete(&tree, 21);

	// ɾ����
	for (i = 0; i < length; i++) {
		node = RBTree_search(tree, array[i]);

		if (node != RBTree_nil()) {
			printf("ɾ�� %d\n", node->key);
			node = RBTree_delete(&tree, node);
			free(node);
		}
	}

	assert(tree == RBTree_nil());
}

//==================================================================
//					MAIN
//==================================================================

typedef void (*Test_Function)();

Test_Function test_function[] = {
	//test_sort,		// ���������㷨
	//test_search,		// ���Բ����㷨
	//test_btree,		// ���� B- ��
	test_redblacktree,	// ���Ժ����
	NULL
};

int main(int argc, const char* argv[])
{
	for (int i = 0; test_function[i] != NULL; i++) {
		test_function[i]();
	}

	printf("\n���Խ���\n");
	system("pause");
	return 0;
}