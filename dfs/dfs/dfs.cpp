#include <iostream>
#include <stdio.h>
#include <stdlib.h>

enum { WHITE, GRAY, BLACK };
int time;

struct node {
	int key;
	int d;
	int f;
	node* next;
};

struct adjList {
	node *head;
};

struct graph {
	int v;
	adjList* arr;
};

struct list {
	int data;
	list* next;
};

list* listHead = NULL;

void insert(list** listHead, int data) {
	list* p = (list*)malloc(sizeof(list));
	p->data = data;
	p->next = (*listHead);
	(*listHead) = p;
}

void printList(list* node) {
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
}

graph* createGraph(int v) {
	graph* g = (graph*)malloc(sizeof(graph));
	g->v = v;
	g->arr = (adjList*)malloc(v * sizeof(adjList));
	int i;
	for (i = 0; i < v; i++) {
		g->arr[i].head = NULL;
	}
	return g;
}

void printGraph(graph* g) {
	int v;
	for (v = 0; v < g->v; ++v) {
		node* x = g->arr[v].head;
		printf("\nAdjacency list of vertex %d\n head ", v);
		while (x) {
			printf("-> %d", x->key);
			x = x->next;
		}
		printf("\n");
	}
}

node* createNode(int key) {
	node* p = (node*)malloc(sizeof(node));
	p->key = key;
	p->d = 0;
	p->f = 0;
	p->next = NULL;
	return p;
}

void addEdge(graph* g, int src, int dest) {
	node* newNode = createNode(dest);
	newNode->next = g->arr[src].head;
	g->arr[src].head = newNode;
}

void DFSVisit(graph* g, node* u, int mark[]) {
	node *p;
	time = time + 1;
	u->d = time;
	mark[u->key] = GRAY;
	printf("%d ", u->key);
	for (p = g->arr[u->key].head; p != NULL; p = p->next) {
		if (mark[p->key] == WHITE) {
			DFSVisit(g, p, mark);
		}
	}
	insert(&listHead, u->key);
	mark[u->key] = BLACK;
	time = time + 1;
	u->f = time;
}

void DFS(int n, int srcNode, graph* g, int nodes[]) {
	int mark[20];
	int i = 0;
	for (int i = 0; i < n; i++) {
		mark[i] = WHITE;
	}
	mark[srcNode] = GRAY;
	printf("%d ", srcNode);
	time = 0;
	for (i = 0; i < n; i++) {
		node *p = createNode(i);
		if (mark[i] == WHITE) {
			DFSVisit(g, p, mark);
		}
	}
}


int main() {
	int n = 9;
	int srcNode = 0;
	int nodes[] = { 0,1,2,3,4,5,6,7,8 };
	graph* g = createGraph(n);

	addEdge(g, 0, 4);
	addEdge(g, 0, 1);
	addEdge(g, 0, 3);
	addEdge(g, 1, 2);
	addEdge(g, 1, 4);
	addEdge(g, 2, 5);
	addEdge(g, 3, 4);
	addEdge(g, 3, 6);
	addEdge(g, 4, 5);
	addEdge(g, 4, 7);
	addEdge(g, 6, 4);
	addEdge(g, 6, 7);
	addEdge(g, 7, 5);
	addEdge(g, 7, 8);

	printGraph(g);
	DFS(n, srcNode, g, nodes);
	printf("\n"); 
	printf("Topological sort: ");
	list* p = (list*)malloc(sizeof(list*));
	list* last = listHead;
	p->data = srcNode;
	p->next = NULL;
	while (last->next != NULL) {
		last = last->next;
	}
	last->next = p;
	printList(listHead);
	printf("\n");
	getchar();
	return 0;
}