#include "BinarySearchTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void BST_insert(BSTree* tree, int key)
{
	assert(tree);

	BSTNode* parent;
	BSTNode* node = *tree;

	// find the parent that will add the new node.
	while (node) {
		// already exists
		if (node->key == key) {
			return;
		}

		parent = node;

		if (key < node->key) {
			node = node->leftChild;
		}
		else {
			node = node->rightChild;
		}
	}

	// malloc a new node.
	node = (BSTNode*)malloc(sizeof(BSTNode));
	if (!node) {
		printf("Error: out of memory!\n");
		return;
	}

	node->key = key;
	node->leftChild = NULL;
	node->rightChild = NULL;

	// tree is empty.
	if (NULL == *tree) {
		*tree = node;
	}

	else {
		// insert the node to the tree.
		if (key < parent->key) {
			parent->leftChild = node;
		}
		else {
			parent->rightChild = node;
		}
	}
}

void BST_remove(BSTree* tree, int key)
{
	assert(tree);

	BSTNode* parent = NULL, *temp = NULL;
	BSTNode* node = *tree;

	// find the node.
	while (node) {
		if (node->key == key) {
			break;
		}

		parent = node;

		if (key < node->key) {
			node = node->leftChild;
		}
		else {
			node = node->rightChild;
		}
	}

	// tree root node equals the key
	if (NULL == parent) {
		free(*tree);
		*tree = NULL;
		return;
	}

	if (!parent->rightChild) {
		assert(parent->leftChild);

		parent->key = parent->leftChild->key;
		free(parent->leftChild);
		parent->leftChild = NULL;
	}
	else {
		// find the most left child of parent in the right-child-tree
		// add set it as new parent.
		//   parent
		//      \
		//      ...
		//         \
		//          temp
		//          /
		//        node           <----- remove this node
		//            \
		//             rightChild

		node = parent->rightChild;
		temp = node
		while (node->leftChild) {
			temp = node;
			node = node->leftChild;
		}

		assert(temp);

		temp->leftChild = node->rightChild;
		parent->key = node->key;

		free(node);
	}
}

BSTNode* BST_search(BSTree* tree, int key)
{
	assert(tree);

	BSTNode* node = *tree;
	while (node) {
		if (key == node->key) {
			return node;
		}

		else {
			if (key < node->key) {
				node = node->leftChild;
			}
			else {
				node = node->rightChild;
			}
		}
	}

	return NULL;
}

// Æ½ºâ¶þ²æÊ÷(Balanced Binary Tree)
//
void BBT_insert(BSTree* tree, int key)
{

}

void BBT_remove(BSTree* tree, int key)
{

}

void BST_create(BSTree* tree, int* data, int length)
{
	assert(tree && data && length >= 0);

	// create a empty tree
	if (length == 0) {
		*tree = (BSTNode*)malloc(sizeof(BSTNode));
		return;
	}

	*tree = NULL;

	int i;
	for (i = 0; i < length; ++i) {
		BST_insert(tree, data[i]);
	}
}

void BST_destory(BSTree* tree)
{
	BSTNode* node = *tree;
	if (node) {
		BST_destory(&node->leftChild);
		BST_destory(&node->rightChild);

		free(node);
		node = NULL;
	}
}
