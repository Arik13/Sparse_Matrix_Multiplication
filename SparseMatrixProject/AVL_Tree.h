#pragma once

#include <vector>
#include <algorithm>
#include <map>

class AVL_Node {
public:
	AVL_Node(int key);
	AVL_Node* left;
	AVL_Node* right;
	int key;
	int height;
};

class AVL_Tree {
public:
	AVL_Tree(int val);
	~AVL_Tree();
	void access(int val);
	void insert(int val);
	void remove(int val);
	bool search(int val);
	void printTree();
private:
	void insert(AVL_Node* node, int val);
	bool search(AVL_Node* node, int val);
	AVL_Node* balance(AVL_Node* node);
	AVL_Node* leftRotate(AVL_Node* node);
	AVL_Node* rightRotate(AVL_Node* node);
	AVL_Node* leftRightRotate(AVL_Node* node);
	AVL_Node* rightLeftRotate(AVL_Node* node);
	void recalculateHeight(AVL_Node* node);
	void printTree(AVL_Node* node, int depth);
	AVL_Node* root;
};

