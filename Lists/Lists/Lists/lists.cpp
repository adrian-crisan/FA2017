#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"

//i did not manage to create any correct graphics
//but the merge for a small input works
using namespace std;

Profiler profiler("demo");

typedef struct node {
	int key;
	struct node* next;
}Node;

typedef struct {
	node *first, *last;
	int no;
}List;

typedef struct {
	int key, l;
}Heap;

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

void heapify(Heap h[], int n, int i, int no) {
	int l, r, m;
	Heap aux;
	l = 2 * i + 1;
	r = 2 * i + 2;
	m = i;
	if (l < n && h[l].key < h[m].key) {
		m = l;
	}
	if (r < n && h[r].key < h[m].key) {
		m = r;
	}
	if (m != i) {
		aux = h[i];
		h[i] = h[m];
		h[m] = aux;
		heapify(h, n, m, no);
	}
}

void buildHeap(Heap h[], int n, int no) {
	for (int i = (n / 2) - 1; i >= 0; i--) {
		heapify(h, n, i, no);
	}
}

void merge(List l[], Heap h[], int n, int no) {
	int res[10000];
	int t = 0;
	for (int i = 0; i < n; i++) {
		profiler.countOperation("k=5", no, 2);
		h[i].key = l[i].first->key;
		h[i].l = i;
	}
	buildHeap(h, n, no);
	profiler.countOperation("k=5", no, 1);
	res[t++] = h[0].key;
	while (n) {
		l[h[0].l].first = l[h[0].l].first->next;
		profiler.countOperation("k=5", no, 2);
		if (l[h[0].l].first == NULL) {
			profiler.countOperation("k=5", no, n - 1);
			for (int i = 0; i < n - 1; i++) {
				h[i] = h[i + 1];
			}
			n--;
		}
		else {
			profiler.countOperation("k=5", no, 1);
			h[0].key = l[h[0].l].first->key;
		}
		buildHeap(h, n, no);
		profiler.countOperation("k=5", no, 1);
		res[t++] = h[0].key;
	}
	t--;
}

void merge10(List l[], Heap h[], int n, int no) {
	int res[10000];
	int t = 0;
	for (int i = 0; i < n; i++) {
		profiler.countOperation("k=10", no, 2);
		h[i].key = l[i].first->key;
		h[i].l = i;
	}
	buildHeap(h, n, no);
	profiler.countOperation("k=10", no, 1);
	res[t++] = h[0].key;
	while (n) {
		l[h[0].l].first = l[h[0].l].first->next;
		profiler.countOperation("k=10", no, 2);
		if (l[h[0].l].first == NULL) {
			profiler.countOperation("k=10", no, n - 1);
			for (int i = 0; i < n - 1; i++) {
				h[i] = h[i + 1];
			}
			n--;
		}
		else {
			profiler.countOperation("k=10", no, 1);
			h[0].key = l[h[0].l].first->key;
		}
		buildHeap(h, n, no);
		profiler.countOperation("k=10", no, 2);
		res[t++] = h[0].key;
	}
	t--;

}
void merge100(List l[], Heap h[], int n, int no) {
	int res[10000];
	int t = 0;
	for (int i = 0; i < n; i++) {
		profiler.countOperation("k=100", no, 2);
		h[i].key = l[i].first->key;
		h[i].l = i;
	}
	buildHeap(h, n, no);
	profiler.countOperation("k=100", no, 1);
	res[t++] = h[0].key;
	while (n) {
		l[h[0].l].first = l[h[0].l].first->next;
		profiler.countOperation("k=100", no, 1);
		if (l[h[0].l].first == NULL) {
			profiler.countOperation("k=100", no, n - 1);
			for (int i = 0; i < n - 1; i++) {
				h[i] = h[i + 1];
			}
			n--;
		}
		else {
			profiler.countOperation("k=100", no, 1);
			h[0].key = l[h[0].l].first->key;
		}
		buildHeap(h, n, no);
		profiler.countOperation("k=100", no, 2);
		res[t++] = h[0].key;
	}
	t--;
}

