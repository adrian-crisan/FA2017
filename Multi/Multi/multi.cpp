#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include<iostream>

using namespace std;

int a[] = { 0, 2, 7, 5, 2, 7, 7, -1, 5, 2 }; //parent vector, offset to the right with one because of index issues
int n = 10;

struct node		//used for multi-way
{
	int key;		//key
	int nodesNo;    //number of nodes
	node *nodes[20];   //nodes
} arbitrary[9];

struct node2	//used for binary tree
{
	int key;	//key;
	node2 *left;    //left son
	node2 *right;   //right son
};

//from array to multiway tree
int toMultiWay(int a[]) {
	int mRoot = -1;			//multiway tree root
	for (int i = 1; i < n; i++) {
		arbitrary[i].key = i;       //arbitrary key gets index of son
		if (a[i] == -1)	{	    //if we find in array -1 value then mRoot gets value of i, the root
			mRoot = i;
		}
	}
	for (int i = 1; i < n; i++) {
		arbitrary[a[i]].nodes[arbitrary[a[i]].nodesNo++] = &arbitrary[i];			//create one more son
	}
	return mRoot;
}

void multiWayPrettyPrint(node *root, int level) // multiway pretty print
{
	if (root == NULL) 
		return;
	for (int i = 0; i < level; i++)
		printf("\t");
	printf("%d \n", root->key);
	for (int i = 0; i < root->nodesNo; i++)
		multiWayPrettyPrint(root->nodes[i], level + 1);
}

//from multiway to binary tree
void toBinary(node *root, node2 *root2) {
	int i;
	node2 *aux = (node2*)malloc(sizeof(node2));			//allocate memory for auxiliary node
	for (i = 0; i < root->nodesNo; i++) {
		if (i == 0) {
			root2->left = (node2*)malloc(sizeof(node2));	//allocate memory for left son, first node of the root of the multiway tree
			root2->left->key = root->nodes[i]->key;			
			root2->left->left = NULL;
			root2->left->right = NULL;
			aux = root2->left;								//auxiliary node gets left son of the binary tree root node
		}
		else {
			aux->right = (node2*)malloc(sizeof(node2));
			aux->right->left = NULL;
			aux->right->right = NULL;
			aux->right->key = root->nodes[i]->key;
			toBinary(root->nodes[i - 1], aux);				//recursive call with the next son of the multiway tree root and auxiliary node as the new root 
			aux = aux->right;								//auxiliary node gets the right son 
		}
	}
}

void prettyPrint(node2 *root, int level)
{
	if (root != NULL) {
		prettyPrint(root->right, level + 1);
		for (int i = 0; i <= level; i++) {
			printf("\t");
		}
		printf("%d \n", root->key);
		prettyPrint(root->left, level + 1);
	}

}

int main()
{
	printf("Input array: ");
	for (int i = 1; i<n; i++) {
		printf("%d ", a[i]);
	}

	printf("\n");
	printf("From array to multiway:\n");
	int root = toMultiWay(a);			//get the root of the multiway tree
	multiWayPrettyPrint(&arbitrary[root], 0);

	printf("From multiway to binary:\n\n");
	node2* root2 = new node2;			//create root of the binary tree
	root2->key = arbitrary[root].key;	//get binary tree key from the key of the root of the multiway
	root2->right = NULL;				//make right son NULL
	toBinary(&arbitrary[root], root2);	//transform the multiway tree into a binary tree
	prettyPrint(root2, 0);
	_getch();
	return 0;
}