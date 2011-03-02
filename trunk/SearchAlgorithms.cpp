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

int sequential_search(int* array, int length, int key)
{
	assert(array && length >= 0);

	int i;

	for (i = 0; i < length; ++i) {
		if (array[i] == value) {
			return i;
		}
	}

	return -1;
}

// 在有序表 [0, length - 1]中进行二分查找。
// 成功时返回结点的位置，失败时返回 -1
int binary_search(int* array, int length, int key)
{

{ //在有序表R[1..n]中进行二分查找，成功时返回结点的位置，失败时返回零
	int low=1，high=n，mid； //置当前查找区间上、下界的初值
		while(low<=high){ //当前查找区间R[low..high]非空
			mid=(low+high)/2；
				if(R[mid].key==K) return mid； //查找成功返回
					if(R[mid].kdy>K)
						high=mid-1; //继续在R[low..mid-1]中查找
					else
						low=mid+1； //继续在R[mid+1..high]中查找
		}
		return 0； //当low>high时表示查找区间为空，查找失败
} //BinSeareh