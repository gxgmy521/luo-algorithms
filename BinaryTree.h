#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

struct BSTNode {
	int key;
	BSTNode* leftChild;
	BSTNode* rightChild;
};

typedef BSTNode* BSTree;

// 二叉查找树(Binary Search Tree)
//
void BST_insert(BSTree* tree, int key);

void BST_remove(BSTree* tree, int key);

BSTNode* BST_search(const BSTree tree, int key);

void BST_create(BSTree* tree, const int* data, int length);

void BST_destory(BSTree* tree);


// 平衡二叉树(Balanced Binary Tree)
//
void BBT_insert(BSTree* tree, int key);

void BBT_remove(BSTree* tree, int key);

#endif // __BINARY_TREE_H__
