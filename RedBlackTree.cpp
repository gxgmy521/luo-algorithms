#include "RedBlackTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// ��С�ؼ���Ԫ��
RBNode* RBTree_minimum(RBNode* x)
{
	while (x->leftChild != &RBNode_Nil) {
		x = x->leftChild;
	}

	return x;
}

// ǰ��
RBNode* RBTree_successor(RBNode* x)
{
	if (x->rightChild != &RBNode_Nil) {
		return RBTree_minimum(x->rightChild);
	}

	RBNode* y = x->parent;

	while (y != &RBNode_Nil && x == y->rightChild) {
		x = y;
		y = y->parent;
	}

	return y;
}

// ����
//            node                        right
//           /    \                      /     \
//          a    right     -->         node     c  
//              /     \               /    \
//             b       c             a      b
//
void RBTree_left_rotate(RBTree* tree, RBNode* node)
{
	assert(node->rightChild && (*tree)->parent == &RBNode_Nil);

	RBNode* right = node->rightChild;

	// set b
	node->rightChild = right->leftChild;
	if (right->leftChild != &RBNode_Nil) {
		right->leftChild->parent = node;
	}

	right->parent = node->parent;
	if (node->parent == &RBNode_Nil) {
		*tree = right;
	}
	else if (node->parent->leftChild == node) {
		node->parent->leftChild = right;
	}
	else {
		node->parent->rightChild = right;
	}

	right->leftChild = node;
	node->parent = right;
}

// ����
//            node                  left
//           /    \                /    \
//         left    c     -->      a     node  
//        /     \                      /    \
//       a       b                    b      c
//
void RBTree_right_rotate(RBTree* tree, RBNode* node)
{
	assert(node->leftChild && (*tree)->parent == &RBNode_Nil);

	RBNode* left = node->leftChild;

	// set b
	node->leftChild = left->rightChild;
	if (left->rightChild != &RBNode_Nil) {
		left->rightChild->parent = node;
	}

	left->parent = node->parent;
	if (node->parent == &RBNode_Nil) {
		*tree = left;
	}
	else if (node->parent->leftChild == node) {
		node->parent->leftChild = left;
	}
	else {
		node->parent->rightChild = left;
	}

	left->rightChild = node;
	node->parent = left;
}

// �������
void RBTree_insert_fixup(RBTree* tree, RBNode* node)
{
	assert(tree && node);

	RBNode* uncle = NULL;
	RBNode* grand = NULL;

	while (node->parent->color == RB_Red) {
		grand = node->parent->parent;

		// ȷ���常�ڵ�
		if (node->parent == grand->leftChild) {
			uncle = grand->rightChild;
		}
		else {
			uncle = grand->rightChild;
		}

		// case 1: �常�ڵ�Ϊ��ɫ
		//         grand(B)        new node  ->    grand(R)          
		//         /     \                         /      \ 
		//   parent(R)    uncle(R)    -->     node(B)   uncle(B)
		//   /     \      /  \                /   \        /  \
 		//  a    node(R) d    e          parent  node(R)  d    e
		//       /   \                          /   \
		//      b     c                        b     c
		//
		if (uncle->color == RB_Red) {
			node->parent->color = RB_Black;
			uncle->color = RB_Black;
			grand->color = RB_Red;
			node = grand;
		}

		// case 2, case 3���常�ڵ�Ϊ��ɫ	
		//         case 2     --->    case 3         -->  done
		//                      parent is as new node
		//         grand(B)          grand(B)            node(B)
		//         /     \           /      \           /      \
 		//   parent(R)    d       node(R)   d      parent(R)  grand(R)
		//   /     \               /     \           /  \      /   \
		//  a    node(R)      parent(R)   c         a    b    c     d
 		//       /   \         /  \
		//      b     c       a    b
		//
		else {
			// �� case 2 װ���� case 3
			if (node->parent->rightChild == node) {
				node = node->parent;

				RBTree_left_rotate(tree, node);
			}

			// case 3
			node->parent->color = RB_Black;
			node->parent->parent->color = RB_Red;

			RBTree_right_rotate(tree, node->parent->parent);
		}
	}

	(*tree)->color = RB_Black;
}

// ���ڵ� node ������ tree �ڣ�Ȼ�� node ��ɫΪ��ɫ����ʱ�������ܲ���
// �����������ʣ���˵��� RBTree_insert_fixup ���Խڵ�������ɫ������
void RBTree_insert(RBTree* tree, RBNode* node)
{
	assert(tree && node);
	
	RBNode* parent = &RBNode_Nil;
	RBNode* temp = *tree;

	// �������һ���������в����ʵ���λ�ò���
	while (temp != &RBNode_Nil) {
		parent = temp;

		if (node->key < temp->key) {
			temp = temp->leftChild;
		}
		else {
			temp = temp->rightChild;
		}
	}

	node->parent = parent;

	// ��Ϊ��
	if (parent == &RBNode_Nil) {
		*tree = node;
	}
	else if (node->key < parent->key) {
		parent->leftChild = node;
	}
	else {
		parent->rightChild = node;
	}

	// Ϊ�ڵ���ɫ
	node->leftChild = &RBNode_Nil;
	node->rightChild = &RBNode_Nil;
	node->color = RB_Red;

	// ������ʹ֮������������
	RBTree_insert_fixup(tree, node);
}

// ɾ������
void RBTree_delete_fixup(RBTree* tree, RBNode* x)
{

}

// ɾ��
RBNode* RBTree_delete(RBTree* tree, RBNode* z)
{
	RBNode* x = NULL;
	RBNode* y = NULL;

	if (z->leftChild == &RBNode_Nil || z->rightChild == &RBNode_Nil) {
		y = z;
	}
	else {
		y = RBTree_successor(z);
	}

	if (y->leftChild != &RBNode_Nil) {
		x = y->leftChild;
	}
	else {
		x = y->rightChild;
	}

	x->parent = y->parent;

	if (y->parent == &RBNode_Nil) {
		*tree = x;
	}
	else {
		if (y == y->parent->leftChild) {
			y->parent->leftChild = x;
		}
		else {
			y->parent->rightChild = x;
		}
	}

	if (y != z) {
		z->key = y->key;
	}

	if (y->color == RB_Black) {
		RBTree_delete_fixup(tree, x);
	}

	return y;
}