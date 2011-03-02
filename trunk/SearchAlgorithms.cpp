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

// ������� [0, length - 1]�н��ж��ֲ��ҡ�
// �ɹ�ʱ���ؽ���λ�ã�ʧ��ʱ���� -1
int binary_search(int* array, int length, int key)
{

{ //�������R[1..n]�н��ж��ֲ��ң��ɹ�ʱ���ؽ���λ�ã�ʧ��ʱ������
	int low=1��high=n��mid�� //�õ�ǰ���������ϡ��½�ĳ�ֵ
		while(low<=high){ //��ǰ��������R[low..high]�ǿ�
			mid=(low+high)/2��
				if(R[mid].key==K) return mid�� //���ҳɹ�����
					if(R[mid].kdy>K)
						high=mid-1; //������R[low..mid-1]�в���
					else
						low=mid+1�� //������R[mid+1..high]�в���
		}
		return 0�� //��low>highʱ��ʾ��������Ϊ�գ�����ʧ��
} //BinSeareh