#include <stdio.h>
#include <stdlib.h>

struct Node {
	int key;
	int size;
	Node* parent;
	Node* left;
	Node* right;
};

Node* newNode(int key) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->size = 0;
	return node;
}

Node* buildTree(int arr[], int start, int end) {
	if (start > end) {
		return NULL;
	}
	int mid = (start + end) / 2;
	Node* root = newNode(arr[mid]);
	root->left = buildTree(arr, start, mid - 1);
	root->right = buildTree(arr, mid + 1, end);
	root->size = end - start + 1;
	return root;
}

void preOrderPrint(Node* node) {
	if (node == NULL) {
		return;
	}
	printf("%d ", node->key);
	preOrderPrint(node->left);
	preOrderPrint(node->right);
}

void printTree(Node* node, int heigth) {
	if (node!=NULL) {
		printTree(node->right, heigth + 1);
		for (int i = 0; i <= heigth; i++) {
			printf("\t");
		}
		printf("%d,%d\n", node->key, node->size);
		printTree(node->left, heigth + 1);
	}
}

int main() {
	int arr[] = { 1,2,3,4,5,6,7,8,9,10,11 };
	int n =11;
	Node* root = buildTree(arr, 0, n - 1);
	printf("\nPreOrder traversal of the balanced BST: ");
	preOrderPrint(root);
	printf("\n");
	printTree(root, 0);
	getchar();
	return 0;
}