int main() {
	//test for 4 lists
	int a[20], b[20], c[20], d[20];
	int n = 20;
	int k = 4;
	Heap h[50];
	List l[20];
	Node *p;
	createList(l, k);
	FillRandomArray(a, n / k, 10, 1000, true, 2);
	FillRandomArray(b, n / k, 10, 1000, true, 2);
	FillRandomArray(c, n / k, 10, 1000, true, 2);
	FillRandomArray(d, n / k, 10, 1000, true, 2);
	for (int j = 0; j < n / k; j++) {
		p = createNode(a[j]);
		addNode(l, 0, p);
	}
	for (int j = 0; j < n / k; j++) {
		p = createNode(b[j]);
		addNode(l, 1, p);
	}
	for (int j = 0; j < n / k; j++) {
		p = createNode(c[j]);
		addNode(l, 2, p);
	}
	for (int j = 0; j < n / k; j++) {
		p = createNode(d[j]);
		addNode(l, 3, p);
	}
	for (int i = 0; i < k; i++) {
		printf("List %d: ", i);
		printList(l, i);
		printf("\n");
	}
	int res[50];
	int t = 0;
	for (int i = 0; i < k; i++) {
		h[i].key = l[i].first->key;
		h[i].l = i;
	}
	buildHeap(h, k, 0);
	res[t++] = h[0].key;
	while (k) {
		l[h[0].l].first = l[h[0].l].first->next;
		if (l[h[0].l].first == NULL) {
			for (int i = 0; i < k - 1; i++) {
				h[i] = h[i + 1];
			}
			k--;
		}
		else {
			h[0].key = l[h[0].l].first->key;
		}
		buildHeap(h, k, 0);
		res[t++] = h[0].key;
	}
	t--;
	printf("Merge: ");
	for (int i = 0; i < t; i++) {
		printf("%d ", res[i]);
	}
	//graphic for k=5, k=10, k=100
	/*int k1 = 5;
	for (int n1 = 100; n1 <= 10000; n1 += 100) {
		int a1[10000];
		List l1[1000];
		Heap h1[1000];
		Node *p1;
		createList(l1, k1);
		for (int i = 0; i < n1 / k1; i++) {
			FillRandomArray(a1, n1 / k1, 10, 10000, true, 2);
			for (int j = 0; j < n1 / k1; j++) {
				p1 = createNode(a1[i]);
				addNode(l1, j, p1);
			}
		}
		merge(l1, h1, k1, n1);
	}
	int k2 = 10;
	for (int n2 = 100; n2 <= 10000; n2 += 100) {
		int a2[10000];
		List l2[1000];
		Heap h2[1000];
		Node *p2;
		createList(l2, k2);
		for (int i = 0; i < n2 / k2; i++) {
			FillRandomArray(a2, n2 / k2, 10, 10000, true, 2);
			for (int j = 0; j < n2 / k2; j++) {
				p2 = createNode(a2[i]);
				addNode(l2, j, p2);
			}
		}
		merge10(l2, h2, k2, n2);
	}
	int k3 = 100;
	for (int n3 = 100; n3 <= 10000; n3 += 100) {
		int a3[10000];
		List l3[10000];
		Heap h3[10000];
		Node *p3;
		createList(l3, k3);
		for (int i = 0; i < n3 / k3; i++) {
			FillRandomArray(a3, n3 / k3, 10, 10000, true, 2);
			for (int j = 0; j < n3 / k3; j++) {
				p3 = createNode(a3[i]);
				addNode(l3, j, p3);
			}
		}
		merge100(l3, h3, k3, n3);
	}*/
	//profiler.createGroup("merge", "k=5", "k=10");
	//profiler.showReport();
	getchar();
	return 0;
}
