#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


typedef struct node {
	int key;
	struct node* next;
}Node;

typedef struct {
	node *first, *last;
	int no;
}List;

void createList(List l[], int k) {
	for (int i = 0; i < k; i++) {
		l[i].first = l[i].last = NULL;
		l[i].no = 0;
	}
}

Node *createNode(int key) {
	Node *node;
	node = (Node*)malloc(sizeof(Node));
	if (node != NULL) {
		node->key = key;
		node->next = NULL;
	}
	return node;
}

void addNode(List l[], int i, Node *node) {
	if (l[i].first == NULL) {
		l[i].first = l[i].last = node;
	}
	else {
		node->next = l[i].first;
		l[i].first = node;
	}
	l[i].no++;
}

void printList(List l[], int i) {
	if (l[i].first == NULL) {
		printf("Empty list.");
	}
	else {
		Node *p;
		for (p = l[i].first; p != NULL; p = p->next) {
			printf("%d ", p->key);
		}
	}
}

List MergeLists(List list1, List list2) {
	if (list1.first == NULL) return list2;
	if (list2.first == NULL) return list1;

	if (list1.first->key < list2.first->key) {
		list1.first->next = MergeLists(list1.first->next, list2);
		return list1;
	}
	else {
		list2.next = MergeLists(list2.next, list1);
		return list2;
	}
}