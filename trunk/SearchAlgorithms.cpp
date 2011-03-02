#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

#include "SearchAlgorithms.h"

#define DEBUG_SORT

#ifdef DEBUG_SORT
#define debug_print(fmt,...) printf(fmt, __VA_ARGS__)
#else
#define debug_print(fmt,...)
#endif

// ˳�����:�����������в��ң��ɹ�ʱ���ؽ���λ�ã�ʧ��ʱ���� -1
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
int blocking_search(
	const int* array,
	int length,
	IndexNode* indexTableHeader,
	int key)
{
	assert(array && length >= 0 && indexTableHeader);

	int i, low, high;
	IndexNode* indexNode = indexTableHeader;

	// ˳���������������������˳��ṹ����ʹ�ö��ֲ������Ч��
	low = 0;
	while (indexNode) {
		if (indexNode->key > key) {
			high = indexNode->index - 1;
			break;
		}
		
		low = indexNode->index;

		indexNode = indexNode->next;
	}

	if (!indexNode) {
		high = length - 1;
	}

	for (i = low; i <= high; ++i) {
		if (array[i] == key) {
			return i;
		}
	}

	return -1;
}
