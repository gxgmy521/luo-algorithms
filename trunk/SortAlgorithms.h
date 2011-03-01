#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

/**
 * �㷨����	 ��ֱ�Ӳ�������
 * �㷨����	 �����δ���������ѡ���¼���뵽�������еĺ���λ��ʹ֮��Ȼ����
 * ʱ�临�Ӷ� ��O(n^2)
 * �ռ临�Ӷ� ��O(1)
 * �ȶ�����	 ����
 */
void insert_sort(int* array, int length)
{
	assert(array && length >= 0);

	int i, j, temp;
	for (i = 1; i < length; ++i) {
		temp = array[i];
		j = i - 1;

		while (temp < array[j]) {
			array[j + 1] = array[j];
			--j;
		}

		array[j + 1] = temp;
	}
}

/**
 * �㷨����	 ��ϣ�����򣨲��������һ�֣�
 * �㷨����	 ���Ƚ��������ż�¼���зָ�����ɸ������У������ĳ����������
 *			   �ļ�¼��ɵģ��ֱ����ֱ�Ӳ�������Ȼ������������
 *			   ��������С�� 1���ٶԸ���ֱ����ֱ�Ӳ�������
 * ʱ�临�Ӷ� ��O(n^2)����¼�϶�ʱ��ֱ�Ӳ�������졣
 * �ռ临�Ӷ� ��O(1)
 * �ȶ�����	 ����
 */
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

/**
 * �㷨����	 ��ð�����򣨽��������һ�֣�
 * �㷨����	 ���� length ����¼�������������У�ÿ������ʱ�������϶�ÿ������
 *             ��¼���бȽϣ������򲻷���Ҫ�����򣩾ͽ�����ÿ���������ʱ
 *             ����ʹ����Χ�ڹؼ�����С�ļ�¼��һ������һ���������϶˵�
 *             ��Ӧλ�ã�����������̹����� length - 1 �ˣ����ν��ؼ�����С��
 *			   ��С �� �ĸ�����¼��ð�������ĵ�һ�����ڶ��� �� λ���ϡ�
 * ʱ�临�Ӷ� ��O(n^2)
 * �ռ临�Ӷ� ��O(0)
 * �ȶ�����	 ����
 */
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

/**
 * �㷨����	 ��ð������Ľ��棨���������һ�֣�
 * �㷨����   ����ÿ��ð��ɨ���У���ס���һ�ν���������λ�� lastExchange��
 *			   ����λ��֮ǰ�����ڼ�¼�������򣩡���һ������ʼʱ��
 *             [0, lastExchange] ����������[lastExchange + 1, length - 1] ��
 *             ��������������һ���������ʹ��ǰ��������������¼���Ӷ����������������
 * ʱ�临�Ӷ� ��O(n^2)
 * �ռ临�Ӷ� ��O(0)
 * �ȶ�����	 ����
 */
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

/**
 * �㷨����	 ���������򣨽��������һ�֣�
 * �㷨����	 ������������һ�ַ��η����� [low, high] ����ѡһ����¼��Ϊ��׼��¼(Pivot)��
 *             �Դ˻�׼����ǰ����������Ϊ����������С�������� [low, pivotpos - 1)
 *             �� [pivotpos + 1, high]����ʹ��������������м�¼��С�ڵ��ڻ�׼��¼��
 *             �ұߵ������������м�¼�����ڵ��ڻ�׼��¼��
 *             ͨ���ݹ���ÿ��������������������л��֣�ֱ��ÿ��������ֻ��һ����¼��
 * ʱ�临�Ӷ� ��ƽ����O(nlgn)�����O(n^2)
 * �ռ临�Ӷ� ��O(lgn)
 * �ȶ�����	 ����
 */

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

void quick_sort(int* array, int length)
{
	assert(array && length >= 0);

	if (length <= 1) {
		return;
	}

	quick_sort_impl( array, 0, length - 1);
}

/**
 * �㷨����	  ��ֱ��ѡ������ѡ�������һ�֣�
 * �㷨����	  ���� i ������ʼʱ����ǰ���������������ֱ�Ϊ [0, i - 1] ��
 *              [i, length - 1]����������ӵ�ǰ��������ѡ���ؼ�����С�ļ�¼ [k]��
 *              �������������ĵ�һ����¼ [i] ������ʹ [0, i] �� [i + 1, length - 1]
 *              �ֱ��Ϊ��¼��������һ�������������ͼ�¼��������һ��������������
 * ʱ�临�Ӷ�  ��O(n^2)
 * �ռ临�Ӷ�  ��O(0)
 * �ȶ�����	  ����
 */
void select_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, j, k, temp;

	for (i = 0; i < length; ++i) {
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

/**
 * �㷨����	 ������������ѡ�������һ�֣�
 * �㷨����	 ������������У��� [0, length - 1] ������һ����ȫ��������
 *             ˳��洢�ṹ��������ȫ��������˫�׽��ͺ��ӽ��֮�����
 *             �ڹ�ϵ��˫�׽�����Ǻ��ӽ����С�����ڵ�ǰ��������ѡ��
 *             ��󣨻���С���ļ�¼��
 * ʱ�临�Ӷ� ��O(nlgn)
 * �ռ临�Ӷ� ��O(1)
 * �ȶ�����	 ����
 */

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

/**
 * �㷨����	 ���鲢����
 * �㷨����	 �����������¼����ֽ�Ϊ������¼���� [0, m]��[m + 1, length - 1]��
 *             ����֮�ϲ���һ����ʱ���� temp �����ϲ���ɺ� temp ���ƻ������С�
 * ʱ�临�Ӷ� ��O(lgn)
 * �ռ临�Ӷ� ��O(n)
 * �ȶ�����	 ����
 */

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
//	for (i = 0; i < high - low + 1; i++){
//		array[low + i] = temp[i];
//	}

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
void merge_sort(int* array, int length)
{
	assert(array && length >= 0);

	if (length <= 1) {
		return;
	}

	int n;

	for(n = 1; n < length; n = (n << 1)) {
		merge_pass(array, length, n);
	}
}

///////////////////////////////////////////////////////////////////////
// �÷��η��������½��ж�·�鲢����
//////////////////////////////////////////////////////////////////////
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

// �÷��η��������½��ж�·�鲢����
void merge_sort_dc(int* array, int length)
{
	assert(array && length >= 0);

	if (length <= 1) {
		return;
	}

	merge_sort_dc_impl(array, 0, length - 1);
}

/**
 * �㷨����	 ����/Ͱ����
 * �㷨����	 ��
 * ʱ�临�Ӷ� ��O(n)
 * �ռ临�Ӷ� ��O(n + rd)
 * �ȶ�����	 ����
 */
void bucket_sort(int* array, int length)
{
	assert(array && length >= 0);

}


/**
 * �㷨����	 ����������
 * �㷨����	 ��
 * ʱ�临�Ӷ� ��O(n)
 * �ռ临�Ӷ� ��O(n + rd)
 * �ȶ�����	 ����
 */
void radix_sort(int* array, int length)
{
	assert(array && length >= 0);

}
