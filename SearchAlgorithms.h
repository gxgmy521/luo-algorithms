#ifndef __SEARCH_ALGORITHMS_H__
#define __SEARCH_ALGORITHMS_H__

/**
* 算法名称	 ：顺序查找
* 算法描述	 ：从表的一端开始，顺序扫描线性表，依次将扫描到的结点关键字和
*              给定值 key 相比较。若当前扫描到的结点关键字与 key 相等，则
*              查找成功；若扫描结束后，仍未找到关键字等于 key 的结点，则
*              查找失败。
* 时间复杂度 ：O(n)，平均时间复杂度为 n/2
* 空间复杂度 ：O(0)
* 前置条件	 ：无
* 返回值	 : 成功时返回结点的位置，失败时返回 -1
*/
int sequential_search(const int* array, int length, int key);


/**
* 算法名称	 ：二分查找
* 算法描述	 ：从表的一端开始，顺序扫描线性表，依次将扫描到的结点关键字和
*              给定值 key 相比较。若当前扫描到的结点关键字与 key 相等，则
*              查找成功；若扫描结束后，仍未找到关键字等于 key 的结点，则
*              查找失败。
* 时间复杂度 ：O(lgn)
* 空间复杂度 ：O(1)
* 前置条件	 ：待排序序列必须有序
* 返回值	 : 成功时返回结点的位置，失败时返回 -1
*/
int binary_search(const int* array, int length, int key);


/**
* 算法名称	 ：分块查找/索引顺序查找
* 算法描述	 ：二分查找表由“分块有序”的线性表和有序的索引表组成。
*              分块查找的基本思想是：
			   （1）首先查找索引表，以确定待查的结点在哪一块。
			        索引表是有序表，可采用二分查找或顺序查找。
			   （2）然后在已确定的块中进行顺序查找。
			        由于块内无序，只能用顺序查找。
* 时间复杂度 ：O(lgn)
* 空间复杂度 ：需要存储索引表，一般为根号n
* 前置条件	 ：序列必须分块有序，且需要创建有序的索引表
* 返回值	 : 成功时返回结点的位置，失败时返回 -1
*/
struct IndexNode {
	int index;
	int key;
	IndexNode* next;
};

int blocking_search(
	const int* array,
	int length,
	IndexNode* indexTable,
	int indexTableLength,
	int key);


#endif // __SEARCH_ALGORITHMS_H__