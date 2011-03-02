#ifndef __SEARCH_ALGORITHMS_H__
#define __SEARCH_ALGORITHMS_H__

// 线性查找:成功时返回结点的位置，失败时返回 -1
int sequential_search(int* array, int length, int key);

// 二分查找:成功时返回结点的位置，失败时返回 -1
int binary_search(int* array, int length, int key);
#endif // __SEARCH_ALGORITHMS_H__