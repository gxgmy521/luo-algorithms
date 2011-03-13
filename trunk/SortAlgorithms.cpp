#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

#include "SortAlgorithms.h"

#define DEBUG_SORT

#ifdef DEBUG_SORT
#define debug_print(fmt,...) printf(fmt, ## __VA_ARGS__)
#else
#define debug_print(fmt,...)
#endif

// ֱ�Ӳ�������
//
void insert_sort(int* array, int length)
{
	assert(array && length >= 0);

	int i, j, temp;
	for (i = 1; i < length; ++i) {
		temp = array[i];
		j = i - 1;

		while (j >= 0 && temp < array[j]) {
			array[j + 1] = array[j];
			--j;
		}

		array[j + 1] = temp;
	}
}

// ϣ������
//
void shell_sort(int* array, int length)
{
	assert(array && length >= 0);

	int i, j , temp;
	int increment = length;

	do {
		increment = increment / 3 + 1;

		// ϣ�������е�һ������increment Ϊ��ǰ����
		// �� [increment, length - 1] ֮��ļ�¼�ֱ������鵱ǰ��������
		for (i = increment; i < length; ++i) {
			temp = array[i];
			j = i - increment;

			while (j >= 0 && temp < array[j]) {
				array[j + increment] = array[j];
				j -= increment;
			}

			array[j + increment] = temp;
		}
	} while (increment > 1);
}

// ð������
//
void bubble_sort(int* array, int length)
{
	assert(array && length >= 0);

	int i, j, temp;
	bool exchange;

	for (i = 1; i < length; ++i) {
		exchange = false;

		for (j = length - 1; j >= i; --j) {
			if (array[j] < array[j - 1]) {
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;

				exchange = true;
			}
		}

		if (!exchange) {
			break;
		}
	}
}

// ð������Ľ���
//
void bubble_sort_opt(int* array, int length)
{
	assert(array && length >= 0);

	int i, j, temp;
	bool exchange;
	int lastExchange = 1;

	for (i = 1; i < length;) {
		exchange = false;

		for (j = length - 1; j >= i; --j) {
			if (array[j] < array[j - 1]) {
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;

				lastExchange = j;
				exchange = true;
			}
		}

		if (!exchange) {
			break;
		}

		i = lastExchange + 1;
	}
}


// �� [low, high] �����֣������ػ�׼��¼��λ��
int quick_partition(int* array, int low, int high)
{
	assert(array && low >= 0 && low <= high);

	int pivot = array[low]; // ������ĵ� 1 ����¼��Ϊ��׼

	while (low < high) {
		while (low < high && array[high] >= pivot) {
			--high;
		}

		if (low < high) {
			array[low++] = array[high];
		}

		while (low < high && array[low] <= pivot) {
			++low;
		}

		if (low < high) {
			array[high--] = array[low];
		}
	}

	array[low] = pivot;

	return low;
}

void quick_sort_impl(int* array, int low, int high)
{
	if (low < high) {
		int pivotPos = quick_partition(array, low, high);

		quick_sort_impl(array, low, pivotPos - 1);
		quick_sort_impl(array, pivotPos + 1, high);
	}
}

// ��������
//
void quick_sort(int* array, int length)
{
	assert(array && length >= 0);

	quick_sort_impl( array, 0, length - 1);
}


// ֱ��ѡ������
//
void selection_sort(int* array, int length)
{
	assert(array && length >= 0);

	int i, j, k, temp;

	for (i = 0; i < length - 1; ++i) {
		k = i;

		for (j = i + 1; j < length; ++j) {
			if (array[j] < array[k]) {
				k = j;
			}
		}

		if (k != i) {
			temp = array[i];
			array[i] = array[k];
			array[k] = temp;
		}
	}
}


// ɸѡ�������ѣ��� [low] ֮�⣬[low] ���������Ӿ����Ǵ����
void adjust_heap(int* heap, int low, int high)
{
	assert(heap);

#if 1	// ѭ��ʵ��

	int i = low;
	int j = 2 * i;
	int temp = heap[i];

	while (j <= high) {
		// �����������ӣ�j Ϊ�����д���Ǹ����±�
		if (j < high && heap[j] < heap[j + 1]) {
			j = j + 1;
		}

		// ���Ƕ�
		if (temp >= heap[j]) {
			break;
		}

		// ����ɸѡ
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * i;
		}
	}

	heap[i] = temp;

