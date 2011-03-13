#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__

enum RBColor{
	RB_Red,
	RB_Black,
};

struct RBNode 
{
	RBColor color;
	int key;
	RBNode* leftChild;
	RBNode* rightChild;
	RBNode* parent;
};

typedef RBNode* RBTree;

static RBNode RBNode_Nil = {RB_Black, 0, 0, 0, 0};

// ��С�ؼ���Ԫ��
RBNode* RBTree_minimum(RBNode* x);

// ǰ��
RBNode* RBTree_successor(RBNode* x);

void RBTree_insert(RBTree* tree, RBNode* node);

RBNode* RBTree_delete(RBTree* tree, RBNode* node);

#endif	// __RED_BLACK_TREE_H__