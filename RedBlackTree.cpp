#include "RedBlackTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// 最小关键字元素
RBNode* RBTree_minimum(RBNode* x)
{
	while (x->leftChild != &RBNode_Nil) {
		x = x->leftChild;
	}

	return x;
}

// 前驱
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

// 左旋
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

// 右旋
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

// 插入调整
void RBTree_insert_fixup(RBTree* tree, RBNode* node)
{
	assert(tree && node);

	RBNode* uncle = NULL;
	RBNode* grand = NULL;

	while (node->parent->color == RB_Red) {
		grand = node->parent->parent;

		// 确定叔父节点
		if (node->parent == grand->leftChild) {
			uncle = grand->rightChild;
		}
		else {
			uncle = grand->rightChild;
		}

		// case 1: 叔父节点为红色
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

		// case 2, case 3：叔父节点为黑色	
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
			// 将 case 2 装换成 case 3
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

// 将节点 node 插入树 tree 内，然后将 node 着色为红色，此时，树可能不再
// 满足红黑树性质，因此调用 RBTree_insert_fixup 来对节点重新着色调整。
void RBTree_insert(RBTree* tree, RBNode* node)
{
	assert(tree && node);
	
	RBNode* parent = &RBNode_Nil;
	RBNode* temp = *tree;

	// 像二叉树一样，在树中查找适当的位置插入
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

	// 树为空
	if (parent == &RBNode_Nil) {
		*tree = node;
	}
	else if (node->key < parent->key) {
		parent->leftChild = node;
	}
	else {
		parent->rightChild = node;
	}

	// 为节点着色
	node->leftChild = &RBNode_Nil;
	node->rightChild = &RBNode_Nil;
	node->color = RB_Red;

	// 调整树使之满足红黑树性质
	RBTree_insert_fixup(tree, node);
}

// 删除调整
void RBTree_delete_fixup(RBTree* tree, RBNode* x)
{

}

// 删除
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