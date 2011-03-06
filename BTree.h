#ifndef __BTREE_SEARCH_H__
#define __BTREE_SEARCH_H__

// B- ��
//

// ����B- ������С����
// ÿ���ڵ��йؼ��ֵ������Ŀ BTree_N = 2 * BTree_T - 1
#define	BTree_T		2
#define BTree_N		(BTree_T * 2 - 1)

struct BTNode {
	int	keynum;						// ����йؼ��ֵĸ�����keynum <= BTree_N
	int key[BTree_N];				// �ؼ�������Ϊkey[0..keynum - 1]
	BTNode* child[BTree_T * 2];		// ����ָ������Ϊchild[0..keynum]
	bool isLeaf;					// �Ƿ���Ҷ�ӽڵ�ı�־
};

typedef BTNode* BTree;				// B-��������


void BTree_create(BTree* tree, const int* data, int length);

void BTree_destory(BTree* tree);

void BTree_insert(BTree* tree, int key);

void BTree_remove(BTree* tree, int key);

void BTree_print(BTree tree, int her = 1);

// ��B-�� tree �в��ҹؼ��� key��
// �ɹ�ʱ�����ҵ��Ľڵ�ĵ�ַ�� key �����е�λ�� *pos
// ʧ��ʱ���� NULL ������ʧ��ʱɨ�赽�Ľڵ�λ�� *pos
//
BTNode* BTree_search(const BTree tree, int key, int* pos);


#endif	// __BTREE_SEARCH_H__