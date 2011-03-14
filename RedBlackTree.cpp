#include "RedBlackTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// ��С�ؼ���Ԫ��
RBNode* RBTree_minimum(RBNode* node)
{
	assert(node);

	RBNode* temp = node;
	while (temp->leftChild != &RBNode_Nil) {
		temp = temp->leftChild;
	}

	return temp;
}


// ���ؼ���Ԫ��
RBNode* RBTree_maximum(RBNode* node)
{
	assert(node);

	RBNode* temp = node;
	while (temp->rightChild != &RBNode_Nil) {
		temp = temp->rightChild;
	}

	return temp;
}

// ��������е�ǰ��
RBNode* RBTree_predecessor(RBNode* node)
{
	assert(node);

	RBNode* child = node->leftChild;

	// û�����ӣ���������
	if (child == &RBNode_Nil) {
		return node;
	}

	// ֻ�����ӣ�����������ֱ��ǰ��
	else if (child->rightChild == &RBNode_Nil) {
		return child->leftChild;
	}

	// ���Һ��Ӿ��У����Һ�����������Ԫ��Ϊ��ֱ��ǰ��
	else {
		return RBTree_maximum(child->rightChild);
	}
}

// ��������еĺ��
RBNode* RBTree_successor(RBNode* node)
{
	// ���Һ��ӣ����Һ���������С��Ԫ��Ϊ��ֱ�Ӻ��
	if (node->rightChild != &RBNode_Nil) {
		return RBTree_minimum(node->rightChild);
	}

	// û���Һ��ӣ������ҵ��ĵ�һ�����֧�ڵ�Ϊ��ֱ�Ӻ�̣�
	// �� node Ϊ��ֱ�Ӻ�̵��������е����Ԫ�ء�
	RBNode* temp = node;
	RBNode* parent = temp->parent;

	while (parent != &RBNode_Nil && temp == parent->rightChild) {
		temp = parent;
		parent = temp->parent;
	}

	return parent;
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
		// ���ݺ�������ʣ��Լ� node �ĸ��׵���ɫΪ��ɫ��
		// ���Կ϶� node ���游�ڵ�һ������
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
void RBTree_delete_fixup(RBTree* tree, RBNode* node)
{
	RBNode* brother = NULL;

	while (node != *tree && node->color == RB_Black) {
		// ȷ���ֵܽڵ�
		if (node == node->parent->leftChild) {
			brother = node->parent->rightChild;
		}
		else {
			brother = node->parent->leftChild;
		}

		// case 1: �ֵܽڵ�Ϊ��ɫ
		if (brother->color == RB_Red) {
			brother->color = RB_Black;
			node->parent->color = RB_Red;

			RBTree_left_rotate(tree, node->parent);

			brother = node->parent->rightChild;
		}

		// case 2: �ֵܽڵ�������Ӿ�Ϊ��ɫ
		if (brother->leftChild->color == RB_Black
			&& brother->rightChild->color == RB_Black) {
				brother->color = RB_Red;
				node = node->parent;
		}

		else {
			// case 3: �ֵܽڵ������Ϊ��ɫ���Һ���Ϊ��ɫ
			if (brother->rightChild->color == RB_Black) {
				brother->leftChild->color = RB_Black;
				brother->color = RB_Red;

				RBTree_right_rotate(tree, brother);

				brother = node->parent->rightChild;
			}

			// case 4:�ֵܽڵ���Һ���Ϊ��ɫ
			brother->color = node->parent->color;
			node->parent->color = RB_Black;
			brother->rightChild->color = RB_Black;

			RBTree_left_rotate(tree, node->parent);

			node = *tree;
		}
	}

	node->color = RB_Black;
}

// ɾ��
RBNode* RBTree_delete(RBTree* tree, RBNode* node)
{
	RBNode* successor = NULL;
	RBNode* temp = NULL;

	if (node->leftChild == &RBNode_Nil || node->rightChild == &RBNode_Nil) {
		successor = node;
	}
	else {
		successor = RBTree_successor(node);
	}

	if (successor->leftChild != &RBNode_Nil) {
		temp = successor->leftChild;
	}
	else {
		temp = successor->rightChild;
	}

	temp->parent = successor->parent;

	if (successor->parent == &RBNode_Nil) {
		*tree = temp;
	}
	else {
		if (successor == successor->parent->leftChild) {
			successor->parent->leftChild = temp;
		}
		else {
			successor->parent->rightChild = temp;
		}
	}

	if (successor != node) {
		node->key = successor->key;
	}

	if (successor->color == RB_Black) {
		RBTree_delete_fixup(tree, temp);
	}

	return successor;
}