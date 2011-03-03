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

// 顺序查找:在任意序列中查找，成功时返回结点的位置，失败时返回 -1
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

// 二分查找:在有序序列中查找，成功时返回结点的位置，失败时返回 -1
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

// 分块查找/索引顺序查找
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
	// 二分查找索引表
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

	// 顺序查找索引表
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

// 散列查找
// 

// 散列函数：取余法
// h(key) = key % hashTableLength
//
int hash_remiander(int key, int hashTableLength)
{
	return key % hashTableLength;
}

// 散列函数：相乘取整法
// h(key) = [hashTableLength * (key * A - [key * A])]
// A 约等于 (根号 5 - 1)/2 = 0.61803398
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

	// 初始化 hash table 设置为序列中没有的值（零值）
	for (i = 0; i < tableLength; ++i) {
		table[i] = zeroValue;
	}

	for (i = 0; i < dataLength; ++i){
		index = (hashFunc)(data[i], tableLength);
		if (table[index] == zeroValue) {
			table[index] = data[i];
		}
		
		// 有冲突
		else {
			// 采用线性散列解决冲突
			temp = (index + 1) % tableLength;
			while (temp != index) {
				if (table[temp] == zeroValue) {
					table[temp] = data[i];
					break;
				}

				temp = (++temp) % tableLength;
			}

			// hash 表已满，报错
			if (temp == index) {
				assert(0 && "Error: Hash table is full!\n");
			}
		}
	}

#ifdef DEBUG_SEARCH
	debug_print("\n创建长度为 %d 的 hash table：\n  ", tableLength);
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

	// 可能是有冲突
	else {
		// 采用线性散列继续查找
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
