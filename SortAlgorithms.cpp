#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

#include "SortAlgorithms.h"

#define DEBUG_SORT

#ifdef DEBUG_SORT
#define debug_print(fmt,...) printf(fmt, __VA_ARGS__)
#else
#define debug_print(fmt,...)
#endif

/**
* 算法名称	 ：直接插入排序
* 算法描述	 ：依次从无序区中选择记录插入到有序区中的合适位置使之依然有序。
* 时间复杂度 ：O(n^2)
* 空间复杂度 ：O(1)
* 稳定排序	 ：是
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
* 算法名称	 ：希尔排序（插入排序的一种）
* 算法描述	 ：先将整个待排记录序列分割成若干个子序列（由相隔某个“增量”
*			   的记录组成的）分别进行直接插入排序，然后逐渐缩减增量
*			   （最终缩小至 1）再对各组分别进行直接插入排序。
* 时间复杂度 ：O(n^2)，记录较多时比直接插入排序快。
* 空间复杂度 ：O(1)
* 稳定排序	 ：否
*/
void shell_sort(int* array, int length)
{
	assert(array && length >= 0);

	int i, j , temp;
	int increment = length;

	do {
		increment = increment / 3 + 1;

		// 希尔排序中的一趟排序，increment 为当前增量
		// 将 [increment, length - 1] 之间的记录分别插入各组当前的有序区
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
* 算法名称	 ：冒泡排序（交换排序的一种）
* 算法描述	 ：将 length 个记录看作按纵向排列，每趟排序时自下至上对每对相邻
*             记录进行比较，若次序不符合要求（逆序）就交换。每趟排序结束时
*             都能使排序范围内关键字最小的记录象一个气泡一样升到表上端的
*             对应位置，整个排序过程共进行 length - 1 趟，依次将关键字最小、
*			   次小 … 的各个记录“冒到”表的第一个、第二个 … 位置上。
* 时间复杂度 ：O(n^2)
* 空间复杂度 ：O(0)
* 稳定排序	 ：是
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
* 算法名称	 ：冒泡排序改进版（交换排序的一种）
* 算法描述   ：在每趟冒泡扫描中，记住最后一次交换发生的位置 lastExchange，
*			   （该位置之前的相邻记录均已有序）。下一趟排序开始时，
*             [0, lastExchange] 是有序区，[lastExchange + 1, length - 1] 是
*             无序区。这样，一趟排序可能使当前有序区扩充多个记录，从而减少排序的趟数。
* 时间复杂度 ：O(n^2)
* 空间复杂度 ：O(0)
* 稳定排序	 ：是
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
* 算法名称	 ：快速排序（交换排序的一种）
* 算法描述	 ：快速排序是一种分治法，在 [low, high] 中任选一个记录作为基准记录(Pivot)，
*             以此基准将当前无序区划分为左、右两个较小的子区间 [low, pivotpos - 1)
*             和 [pivotpos + 1, high]，并使左边子区间中所有记录均小于等于基准记录，
*             右边的子区间中所有记录均大于等于基准记录。
*             通过递归调用快速排序对左、右子区间进行划分，直至每个子区间只有一个记录。
* 时间复杂度 ：平均：O(nlgn)，最坏：O(n^2)
* 空间复杂度 ：O(lgn)
* 稳定排序	 ：否
*/

// 对 [low, high] 做划分，并返回基准记录的位置
int quick_partition(int* array, int low, int high)
{
	assert(array && low >= 0 && low <= high);

	int pivot = array[low]; // 用区间的第 1 个记录作为基准

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
* 算法名称	  ：直接选择排序（选择排序的一种）
* 算法描述	  ：第 i 趟排序开始时，当前有序区和无序区分别为 [0, i - 1] 和
*              [i, length - 1]。该趟排序从当前无序区中选出关键字最小的记录 [k]，
*              将它与无序区的第一个记录 [i] 交换，使 [0, i] 和 [i + 1, length - 1]
*              分别变为记录个数增加一个的新有序区和记录个数减少一个的新无序区。
* 时间复杂度  ：O(n^2)
* 空间复杂度  ：O(0)
* 稳定排序	  ：否
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
* 算法名称	 ：堆排序（树形选择排序的一种）
* 算法描述	 ：在排序过程中，将 [0, length - 1] 看成是一棵完全二叉树的
*             顺序存储结构，利用完全二叉树中双亲结点和孩子结点之间的内
*             在关系（双亲结点总是孩子结点大或小），在当前无序区中选择
*             最大（或最小）的记录。
* 时间复杂度 ：O(nlgn)
* 空间复杂度 ：O(1)
* 稳定排序	 ：否
*/

// 筛选法调整堆，除 [low] 之外，[low] 的两个孩子均已是大根堆
void adjust_heap(int* heap, int low, int high)
{
	assert(heap);

#if 1	// 循环实现

	int i = low;
	int j = 2 * i;
	int temp = heap[i];

	while (j <= high) {
		// 若有两个孩子，j 为孩子中大的那个的下标
		if (j < high && heap[j] < heap[j + 1]) {
			j = j + 1;
		}

		// 已是堆
		if (temp >= heap[j]) {
			break;
		}

		// 继续筛选
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * i;
		}
	}

	heap[i] = temp;

#else	// 递归实现

	int i = low;
	int j = 2 * i;
	int temp = heap[i];

	if (j >= high) {
		return;
	}

	// 若有两个孩子，j 为孩子中大的那个的下标
	if (j < high && heap[j + 1] > heap[j]) {
		j = j + 1;
	}

	// 已经为堆，无需调整
	if (heap[low] >= heap[j]) {
		return;
	}

	heap[i] = heap[j];
	heap[j] = temp;

	// 调整之后，[j, high] 可能不满足堆了，需继续调整
	adjust_heap(heap, j, high);

#endif
}

// 只有一个结点的树是堆，而在完全二叉树中，所有序号 i > n/2 的结点都是叶子，
// 因此以这些结点为根的子树均已是堆。这样，我们只需依次将以序号为
// n/2, n/2 - 1, …, 0 的结点作为根的子树都调整为堆即可。
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

	// 将 [0, length - 1] 建成初始堆
	build_heap(array, length);

	// 对当前无序区 [0, i - 1] 进行堆排序，共做 length - 1 趟。
	for(i = length - 1; i > 0; --i) {
		// 将堆顶和堆中最后一个记录交换
		temp = array[0];
		array[0] = array[i];
		array[i]= temp;

		// 将 [0, i - 1] 重新调整为堆，仅有 [0] 可能违反堆性质
		adjust_heap(array, 0, i - 1);
	}
}

/**
* 算法名称	 ：归并排序
* 算法描述	 ：将待排序记录数组分解为两个记录数组 [0, m]，[m + 1, length - 1]，
*             并将之合并到一个临时数组 temp ，待合并完成后将 temp 复制回数组中。
* 时间复杂度 ：O(lgn)
* 空间复杂度 ：O(n)
* 稳定排序	 ：是
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

// 对 [0, length - 1] 做一趟归并长度为 n  的归并排序
void merge_pass(int* array, int length, int n)
{ 
	assert(array && length >= 1 && n >= 1);

	int i;
	int sortLength = 2 * n;

	// 归并长度为 n 的两个相邻子序列
	for(i = 0; i + sortLength - 1 < length; i = i + sortLength) {
		merge(array, i, i + n - 1, i + sortLength - 1);
	}

	// 若 i + n - 1 < length - 1，则剩余一个子文件轮空，无须归并。
	// 尚有两个子序列，其中后一个长度小于 n, 归并最后两个子序列。
	if (length - 1 > i + n - 1) {
		merge(array, i, i + n - 1, length - 1);
	}
}

// 用分治法自下向上进行二路归并排序
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
// 用分治法自上向下进行二路归并排序
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

// 用分治法自上向下进行二路归并排序
void merge_sort_dc(int* array, int length)
{
	assert(array && length >= 0);

	if (length <= 1) {
		return;
	}

	merge_sort_dc_impl(array, 0, length - 1);
}

/**
* 算法名称	 ：箱/桶排序
* 算法描述	 ：将长度为 N 待排序序列划分成 M 个的子区间（桶）；然后基于
*              某种映射函数，将待排序列的关键字 k 映射到第 i 个桶中（即桶数组
*              B 的下标 i ），那么该关键字 k 就作为 B[i] 中的元素（每个桶 B[i]
*              都是一组大小为N/M的序列）；接着对每个桶 B[i] 中的所有元素进行
*              比较排序（可以使用快速排序）；然后依次枚举输出 B[0]....B[M] 中的
*              全部内容即是一个有序序列。
* 时间复杂度 ：O(n)
* 空间复杂度 ：O(n)
* 稳定排序	 ：是
*/
struct bucket_node {
	int key;
	bucket_node* next;
};

// 取得数组中最大数的位数
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

// 取得数 num 中从低到高第 n 位上的数字
int get_ditital_at(int num, int n)
{
	while (--n > 0) {
		num /= 10;
	}

	return (num % 10);
}

void bucket_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, index;
	bucket_node* temp = NULL;
	bucket_node bucket[10] = {0, };	// 根据数字个数 0 ~ 9 建立 10 个桶

	int count = get_max_digital_count(array, length);

	// 建立数据节点
	bucket_node* data = (bucket_node*)malloc(length * sizeof(bucket_node));
	if (!data) {
		printf("Error: out of memory!\n");
		return;
	}

	for (i = 0; i < length; i++) {
		data[i].key = array[i];
		data[i].next = NULL;
	}

	// 分配
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

	// 收集
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

/**
* 算法名称	 ：基数排序
* 算法描述	 ：
* 时间复杂度 ：O(n)
* 空间复杂度 ：O(n + rd)
* 稳定排序	 ：是
*
*/
void radix_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, k, index;
	const int buffer_size = length * sizeof(int);
	int count = get_max_digital_count(array, length);

	int bucket[10] = {0, };
	int* temp = (int*)malloc(buffer_size);
	if (!temp) {
		printf("Error: out of memory!\n");
		return;
	}

	for (k = 1; k <= count; ++k) {
		memset(bucket, 0, 10 * sizeof(int));

		// 统计各桶中元素的个数
		for (i = 0; i < length; ++i) {
			index = get_ditital_at(array[i], k);
			++bucket[index];
		}

		// 为每个记录创建索引下标
		for (i = 1; i < 10; ++i) {
			bucket[i] += bucket[i - 1];
		}

		// 按索引下标顺序排列
		for (i = length - 1; i >= 0; --i) {
			index = get_ditital_at(array[i], k);
			assert(bucket[index] - 1 >= 0);
			temp[--bucket[index]] = array[i];
		}
		
		// 一趟桶排序完毕，拷贝结果
		memcpy(array, temp, buffer_size);

#ifdef DEBUG_SORT
		debug_print(" 第 %d 趟排序：", k);
		for (i = 0; i < length; ++i) {
			debug_print("%d ", array[i]);
		}

		debug_print("\n");
#endif
	}

	free(temp);
}
