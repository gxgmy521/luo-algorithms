#include <stdlib.h>
#include <assert.h>

/**
 * �㷨����	  ��ֱ�Ӳ�������
 * �㷨����	  ��[0, i - 1]Ϊ�������У����� i ��Ԫ�ز��뵽���ʵ�λ�� j + 1��
 *				���� [i - 1, j + 1] ֮���Ԫ�����κ���һ��λ�á�
 * ʱ�临�Ӷ� ��O(n^2)
 * �ռ临�Ӷ� ��O(1)
 * �ȶ�����	  ����
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
 * �㷨����	  ��ϣ�����򣨲��������һ�֣�
 * �㷨����	  ���Ƚ���������Ԫ�����зָ�����ɸ������У������ĳ����������
 *				��Ԫ����ɵģ��ֱ����ֱ�Ӳ�������Ȼ������������
 *				��������С�� 1���ٶԸ���ֱ����ֱ�Ӳ�������
 * ʱ�临�Ӷ� ��O(n^2)��Ԫ�ؽ϶�ʱ��ֱ�Ӳ�������졣
 * �ռ临�Ӷ� ��O(1)
 * �ȶ�����	  ����
 */
void shell_sort(int* array, int length)
{
	assert(array && length >= 0);

	int i, j , temp;
	int increment = length;

	do 
	{
		increment = increment / 3 + 1;

		// ϣ�������е�һ������increment Ϊ��ǰ����
		// �� [increment, length - 1] ֮���Ԫ�طֱ������鵱ǰ��������
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
 * �㷨����	  ��ð�����򣨽��������һ�֣�
 * �㷨����	  ���� length ����¼�������������У�ÿ������ʱ�������϶�ÿ������
 *              ��¼���бȽϣ������򲻷���Ҫ�����򣩾ͽ�����ÿ���������ʱ
 *              ����ʹ����Χ�ڹؼ�����С�ļ�¼��һ������һ���������϶˵�
 *              ��Ӧλ�ã�����������̹����� length - 1 �ˣ����ν��ؼ�����С��
 *			    ��С �� �ĸ�����¼��ð������ĵ�һ�����ڶ��� �� λ���ϡ�
 * ʱ�临�Ӷ� ��O(n^2)
 * �ռ临�Ӷ� ��O(1)
 * �ȶ�����	  ����
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
 * �㷨����	  ��ð������Ľ��棨���������һ�֣�
 * �㷨����   ����ÿ��ð��ɨ���У���ס���һ�ν���������λ�� lastExchange��
 *			    ����λ��֮ǰ�����ڼ�¼�������򣩡���һ������ʼʱ��
 *              [0, lastExchange]����������[lastExchange + 1, length - 1]
 *              ����������������һ���������ʹ��ǰ��������������¼��
 *              �Ӷ����������������
 * ʱ�临�Ӷ� ��O(n^2)
 * �ռ临�Ӷ� ��O(1)
 * �ȶ�����	  ����
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
* �㷨����	 ���������򣨽��������һ�֣�
* �㷨����	 ����ÿ��ð��ɨ���У���ס���һ�ν���������λ�� lastExchange��
*			   ����λ��֮ǰ�����ڼ�¼�������򣩡���һ������ʼʱ��
*              [0, lastExchange]����������[lastExchange + 1, length - 1]
*              ����������������һ���������ʹ��ǰ��������������¼��
*              �Ӷ����������������
* ʱ�临�Ӷ� ��ƽ����O(nlgn)�����O(n^2)
* �ռ临�Ӷ� ��O(lgn)
* �ȶ�����	 ����
*/

int quick_partition(int* array, int low, int high)
{
	// ��[low, high]�����֣������ػ�׼��¼��λ��

	assert(array && low >= 0 && low <= high);

	int pivot = array[low]; // ������ĵ� 1 ����¼��Ϊ��׼
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