#else	// �ݹ�ʵ��

	int i = low;
	int j = 2 * i;
	int temp = heap[i];

	if (j >= high) {
		return;
	}

	// �����������ӣ�j Ϊ�����д���Ǹ����±�
	if (j < high && heap[j + 1] > heap[j]) {
		j = j + 1;
	}

	// �Ѿ�Ϊ�ѣ��������
	if (heap[low] >= heap[j]) {
		return;
	}

	heap[i] = heap[j];
	heap[j] = temp;

	// ����֮��[j, high] ���ܲ�������ˣ����������
	adjust_heap(heap, j, high);

#endif
}

// ֻ��һ���������Ƕѣ�������ȫ�������У�������� i > n/2 �Ľ�㶼��Ҷ�ӣ�
// �������Щ���Ϊ�������������Ƕѡ�����������ֻ�����ν������Ϊ
// n/2, n/2 - 1, ��, 0 �Ľ����Ϊ��������������Ϊ�Ѽ��ɡ�
void build_heap(int* heap, int length)
{
	assert(heap && length >= 0);

	int i;

	for(i = length / 2; i >= 0; --i) {
		adjust_heap(heap, i, length - 1);
	}
}


// ������
//
void heap_sort(int* array, int length)
{
	assert(array && length >= 0);

	int i, temp;

	// �� [0, length - 1] ���ɳ�ʼ��
	build_heap(array, length);

	// �Ե�ǰ������ [0, i - 1] ���ж����򣬹��� length - 1 �ˡ�
	for(i = length - 1; i > 0; --i) {
		// ���Ѷ��Ͷ������һ����¼����
		temp = array[0];
		array[0] = array[i];
		array[i]= temp;

		// �� [0, i - 1] ���µ���Ϊ�ѣ����� [0] ����Υ��������
		adjust_heap(array, 0, i - 1);
	}
}


void merge(int* array, int low, int mid, int high)
{
	assert(array && low >= 0 && low <= mid && mid <= high);

	int* temp = (int*)malloc((high - low + 1) * sizeof(int));
	if (!temp) {
		printf("Error:out of memory!");
		return;
	}

	int i = low;
	int j = mid + 1;
	int index = 0;

	while (i <= mid && j <= high) {
		if (array[i] <= array[j]) {
			temp[index++] = array[i++];
		}
		else {
			temp[index++] = array[j++];
		}
	}

	while (i <= mid) {
		temp[index++] = array[i++];
	}

	while (j <= high) {
		temp[index++] = array[j++];
	}

	memcpy((void*)(array + low), (void*)temp, (high - low + 1) * sizeof(int)) ;

	free(temp);
}

// �� [0, length - 1] ��һ�˹鲢����Ϊ n  �Ĺ鲢����
void merge_pass(int* array, int length, int n)
{
	assert(array && length >= 1 && n >= 1);

	int i;
	int sortLength = 2 * n;

	// �鲢����Ϊ n ����������������
	for(i = 0; i + sortLength - 1 < length; i = i + sortLength) {
		merge(array, i, i + n - 1, i + sortLength - 1);
	}

	// �� i + n - 1 < length - 1����ʣ��һ�����ļ��ֿգ�����鲢��
	// �������������У����к�һ������С�� n, �鲢������������С�
	if (length - 1 > i + n - 1) {
		merge(array, i, i + n - 1, length - 1);
	}
}

// �÷��η��������Ͻ��ж�·�鲢����
//
void merge_sort(int* array, int length)
{
	assert(array && length >= 0);

	int n;

	for(n = 1; n < length; n = (n << 1)) {
		merge_pass(array, length, n);
	}
}


void merge_sort_dc_impl(int* array, int low, int high)
{
	assert(array && low >= 0);

	int mid;
	if (low < high) {
		mid = (low + high) >> 1;

		merge_sort_dc_impl(array, low, mid);
		merge_sort_dc_impl(array, mid + 1, high);

		merge(array, low, mid, high);
	}
}

// �÷��η��������½�������
void merge_sort_dc(int* array, int length)
{
	assert(array && length >= 0);

	merge_sort_dc_impl(array, 0, length - 1);
}

