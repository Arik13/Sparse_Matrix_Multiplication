#include "AVL_Tree.h"

int main() {
	printf("Program initiated\n");
	const int n = 200;
	int randomArray[n];
	for (int i = 0; i < n; i++) {
		randomArray[i] = rand() % 1000;
		printf("%d ", randomArray[i]);
	}
	printf("\n");
	AVL_Tree* av = new AVL_Tree(randomArray[0]);
	for (int i = 1; i < n; i++) {
		av->insert(randomArray[i]);
	}
	for (int i = 0; i < n; i++) {
		printf("%d exists: %s\n", randomArray[i], (av->search(randomArray[i])? "True" : "False"));
	}
	av->printTree();
	return 0;
}