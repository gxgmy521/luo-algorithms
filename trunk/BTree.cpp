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
	
	int i = 1;

	while (i <= tree->keynum && key > tree->key[i]) {
		++i;
	}

	// Find the key.
	if (i <= tree->keynum && tree->key[i] == key) {
		if (pos) {
			*pos = i;
		}

		return tree;
	}

	// tree 为叶子节点，找不到 key，查找失败返回
	if (tree->isLeaf) {
		return NULL;
	}

	// 节点内查找失败，但 tree->key[i - 1]< key < tree->key[i]，
	// 下一个查找的结点应为 child[i - 1]

	// 递归地继续查找于树 tree->child[i - 1]
	return BTree_search(tree->child[i - 1], key, pos);
}

// tree 是一个非满节点
// child 是 tree 的第 i 个孩子节点，且是满的
void BTree_split_child(BTNode* parent, int i, BTNode* node)
{
	assert(parent && node);

	int j;

	// creat a new node
	//
	BTNode* newNode = (BTNode*)calloc(sizeof(BTNode), 1);
	if (!newNode) {
		printf("Error! out of memory!\n");
		return;
	}

	newNode->isLeaf = true;

	// get the position of slit
	//
	int mid = BTree_T;

	// set newNode(bigger children of child node)
	//
	newNode->keynum = mid - 1;
	for (j = 0; j < newNode->keynum; ++j) {
		newNode->key[j] = node->key[mid + j];
	}

	if (!node->isLeaf) {
		for (j = 0; j < mid - 1; ++j) {
			newNode->child[j] = node->child[mid + j];
		}
	}

	// reset child(smaller children of child node)
	//
	node->keynum = mid - 1;

	// adjust tree
	//
	for (j = parent->keynum; j >= i; --j) {
		parent->child[j + 1] = parent->child[j]; 
	}

	parent->child[i] = newNode;

	for (j = parent->keynum - 1; j >= i; --j) {
		parent->key[j + 1] = parent->key[j];
	}

	parent->key[i - 1] = node->key[mid - 1];
	++parent->keynum;

	// clear node
	//
	for (j = mid - 1; j < BTree_N; ++j) {
		node->key[j] = '-';
		node->child[j] = NULL;
	}
}

void BTree_insert_nonfull(BTNode* node, int key)
{
	int i = node->keynum;
	if (node->isLeaf) {
		while (i >= 1 && key < node->key[i - 1]) {
			node->key[i] = node->key[i - 1];
			--i;
		}

		node->key[i] = key;
		++node->keynum;
	}

	else {
		// find the child to be inserted.
		while (i >= 0 && key < node->key[i]) {
			--i;
		}
		
		//++i;

		// child is full
		//
		if (node->child[i]->keynum == BTree_N) {
			BTree_split_child(node, i + 1, node->child[i]);

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

	if (root->keynum == BTree_N) {
		node = (BTNode*)calloc(sizeof(BTNode), 1);
		if (!node) {
			printf("Error! out of memory!\n");
			return;
		}

		*tree = node;
		node->isLeaf = false;
		node->keynum = 0;
		node->child[0] = root;

		BTree_split_child(node, 1, root);

		BTree_insert_nonfull(node, key);
	}
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

}

void BTree_destory(BTree* tree)
{
	assert(tree);

}

