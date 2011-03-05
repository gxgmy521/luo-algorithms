#include "BTree.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

#define DEBUG_TREE

#ifdef DEBUG_TREE
#define debug_print(fmt,...) printf(fmt, ## __VA_ARGS__)
#else
#define debug_print(fmt,...)
#endif

BTNode* BTree_search(const BTree tree, int key, int* pos)
{
	assert(tree);
	
	int i = 0;

	while (i < tree->keynum && key > tree->key[i]) {
		++i;
	}

	// Find the key.
	if (i < tree->keynum && tree->key[i] == key) {
		if (pos) {
			*pos = i;
		}

		return tree;
	}

	// tree ΪҶ�ӽڵ㣬�Ҳ��� key������ʧ�ܷ���
	if (tree->isLeaf) {
		return NULL;
	}

	// �ڵ��ڲ���ʧ�ܣ��� tree->key[i - 1]< key < tree->key[i]��
	// ��һ�����ҵĽ��ӦΪ child[i]

	// �ݹ�ؼ����������� tree->child[i]
	return BTree_search(tree->child[i], key, pos);
}

// parent ��һ�������ĸ��ڵ�
// node �� tree ���ӱ����±�Ϊ index �ĺ��ӽڵ㣬��������
void BTree_split_child(BTNode* parent, int index, BTNode* node)
{
	assert(parent && node);

	int i;

	// �����½ڵ㣬�洢 node �к�벿�ֵ�����
	BTNode* newNode = (BTNode*)calloc(sizeof(BTNode), 1);
	if (!newNode) {
		printf("Error! out of memory!\n");
		return;
	}
	
	newNode->isLeaf = true;
	newNode->keynum = BTree_T - 1;

	// ���� node ��벿�ֹؼ���
	for (i = 0; i < newNode->keynum; ++i){
		newNode->key[i] = node->key[BTree_T + i];
	}

	// ��� node ����Ҷ�ӽڵ㣬���� node ��벿�ֵĺ��ӽڵ�
	if (!node->isLeaf) {
		for (i = 0; i < BTree_T; i++) {
			newNode->child[i] = node->child[BTree_T + i];
		}
	}

	// �� node ���ѳ� newNode ֮����������ݼ���
	node->keynum = BTree_T - 1;

	// �������ڵ�
	for (i = parent->keynum; i > index; --i) {
		parent->child[i + 1] = parent->child[i]; 
	}

	parent->child[index + 1] = newNode;

	for (i = parent->keynum - 1; i >= index; --i) {
		parent->key[i + 1] = parent->key[i];
	}

	parent->key[index] = node->key[BTree_T - 1];
	++parent->keynum;

	// ��� node �е��к�����
	//
	for (i = BTree_T - 1; i < BTree_N; ++i) {
		node->key[i] = '-';
		node->child[i + 1] = NULL;
	}
}

void BTree_insert_nonfull(BTNode* node, int key)
{
	assert(node);

	int i;

	// �ڵ���Ҷ�ӽڵ㣬ֱ�Ӳ��루ע�⣺�ڵ���������һ�����ݣ�
	if (node->isLeaf) {
		assert(node->keynum >= 1);

		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			node->key[i + 1] = node->key[i];
			--i;
		}
		
		node->key[i + 1] = key;
		++node->keynum;
	}

	// �ڵ����ڲ��ڵ�
	else {
		// ���Ҳ����λ��
		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			--i;
		}

		++i;

		// ����ú��ӽڵ����������ѵ���ֵ
		if (node->child[i]->keynum == BTree_N) {
			BTree_split_child(node, i, node->child[i]);

			if (key > node->key[i]) {
				++i;
			}
		}

		BTree_insert_nonfull(node->child[i], key);
	}
}

void BTree_insert(BTree* tree, int key)
{
	BTNode* node;
	BTNode* root = *tree;

	// ��Ϊ��
	if (NULL == root) {
		root = (BTNode*)calloc(sizeof(BTNode), 1);
		if (!root) {
			printf("Error! out of memory!\n");
			return;
		}
		root->isLeaf = true;
		root->keynum = 1;
		root->key[0] = key;

		*tree = root;
		return;
	}

	// �ڵ���������Ҫ���з��ѵ���
	if (root->keynum == BTree_N) {
		// �����½ڵ㵱����
		node = (BTNode*)calloc(sizeof(BTNode), 1);
		if (!node) {
			printf("Error! out of memory!\n");
			return;
		}
	
		*tree = node;
		node->isLeaf = false;
		node->keynum = 0;
		node->child[0] = root;

		BTree_split_child(node, 0, root);

		BTree_insert_nonfull(node, key);
	}

	// �ڵ�δ�����ڵ�ǰ�ڵ��в��� key
	else {
		BTree_insert_nonfull(root, key);
	}
}

void BTree_remove(BTree* tree, int key)
{
	assert(tree);

}

void BTree_create(BTree* tree, const int* data, int length)
{
	assert(tree);

	int i;
	for (i = 0; i < length; i++) {
		BTree_insert(tree, data[i]);
	}
}

void BTree_destory(BTree* tree)
{
	assert(tree);

}

