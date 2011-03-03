#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

#include "SearchAlgorithms.h"

#define DEBUG_SEARCH

#ifdef DEBUG_SEARCH
#define debug_print(fmt,...) printf(fmt, __VA_ARGS__)
#else
#define debug_print(fmt,...)
#endif

// ˳�����:�����������в��ң��ɹ�ʱ���ؽ���λ�ã�ʧ��ʱ���� -1
//
int sequential_search(const int* array, int length, int key)
{
	assert(array && length >= 0);

	int i;

	for (i = 0; i < length; ++i) {
		if (array[i] == key) {
			return i;
		}
	}

	return -1;
}

// ���ֲ���:�����������в��ң��ɹ�ʱ���ؽ���λ�ã�ʧ��ʱ���� -1
//
int binary_search(const int* array, int length, int key)
{
	assert(array && length >= 0);

	int low = 0;
	int high = length;
	int mid;

	while (low <= high) {
		mid = (low + high) >> 1;

		if (array[mid] == key) {
			return mid;
		}

		if (array[mid] > key) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	return -1;
}

// �ֿ����/����˳�����
//
int blocking_search(
	const int* array,
	int length,
	IndexNode* indexTable,
	int indexTableLength,
	int key)
{
	assert(array && length >= 0 && indexTable && indexTableLength >= 0);

#if 1
	// ���ֲ���������
	int i, mid;
	int low = 0;
	int high = indexTableLength - 1;

	while (low <= high) {
		mid = (low + high) >> 1;

		if (indexTable[mid].key == key) {
			return indexTable[mid].index;
		}
		else if (indexTable[mid].key > key) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	low = indexTable[low].index;
	high = indexTable[high].index;

#else

	// ˳�����������
	int i;
	int low = 0;
	int high = length - 1;

	for (i = 0; i < indexTableLength; ++i) {
		if (indexTable[i].key > key) {
			high = indexTable[i].index - 1;
			break;
		}

		low = indexTable[i].index;
	}
#endif

	for (i = low; i <= high; ++i) {
		if (array[i] == key) {
			return i;
		}
	}

	return -1;
}

// ɢ�в���
// 

// ɢ�к�����ȡ�෨
// h(key) = key % hashTableLength
//
int hash_remiander(int key, int hashTableLength)
{
	return key % hashTableLength;
}

// ɢ�к��������ȡ����
// h(key) = [hashTableLength * (key * A - [key * A])]
// A Լ���� (���� 5 - 1)/2 = 0.61803398
//
int hash_multi_round_off(int key, int hashTableLength)
{
	double d = key * 0.61803398;
	return (int)(hashTableLength * (d - (int)d));
}

// ̽��ʱ��ʹ�õĶ��� hash ���� h1���ܵ�̽�鷨Ϊ��
// hi = (h(key) + i * h1(key)) % hashTableLength, 0 <= i <= hashTableLength - 1
// 
// ���� h1(key) �ķ����϶࣬�����۲���ʲô�������壬������ʹ h1(key) ��ֵ��
// hashTableLength ���أ�����ʹ������ͻ��ͬ��ʵ�ַ���ȵطֲ����������У�
// ����������ͬ��ʵ�ַ��ѭ�����㡣
//
// �������� hashTableLength Ϊ�������� h1(key) ȡ 1 �� hashTableLength - 1 ֮��
//		���κ������� hashTableLength ���أ���ˣ����ǿ��Լ򵥵ؽ�������Ϊ��
//		h1(key) = key % (hashTableLength - 2) + 1
// �������� hashTableLength �� 2 �ķ��ݣ�
//      �� h1(key) ��ȡ 1 �� hashTableLength - 1֮����κ�������
//
int hash_double(int key, int hashTableLength)
{
	return key % (hashTableLength - 2) + 1;
}

//=========================================================
//					���ŵ�ַ��ɢ��
//=========================================================
// �������ÿ��ŵ�ַ����ɢ�б�
//
void create_open_address_hash_table(
   int* table,
   int tableLength,
   const int* data,
   int dataLength,
   Hash_Function hashFunc,
   Conflict_Resolution confictResolution)
{
	assert(data && table && hashFunc
		&& dataLength > 0 && tableLength > 0);

	int i, j, index, index2, temp;
	const int zeroValue = -1;	// ����Ϊ������û�е�ֵ����ֵ��

	// ��ʼ�� hash table
	for (i = 0; i < tableLength; ++i) {
		table[i] = zeroValue;
	}

	for (i = 0; i < dataLength; ++i){
		index = (hashFunc)(data[i], tableLength);
		if (table[index] == zeroValue) {
			table[index] = data[i];
		}
		
		// �г�ͻ
		else {
			// ����˫��ɢ��̽������ͻ
			// hi = (h(key) + i * h1(key)) % tableLength, 0 <= i <= tableLength - 1
			if (Conflict_Resolution_Double_Hash == confictResolution) {
				index2 = hash_double(data[i], tableLength);

				j = 1;
				while (j < tableLength) {
					temp = index + j * index2;
					if (table[temp] == zeroValue) {
						table[temp] = data[i];
						break;
					}

					++j;
				}
			}

			// ���ö���̽������ͻ
			// hi = (h(key) + i * i) % tableLength, 0 <= i <= tableLength - 1
			else if (Conflict_Resolution_Quadratic == confictResolution) {
				j = 1;
				while (j < tableLength) {
					temp = (index + j * j) % tableLength;
					if (table[temp] == zeroValue) {
						table[temp] = data[i];
						break;
					}

					++j;
				}

				// hash ���������������
				// ��������п�����δ������ֻ�Ƕ���ɢ���㷨�޷�̽�鵽��Щ�յ���
				if (temp == tableLength) {
					assert(0 && "Error: Hash table may be full!\n");
				}
			}

			// ��������̽������ͻ��Conflict_Resolution_Linear��
			// hi = (h(key) + i) % tableLength, 0 <= i <= tableLength - 1
			else {
				temp = (index + 1) % tableLength;	
				while (temp != index) {
					if (table[temp] == zeroValue) {
						table[temp] = data[i];
						break;
					}

					temp = (++temp) % tableLength;
				}

				// hash ������������
				if (temp == index) {
					assert(0 && "Error: Hash table is full!\n");
				}
			}
		}
	}

#ifdef DEBUG_SEARCH
	debug_print("\n��������Ϊ %d �� hash table��\n  ", tableLength);
	for (i = 0; i < tableLength; ++i) {
		debug_print("%d ", table[i]);
	}
	debug_print("\n");
#endif
}

// �ڲ��ÿ��ŵ�ַ����ɢ�б��в���
//
int open_address_hash_search(
	 int key,
	 const int* table,
	 int tableLength,
	 Hash_Function hashFunc,
	 Conflict_Resolution confictResolution)
{
	assert(table && hashFunc && tableLength > 0);
	
	int j, index, index2, temp;
	const int zeroValue = -1;

	index = (hashFunc)(key, tableLength);
	if (table[index] == key) {
		return index;
	}
	else if (table[index] == zeroValue) {
		return -1;
	}

	// �������г�ͻ
	else {
		// ����˫��ɢ��̽���������
		// hi = (h(key) + i * h1(key)) % tableLength, 0 <= i <= tableLength - 1
		if (Conflict_Resolution_Double_Hash == confictResolution) {
			index2 = hash_double(key, tableLength);
			j = 1;
			while (j < tableLength) {
				temp = index + j * index2;
				if (table[temp] == zeroValue) {
					return -1;
				}
				else if (table[temp] == key) {
					return temp;
				}

				++j;
			}
		}

		// ���ö���̽���������
		// hi = (h(key) + i * i) % tableLength, 0 <= i <= tableLength - 1
		else if (Conflict_Resolution_Quadratic == confictResolution) {
			j = 1;
			while (j < tableLength) {
				temp = (index + j * j) % tableLength;
				if (table[temp] == key) {
					return temp;
				}
				else if (table[index] == zeroValue) {
					return -1;
				}

				++j;
			}
		}

		// ��������̽��������ң�Conflict_Resolution_Linear��
		// hi = (h(key) + i) % tableLength, 0 <= i <= tableLength - 1
		else {
			temp = (index + 1) % tableLength;
			while (temp != index) {
				if (table[temp] == key) {
					return temp;
				}
				else if (table[temp] == zeroValue){
					return -1;
				}

				temp = (++temp) % tableLength;
			}
		}
	}

	return -1;
}

//=========================================================
//					����ַ��ɢ��
//=========================================================

// ����������������ɢ�б�
//
void create_link_hash_table(
	Hash_Node* table,
	int tableLength,
	const int* data,
	int dataLength,
	Hash_Function hashFunc)
{
	assert(table && data && hashFunc && tableLength > 0 && dataLength > 0);

	const int zeroValue = -1;	// ����Ϊ������û�е�ֵ����ֵ��
	int i, index;
	Hash_Node* node, *newNode;

	table = (Hash_Node*)malloc(tableLength * sizeof(Hash_Node));
	if (!table) {
		printf("Error: out of memory!\n");
		return;
	}

	// ��ʼ����
	for (i = 0; i < tableLength; ++i) {
		table[i].key = zeroValue;
		table[i].next = NULL;
	}

	for (i = 0; i < dataLength; ++i) {
		index = (hashFunc)(data[i], tableLength);
		if (table[index].key == zeroValue) {
			table[index].key = data[i];
		}
		else {
			node = table[index].next;
			while (node->next) {
				node = node->next;
			}

			newNode = (Hash_Node*)malloc(sizeof(Hash_Node));
			newNode->key = data[i];
			newNode->next = NULL;

			node->next = newNode;
		}
	}

#ifdef DEBUG_SEARCH
	debug_print("\n��������Ϊ %d �� hash table��\n  ", tableLength);
	for (i = 0; i < tableLength; ++i) {
		node = &table[i];
		while (node) {
			debug_print("%d ", node->key);
			node = node->next;
		}

		debug_print("\n");
	}
	debug_print("\n");
#endif
}

// ���ٲ�����������ɢ�б�
//
void destroy_link_hash_table(
	Hash_Node* table,
	int tableLength)
{
	int i;
	Hash_Node* node, *nextNode;

	for (i = 0; i < tableLength; ++i) {
		node = &table[i];
		while (node) {
			nextNode = node->next;
			free(node);

			node = nextNode;
		}
	}
}

// �ڲ�����������ɢ�б��в���
//
int open_address_hash_search(
	int key,
	const Hash_Node** table,
	int tableLength,
	 Hash_Function hashFunc)
{
	assert(table && hashFunc && tableLength > 0);

	return 0;
}