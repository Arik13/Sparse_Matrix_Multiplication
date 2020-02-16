#include "AVL_Tree.h"
#include <stdio.h>

AVL_Tree::AVL_Tree(int val) {
	root = new AVL_Node(val);
}

AVL_Tree::~AVL_Tree() {
	delete root;
}

void AVL_Tree::access(int val) {

}

void AVL_Tree::insert(int val) {
	insert(root, val);
	root = balance(root);
	recalculateHeight(root);
}

void AVL_Tree::remove(int val) {

}

bool AVL_Tree::search(int val) {
	return search(root, val);
}

void AVL_Tree::insert(AVL_Node* node, int val) {
	if (val > node->key) {
		if (node->right) {
			insert(node->right, val);
			node->height = node->right->height + 1;
		}
		else {
			node->right = new AVL_Node(val);
			if (!node->left) node->height++;
		}
	}
	else {
		if (node->left) {
			insert(node->left, val);
			node->height = node->left->height + 1;
		}
		else {
			node->left = new AVL_Node(val);
			if (!node->right) node->height++;
		}
	}
	
	node->left = balance(node->left);
	node->right = balance(node->right);
	recalculateHeight(node);
}

bool AVL_Tree::search(AVL_Node* node, int val) {
	if (val == node->key) return true;
	else if (val < node->key) {
		if (node->left) {
			return search(node->left, val);
		}
		else {
			return false;
		}
	}
	else {
		if (node->right) {
			return search(node->right, val);
		}
		return false;
	}
}

AVL_Node* AVL_Tree::balance(AVL_Node* node) {
	if (!node) return node;
	int lh = (node->left) ? node->left->height : 0;
	int rh = (node->right) ? node->right->height : 0;
	int bf = lh - rh;
	if (bf > -2 && bf < 2) return node;
	//printf("Found unbalanced tree\n");
	// Left heavy case
	if (lh > rh) {
		int slh = (node->left->left) ? node->left->left->height : 0;
		int srh = (node->left->right) ? node->left->right->height : 0;
		// Double left heavy
		if (slh > srh) {
			//printf("Double left heavy\n");
			AVL_Node* newNode = rightRotate(node);
			return newNode;
		}
		// Left-right heavy
		else {
			//printf("Left right heavy\n");
			AVL_Node* newNode = rightLeftRotate(node);
			return newNode;
		}
	}
	// Right heavy case
	else {
		int slh = (node->right->left) ? node->right->left->height : 0;
		int srh = (node->right->right) ? node->right->right->height : 0;
		// Right left heavy
		if (slh > srh) {
			//printf("Right left heavy\n");
			AVL_Node* newNode = leftRightRotate(node);
			return newNode;
		}
		// Double right heavy
		else {
			//printf("Double right heavy\n");
			AVL_Node* newNode = leftRotate(node);
			return newNode;
		}
	}
}

AVL_Node* AVL_Tree::leftRotate(AVL_Node* node) {
	AVL_Node* b = node->right;
	node->right = b->left;
	b->left = node;
	recalculateHeight(node);
	recalculateHeight(b);
	return b;
}

AVL_Node* AVL_Tree::rightRotate(AVL_Node* node) {
	AVL_Node* b = node->left;
	node->left = b->right;
	b->right = node;
	recalculateHeight(node);
	recalculateHeight(b);
	return b;
}

AVL_Node* AVL_Tree::leftRightRotate(AVL_Node* node) {
	node->right = rightRotate(node->right);
	return leftRotate(node);
}

AVL_Node* AVL_Tree::rightLeftRotate(AVL_Node* node) {
	node->left = leftRotate(node->left);
	return rightRotate(node);
}

void AVL_Tree::recalculateHeight(AVL_Node* node) {
	if (!node) return;
	int lh = (node->left) ? node->left->height : 0;
	int rh = (node->right) ? node->right->height : 0;
	node->height = std::max(lh, rh) + 1;
}

void AVL_Tree::printTree() {
	std::map<int, std::vector<int>*> treeArr;
	printf("B: ");
	printTree(root, 0);
}

void AVL_Tree::printTree(AVL_Node* node, int depth) {
	if (!node) return;
	printf("Depth: %d -- Height: %d -- Val: %d -- L: %d -- R: %d\n", depth, node->height, node->key, (node->left)? node->left->key : -1, (node->right)? node->right->key : -1);
	if (node->left) {
		printf("L: ");
		printTree(node-> left, depth + 1);
	}
	if (node->right) {
		printf("R: ");
		printTree(node->right, depth + 1);
	}
}

AVL_Node::AVL_Node(int key) {
	this->left = nullptr;
	this->right = nullptr;
	this->key = key;
	this->height = 1;
}
