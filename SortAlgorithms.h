#include <stdlib.h>
#include <assert.h>

/**
 * 算法名称	  ：直接插入排序
 * 算法描述	  ：[0, i - 1]为有序序列，将第 i 个元素插入到合适的位置 j + 1，
 *				并将 [i - 1, j + 1] 之间的元素依次后移一个位置。
 * 时间复杂度 ：O(n^2)
 * 空间复杂度 ：O(1)
 * 稳定排序	  ：是
 */
void insert_sort(int* array, int length)
{
	assert(array && length >= 0);

	int i, j, temp;
	for (i = 1; i < length; i++)
	{
		temp = array[i];
		j = i - 1;

		while (temp < array[j]) 
		{
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

	do 
	{
		increment = increment / 3 + 1;

		// 希尔排序中的一趟排序，increment 为当前增量
		// 将 [increment, length - 1] 之间的元素分别插入各组当前的有序区
		for (i = increment; i < length; i++)
		{
			temp = array[i];
			j = i - increment;

			while (j >= 0 && temp < array[j]) 
			{
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
 * 空间复杂度 ：O(1)
 * 稳定排序	  ：是
 */
void bubble_sort(int* array, int length)
{
	assert(array && length >= 0);
	
	int i, j, temp;
	bool exchange;
	for (i = 1; i < length; i++)
	{
		exchange = false;

		for (j = length - 1; j >= i; j--)
		{
			if (array[j] < array[j - 1])
			{
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
 * 空间复杂度 ：O(1)
 * 稳定排序	  ：是
 */
void bubble_sort_opt(int* array, int length)
{
	assert(array && length >= 0);

	int i, j, temp;
	bool exchange;
	int lastExchange = 1;
	for (i = 1; i < length;)
	{
		exchange = false;

		for (j = length - 1; j >= i; j--)
		{
			if (array[j] < array[j - 1])
			{
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
*              [0, lastExchange]是有序区，[lastExchange + 1, length - 1]
*              是无序区。这样，一趟排序可能使当前有序区扩充多个记录，
*              从而减少排序的趟数。
* 时间复杂度 ：平均：O(nlgn)，最坏：O(n^2)
* 空间复杂度 ：O(lgn)
* 稳定排序	 ：否
*/

int quick_partition(int* array, int low, int high)
{
	// 对[low, high]做划分，并返回基准记录的位置

	assert(array && low >= 0 && low <= high);

	int pivot = array[low]; // 用区间的第 1 个记录作为基准
	while (low < high)
	{
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
	if (low < high)
	{
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