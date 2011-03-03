#ifndef __SORT_ALGORITHMS_H__
#define __SORT_ALGORITHMS_H__

// ֱ�Ӳ�������
void insert_sort(int* array, int length);

// ϣ������
void shell_sort(int* array, int length);

// ð������
void bubble_sort(int* array, int length);

// ð������Ľ���
void bubble_sort_opt(int* array, int length);

// ��������
void quick_sort(int* array, int length);

// ֱ��ѡ������
void select_sort(int* array, int length);

// ������
void heap_sort(int* array, int length);

// �÷��η��������Ͻ��ж�·�鲢����
void merge_sort(int* array, int length);

// �÷��η��������½��ж�·�鲢����
void merge_sort_dc(int* array, int length);

// ��/Ͱ�����Կռ任ʱ��
// ������ֻ����������
void bucket_sort(int* array, int length);

// ���������Կռ任ʱ��
// ������ֻ����������
void radix_sort(int* array, int length);

#endif // __SORT_ALGORITHMS_H__