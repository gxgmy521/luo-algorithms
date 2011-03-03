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

void create_open_address_hash_table(
   const int* data,
   int dataLength,
   Hash_Function hashFunc,
   int tableLength,
   int* table)
{
	assert(data && table && hashFunc
		&& dataLength > 0 && tableLength > 0);

	int i, index, temp;
	const int zeroValue = -1;

	// ��ʼ�� hash table ����Ϊ������û�е�ֵ����ֵ��
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
			// ��������ɢ�н����ͻ
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

#ifdef DEBUG_SEARCH
	debug_print("\n��������Ϊ %d �� hash table��\n  ", tableLength);
	for (i = 0; i < tableLength; ++i) {
		debug_print("%d ", table[i]);
	}
	debug_print("\n");
#endif
}

int open_address_hash_search(
	 const int* table,
	 int tableLength,
	 Hash_Function hashFunc,
	 int key)
{
	assert(table && hashFunc && tableLength > 0);
	
	int index, temp;
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
		// ��������ɢ�м�������
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

	return -1;
}