// array �м�¼��ֵ������ڷ�Χ [0, k] ֮�䡣
//
void counting_sort(int* array, int length, int k)
{
	int* temp = NULL;	// a copy of array.
	int* counts = NULL;	// for counting.
	int i;

	temp = (int*)malloc(sizeof(int) * length);
	if (!temp) {
		printf("Error: out of memory!\n");
		return;
	}

	counts = (int*)calloc(sizeof(int), k + 1);
	if (!counts) {
		printf("Error: out of memory!\n");

		if (temp) {
			free(temp);
		}
		return;
	}

	memcpy(temp, array, sizeof(int) * length);

	// ����
	for (i = 0; i < length; ++i) {
		++counts[temp[i]];
	}

	// ȷ��˳��
	for (i = 1; i <= k; ++i) {
		counts[i] += counts[i - 1];
	}

	// ����
	for (i = 0; i < length; ++i) {
		array[counts[temp[i]] - 1] = temp[i];
		--counts[temp[i]];
	}

	if (temp) {
		free(temp);
	}

	if (counts) {
		free(counts);
	}
}

// ��/Ͱ����ͻ��������Կռ任ʱ��
//
struct bucket_node {
	int key;
	bucket_node* next;
};

// ȡ���������������λ��
int get_max_digital_count(int* array, int length)
{
	assert(array && length > 0);

	int i = 0;
	int max = array[0];
	int maxDigitalCount = 1;

	for (i = 1; i < length; i++) {
		if (max < array[i]) {
			max = array[i];
		}
	}

	while ((max / 10) > 0) {
		max %= 10;
		++maxDigitalCount;
	}

	return maxDigitalCount;
}

// ȡ���� num �дӵ͵��ߵ� n λ�ϵ�����
int get_ditital_at(int num, int n)
{
	while (--n > 0) {
		num /= 10;
	}

	return (num % 10);
}

// ��/Ͱ����
//
void bucket_sort(int* array, int length)
{
	assert(array && length >= 0);

	if (length <= 1) {
		return;
	}

	int i, index;
	bucket_node* temp = NULL;
	bucket_node bucket[10] = {0, };	// �������ָ��� 0 ~ 9 ���� 10 ��Ͱ

	int count = get_max_digital_count(array, length);

	// �������ݽڵ�
	bucket_node* data = (bucket_node*)malloc(length * sizeof(bucket_node));
	if (!data) {
		printf("Error: out of memory!\n");
		return;
	}

	for (i = 0; i < length; i++) {
		data[i].key = array[i];
		data[i].next = NULL;
	}

	// ����
	for (i = 0; i < length; i++) {
		index = get_ditital_at(data[i].key, count);
		if (bucket[index].next == NULL) {
			bucket[index].next = &data[i];
		}
		else {
			temp = &bucket[index];
			while (temp->next != NULL && temp->next->key < data[i].key) {
				temp = temp->next;
			}

			data[i].next = temp->next;
			temp->next = &data[i];
		}
	}

	// �ռ�
	index = 0;
	for (i = 0; i < 10; i++) {
		temp = bucket[i].next;
		while (temp != NULL) {
			array[index++] = temp->key;
			temp = temp->next;
		}
	}


	free(data);
}

// ��������
//
void radix_sort(int* array, int length)
{
	assert(array && length >= 0);

	if (length <= 1) {
		return;
	}

	const int buffer_size = length * sizeof(int);

	int i, k, count, index;
	int bucket[10] = {0, };	// �������ָ��� 0 ~ 9 ���� 10 ��Ͱ

	int* temp = (int*)malloc(buffer_size);
	if (!temp) {
		printf("Error: out of memory!\n");
		return;
	}

	count = get_max_digital_count(array, length);

	for (k = 1; k <= count; ++k) {
		memset(bucket, 0, 10 * sizeof(int));

		// ͳ�Ƹ�Ͱ��Ԫ�صĸ���
		for (i = 0; i < length; ++i) {
			index = get_ditital_at(array[i], k);
			++bucket[index];
		}

		// Ϊÿ����¼���������±�
		for (i = 1; i < 10; ++i) {
			bucket[i] += bucket[i - 1];
		}

		// �������±�˳������
		for (i = length - 1; i >= 0; --i) {
			index = get_ditital_at(array[i], k);
			assert(bucket[index] - 1 >= 0);
			temp[--bucket[index]] = array[i];
		}

		// һ��Ͱ������ϣ��������
		memcpy(array, temp, buffer_size);

#ifdef DEBUG_SORT
		debug_print(" �� %d ������", k);
		for (i = 0; i < length; ++i) {
			debug_print("%d ", array[i]);
		}

		debug_print("\n");
#endif
	}

	free(temp);
}
