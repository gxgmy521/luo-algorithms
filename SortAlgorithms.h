#include <stdlib.h>
#include <assert.h>

/**
 * 算法名称	  ：直接插入排序
 * 算法描述	  ：依次从无序区中选择元素插入到有序区中的合适位置使之依然有序。
 * 时间复杂度 ：O(n^2)
 * 空间复杂度 ：O(1)
 * 稳定排序	  ：是
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
 * 算法名称	  ：希尔排序（插入排序的一种）
 * 算法描述	  ：先将整个待排元素序列分割成若干个子序列（由相隔某个“增量”
 *				的元素组成的）分别进行直接插入排序，然后逐渐缩减增量
 *				（最终缩小至 1）再对各组分别进行直接插入排序。
 * 时间复杂度 ：O(n^2)，元素较多时比直接插入排序快。
 * 空间复杂度 ：O(1)
 * 稳定排序	  ：否
 */
void shell_sort(int* array, int length)
{
	assert(array && length >= 0);

	int i, j , temp;
	int increment = length;

	do {
		increment = increment / 3 + 1;

		// 希尔排序中的一趟排序，increment 为当前增量
		// 将 [increment, length - 1] 之间的元素分别插入各组当前的有序区
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
 * 算法名称	  ：冒泡排序（交换排序的一种）
 * 算法描述	  ：将 length 个记录看作按纵向排列，每趟排序时自下至上对每对相邻
 *              记录进行比较，若次序不符合要求（逆序）就交换。每趟排序结束时
 *              都能使排序范围内关键字最小的记录象一个气泡一样升到表上端的
 *              对应位置，整个排序过程共进行 length - 1 趟，依次将关键字最小、
 *			    次小 … 的各个记录“冒到”表的第一个、第二个 … 位置上。
 * 时间复杂度 ：O(n^2)
 * 空间复杂度 ：O(0)
 * 稳定排序	  ：是
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
 * 算法名称	  ：冒泡排序改进版（交换排序的一种）
 * 算法描述   ：在每趟冒泡扫描中，记住最后一次交换发生的位置 lastExchange，
 *			    （该位置之前的相邻记录均已有序）。下一趟排序开始时，
 *              [0, lastExchange]是有序区，[lastExchange + 1, length - 1]
 *              是无序区。这样，一趟排序可能使当前有序区扩充多个记录，
 *              从而减少排序的趟数。
 * 时间复杂度 ：O(n^2)
 * 空间复杂度 ：O(0)
 * 稳定排序	  ：是
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
 * 算法描述	 ：在每趟冒泡扫描中，记住最后一次交换发生的位置 lastExchange，
 *			   （该位置之前的相邻记录均已有序）。下一趟排序开始时，
 *             [0, lastExchange]是有序区，[lastExchange + 1, length - 1]
 *             是无序区。这样，一趟排序可能使当前有序区扩充多个记录，
 *             从而减少排序的趟数。
 * 时间复杂度 ：平均：O(nlgn)，最坏：O(n^2)
 * 空间复杂度 ：O(lgn)
 * 稳定排序	  ：否
 */

// 对[low, high]做划分，并返回基准记录的位置
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

	if (length == 0) {
		return;
	}

	quick_sort_impl( array, 0, length - 1);
}

/**
 * 算法名称	  ：直接选择排序（选择排序的一种）
 * 算法描述	  ：第 i 趟排序开始时，当前有序区和无序区分别为[0, i - 1]和
 *              [i, length - 1]。该趟排序从当前无序区中选出关键字最小的记录 [k]，
 *              将它与无序区的第一个记录[i]交换，使[0, i]和[i + 1, length - 1]分别
 *              变为记录个数增加一个的新有序区和记录个数减少一个的新无序区。
 * 时间复杂度 ：O(n^2)
 * 空间复杂度 ：O(0)
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
 * 算法名称	  ：堆排序（树形选择排序的一种）
 * 算法描述	  ：在排序过程中，将 [0, length - 1] 看成是一棵完全二叉树的
 *              顺序存储结构，利用完全二叉树中双亲结点和孩子结点之间的内
 *              在关系，在当前无序区中选择关键字最大（或最小）的记录。
 * 时间复杂度 ：O(nlgn)
 * 空间复杂度 ：O(1)
 * 稳定排序	  ：否
 */

// 筛选法调整堆，除 [low] 之外，[low] 的两个孩子均已是大根堆
void adjust_heap(int* heap, int low, int high)
{
	assert(heap);

#if 1	// 递归实现
	int i = low;
	int j = 2 * i;
	int temp;

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
	
	temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;

	// 调整之后，[j, high] 可能不满足堆了，需继续调整
	adjust_heap(heap, j, high);

#else	// 循环实现

	int i = low;
	int j = 2 * i;
	int temp;

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
#endif
}

// 只有一个结点的树是堆，而在完全二叉树中，所有序号 i > n/2 的结点都是叶子，
// 因此以这些结点为根的子树均已是堆。这样，我们只需依次将以序号为
// n/2, n/2 - 1，…，0 的结点作为根的子树都调整为堆即可。
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

void merge_sort(int* array, int length)
{
	assert(array && length >= 0);
}
