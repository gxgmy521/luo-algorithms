#include "BinaryTree.h"
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

	// key is not in the tree.
	if (!node) {
		printf("Can not remove %d, it is not in the tree!\n", key);
		return;
	}

	// ����ڵ���Ҷ�ӽڵ㣬ֱ��ɾ�����Ѹ��ڵ���Ӧ��������Ϊ NULL
	if (NULL == node->leftChild && NULL == node->rightChild) {
		// tree root node equals the key
		if (node == *tree) {
			*tree = NULL;
		}
		else {
			assert(parent);

			if (parent->leftChild == node) {
				parent->leftChild = NULL;
			}
			else {
				parent->rightChild = NULL;
			}
		}

		free(node);
	}

	// ����ڵ�����Ӳ�Ϊ�գ��Һ���Ϊ��
	else if (NULL != node->leftChild) {
		if (parent->leftChild == node) {
			parent->leftChild = node->leftChild;
		}
		else {
			parent->rightChild = node->leftChild;
		}

		free(node);
	}

	// ����ڵ���Һ��Ӳ�Ϊ�գ�����Ϊ��
	else if (NULL != node->rightChild) {
		if (parent->leftChild == node) {
			parent->leftChild = node->rightChild;
		}
		else {
			parent->rightChild = node->rightChild;
		}

		free(node);
	}

	// �ڵ�����Һ��Ӿ���Ϊ��
	else {
		// find the most left child of node in the right-child-tree
		// add set it as new parent.
		//
		//          node		<----- replace this node
		//		   /    \
		//       ...    ...
		//             /
		//           temp       <----- remove most left child
		//          /    \
		//        null  rightChild

		parent = node;
		temp = node->rightChild;
		while (temp->leftChild) {
			parent = temp;
			temp = temp->leftChild;
		}

		assert(temp);

		node->key = temp->key;
		parent->leftChild = temp->rightChild;

		free(node);
	}
}

BSTNode* BST_search(BSTree tree, int key)
{
#if 1
	// �ݹ�ʵ��
	if (tree == NULL || tree->key == key) {
		return tree;
	}
	else if (key < tree->key) {
		return BST_search(tree->leftChild, key);
	}
	else {
		return BST_search(tree->rightChild, key);
	}
#else
	// ѭ��ʵ��
	BSTNode* node = tree;
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
#endif
	return NULL;
}

// ƽ�������(Balanced Binary Tree)
//
void BBT_insert(BSTree* tree, int key)
{

}

void BBT_remove(BSTree* tree, int key)
{

}

// �����������ݴ���������
//
void BST_create(BSTree* tree, const int* data, int length)
{
	assert(tree && length >= 0);

	*tree = NULL;

	if (!data || length == 0) {
		return;
	}

	int i;
	for (i = 0; i < length; ++i) {
		BST_insert(tree, data[i]);
	}
}

// ���ٶ�����
//
void BST_destory(BSTree* tree)
{
	BSTNode* node = *tree;
	if (node) {
		BST_destory(&node->leftChild);
		BST_destory(&node->rightChild);

		free(node);
		node = NULL;
	}

	*tree = NULL;
}

// ǰ�����
void BST_prev_order_impl(BSTree tree, int* data, int& index)
{
    assert(data && tree && index >= 0);

    data[index] = tree->key;

    if (tree->leftChild) {
        BST_prev_order_impl(tree->leftChild, data, index);
    }

    if (tree->rightChild) {
        BST_prev_order_impl(tree->rightChild, data, ++index);
    }
}

void BST_prev_order(BSTree* tree, int* data)
{
    assert(data);

    if (!tree) {
        return;
    }

    int index = 0;

    BST_prev_order_impl(*tree, data, index);
}

// �������
void BST_in_order_impl(BSTree tree, int* data, int& index)
{
    assert(data && tree && index >= 0);

    if (tree->leftChild) {
        BST_in_order_impl(tree->leftChild, data, ++index);
    }

    data[index] = tree->key;

    if (tree->rightChild) {
        BST_in_order_impl(tree->rightChild, data, ++index);
    }
}

void BST_in_order(BSTree* tree, int* data)
{
    assert(data);

    if (!tree) {
        return;
    }

    int index = 0;

    BST_in_order_impl(*tree, data, index);
}

// �������
void BST_post_order_impl(BSTree tree, int* data, int& index)
{
    assert(data && tree && index >= 0);

    if (tree->leftChild) {
        BST_post_order_impl(tree->leftChild, data, ++index);
    }

    if (tree->rightChild) {
        BST_post_order_impl(tree->rightChild, data, ++index);
    }

    data[index] = tree->key;
}

void BST_post_order(BSTree* tree, int* data)
{
    assert(data);

    if (!tree) {
        return;
    }

    int index = 0;

    BST_post_order_impl(*tree, data, index);
}
