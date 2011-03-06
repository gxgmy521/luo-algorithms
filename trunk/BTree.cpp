#include "BTree.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

//#define DEBUG_TREE

#ifdef DEBUG_TREE
#define debug_print(fmt,...) printf(fmt, ## __VA_ARGS__)
#else
#define debug_print(fmt,...)
#endif

void disk_write(BTNode* node)
{
	printf("向磁盘写入节点\n");
}

void disk_read(BTNode** node)
{
	printf("从磁盘读取节点\n");
}

void BTree_print(BTree tree, int her) 
{
	int i;
	BTNode* node = tree;

	if (node) {
		printf("第 %d 层， %d node : ", her, node->keynum);

		for (i = 0; i < node->keynum; ++i) {
			printf("%c ", node->key[i]);
		}

		printf("\n");

		++her;
		for (i = 0 ; i <= BTree_N; i++) {
			if (node->child[i]) {
				BTree_print(node->child[i], her);
			}
		}
	}
}

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

	// tree 为叶子节点，找不到 key，查找失败返回
	if (tree->isLeaf) {
		return NULL;
	}

	// 节点内查找失败，但 tree->key[i - 1]< key < tree->key[i]，
	// 下一个查找的结点应为 child[i]

	// 从磁盘读取第 i 个孩子的数据
	disk_read(&tree->child[i]);

	// 递归地继续查找于树 tree->child[i]
	return BTree_search(tree->child[i], key, pos);
}

// parent 是一个非满的父节点
// node 是 tree 孩子表中下标为 index 的孩子节点，且是满的
void BTree_split_child(BTNode* parent, int index, BTNode* node)
{
	assert(parent && node);

	int i;

	// 创建新节点，存储 node 中后半部分的数据
	BTNode* newNode = (BTNode*)calloc(sizeof(BTNode), 1);
	if (!newNode) {
		printf("Error! out of memory!\n");
		return;
	}
	
	newNode->isLeaf = true;
	newNode->keynum = BTree_T - 1;

	// 拷贝 node 后半部分关键字
	for (i = 0; i < newNode->keynum; ++i){
		newNode->key[i] = node->key[BTree_T + i];
	}

	// 如果 node 不是叶子节点，拷贝 node 后半部分的孩子节点
	if (!node->isLeaf) {
		for (i = 0; i < BTree_T; i++) {
			newNode->child[i] = node->child[BTree_T + i];
		}
	}

	// 将 node 分裂出 newNode 之后，里面的数据减半
	node->keynum = BTree_T - 1;

	// 调整父节点
	for (i = parent->keynum; i > index; --i) {
		parent->child[i + 1] = parent->child[i]; 
	}

	parent->child[index + 1] = newNode;

	for (i = parent->keynum - 1; i >= index; --i) {
		parent->key[i + 1] = parent->key[i];
	}

	parent->key[index] = node->key[BTree_T - 1];
	++parent->keynum;

	// 清除 node 中的中后部数据
	// 可以不处理，因为是通过 keynum 控制访问的
// 	for (i = BTree_T - 1; i < BTree_N; ++i) {
// 		node->key[i] = 0;
// 		node->child[i + 1] = NULL;
// 	}

	// 写入磁盘
 	disk_write(parent);
 	disk_write(newNode);
 	disk_write(node);
}

void BTree_insert_nonfull(BTNode* node, int key)
{
	assert(node);

	int i;

	// 节点是叶子节点，直接插入（注意：节点至少已有一个数据）
	if (node->isLeaf) {
		assert(node->keynum >= 1);

		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			node->key[i + 1] = node->key[i];
			--i;
		}
		
		node->key[i + 1] = key;
		++node->keynum;

		// 写入磁盘
		disk_write(node);
	}

	// 节点是内部节点
	else {
		// 查找插入的位置
		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			--i;
		}

		++i;

		// 从磁盘读取孩子节点
		disk_read(&node->child[i]);

		// 如果该孩子节点已满，分裂调整值
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

	// 树为空
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

		// 写入磁盘
		disk_write(root);

		return;
	}

	// 节点已满，需要进行分裂调整
	if (root->keynum == BTree_N) {
		// 产生新节点当作根
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

	// 节点未满，在当前节点中插入 key
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

#ifdef DEBUG_TREE
	debug_print("\n 开始创建 B- 树，关键字为:\n");
	for (i = 0; i < length; i++) {
		printf(" %c ", data[i]);
	}
	debug_print("\n");
#endif

	
	for (i = 0; i < length; i++) {
#ifdef DEBUG_TREE
		debug_print("\n插入关键字 %c:\n", data[i]);
#endif
		BTree_insert(tree, data[i]);

#ifdef DEBUG_TREE
		BTree_print(*tree);
#endif
	}

	debug_print("\n");
}

void BTree_destory(BTree* tree)
{
	int i;
	BTNode* node = *tree;

	if (node) {
		for (i = 0; i <= node->keynum; i++) {
			BTree_destory(&node->child[i]);
		}

		free(node);
	}

	*tree = NULL;
}

