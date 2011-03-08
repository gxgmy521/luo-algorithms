#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

struct BSTNode {
	int key;
	BSTNode* leftChild;
	BSTNode* rightChild;
};

typedef BSTNode* BSTree;

// ���������(Binary Search Tree)
//
void BST_insert(BSTree* tree, int key);

void BST_remove(BSTree* tree, int key);

BSTNode* BST_search(const BSTree tree, int key);

void BST_create(BSTree* tree, const int* data, int length);

void BST_destory(BSTree* tree);


// ƽ�������(Balanced Binary Tree)
//
void BBT_insert(BSTree* tree, int key);

void BBT_remove(BSTree* tree, int key);

// ����������
//
// ǰ�����
void BST_prev_order(BSTree* tree, int* data);

// �������
void BST_in_order(BSTree* tree, int* data);

// �������
void BST_post_order(BSTree* tree, int* data);

#endif // __BINARY_TREE_H__
