#ifndef __SEARCH_ALGORITHMS_H__
#define __SEARCH_ALGORITHMS_H__

/**
* �㷨����	 ��˳�����
* �㷨����	 ���ӱ��һ�˿�ʼ��˳��ɨ�����Ա����ν�ɨ�赽�Ľ��ؼ��ֺ�
*              ����ֵ key ��Ƚϡ�����ǰɨ�赽�Ľ��ؼ����� key ��ȣ���
*              ���ҳɹ�����ɨ���������δ�ҵ��ؼ��ֵ��� key �Ľ�㣬��
*              ����ʧ�ܡ�
* ʱ�临�Ӷ� ��O(n)��ƽ��ʱ�临�Ӷ�Ϊ n/2
* �ռ临�Ӷ� ��O(0)
* ǰ������	 ����
* ����ֵ	 : �ɹ�ʱ���ؽ���λ�ã�ʧ��ʱ���� -1
*/
int sequential_search(const int* array, int length, int key);


/**
 * �㷨����	 �����ֲ���
 * �㷨����	 ���ӱ��һ�˿�ʼ��˳��ɨ�����Ա����ν�ɨ�赽�Ľ��ؼ��ֺ�
 *             ����ֵ key ��Ƚϡ�����ǰɨ�赽�Ľ��ؼ����� key ��ȣ���
 *             ���ҳɹ�����ɨ���������δ�ҵ��ؼ��ֵ��� key �Ľ�㣬��
 *             ����ʧ�ܡ�
 * ʱ�临�Ӷ� ��O(lgn)
 * �ռ临�Ӷ� ��O(1)
 * ǰ������	 �����������б�������
 * ����ֵ	 : �ɹ�ʱ���ؽ���λ�ã�ʧ��ʱ���� -1
 */
int binary_search(const int* array, int length, int key);


/**
 * �㷨����	 ���ֿ����/����˳�����
 * �㷨����	 �����ֲ��ұ��ɡ��ֿ����򡱵����Ա���������������ɡ�
 *             �ֿ���ҵĻ���˼���ǣ�
 *			  ��1�����Ȳ�����������ȷ������Ľ������һ�顣
 *			       ��������������ɲ��ö��ֲ��һ�˳����ҡ�
 *			  ��2��Ȼ������ȷ���Ŀ��н���˳����ҡ�
 *			       ���ڿ�������ֻ����˳����ҡ�
 * ʱ�临�Ӷ� ��O(lgn)
 * �ռ临�Ӷ� ����Ҫ�洢������һ��Ϊ����n
 * ǰ������	 �����б���ֿ���������Ҫ���������������
 * ����ֵ	 : �ɹ�ʱ���ؽ���λ�ã�ʧ��ʱ���� -1
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


/**
 * �㷨����	 ��ɢ�в���
 * �㷨����	 ��������ɢ�к������ؼ���ӳ�䵽ɢ�б��е�ÿ��λ�ã�ֱ����ɢ�б���ȡֵ
 * ʱ�临�Ӷ� ��O(1)���Կռ任ʱ��
 * �ռ临�Ӷ� ��O(m)��m Ϊɢ�б���
 * ǰ������	 ����
 * ����ֵ	 : �ɹ�ʱ���ؽ���λ�ã�ʧ��ʱ���� -1
 */

// ��ͻ����ʱ����������̽��ķ�ʽ
enum Conflict_Resolution
{
	Conflict_Resolution_Linear		= 0,	// ����̽��
	Conflict_Resolution_Quadratic	= 1,	// ����̽��
	Conflict_Resolution_Double_Hash	= 2,	// ˫��ɢ��̽��
};

// hash ����
typedef int (*Hash_Function)(int key, int hashTableLength);

// ɢ�к�����ȡ�෨
// h(key) = key % hashTableLength
//
int hash_remiander(int key, int hashTableLength);

// ɢ�к��������ȡ����
// h(key) = [hashTableLength * (key * A - [key * A])]
// A Լ���� (���� 5 - 1)/2 = 0.61803398
//
int hash_multi_round_off(int key, int hashTableLength);

//=========================================================
//					���ŵ�ַ����ϣ����
//=========================================================
// �������ÿ��ŵ�ַ����ɢ�б�
void create_open_address_hash_table(
	int* table,
	int tableLength,
	const int* data,
	int dataLength,
	Hash_Function hashFunc = hash_remiander,			// ���� hash ����
	Conflict_Resolution = Conflict_Resolution_Linear,	// ����ɢ�б�����ͻʱ���õ�̽�鷽ʽ
	int zeroValue = -1);								// ����Ϊ������û�е�ֵ����ֵ��

// �ڲ��ÿ��ŵ�ַ����ɢ�б��в���
int open_address_hash_search(
	int key,
	const int* table,
	int tableLength,
	Hash_Function hashFunc = hash_remiander,			// ���� hash ����
	Conflict_Resolution = Conflict_Resolution_Linear,	// ����ɢ�б�����ͻʱ���õ�̽�鷽ʽ
	int zeroValue = -1);								// ����Ϊ������û�е�ֵ����ֵ��

//=========================================================
//					��������ϣ����
//=========================================================
struct Hash_Node{
	int key;
	Hash_Node* next;
};

// ����������������ɢ�б�
void create_link_hash_table(
	Hash_Node** table,
	int tableLength,
	const int* data,
	int dataLength,
	Hash_Function hashFunc = hash_remiander,// ���� hash ����
	int zeroValue = -1);					// ����Ϊ������û�е�ֵ����ֵ��

// ���ٲ�����������ɢ�б�
void destroy_link_hash_table(
	Hash_Node* table,
	int tableLength);

// �ڲ�����������ɢ�б��в���
int link_hash_search(
	int key,
	const Hash_Node* hashTable,
	int tableLength,
	Hash_Function hashFunc = hash_remiander,// ���� hash ����
	int zeroValue = -1);					// ����Ϊ������û�е�ֵ����ֵ��


#endif // __SEARCH_ALGORITHMS_H__