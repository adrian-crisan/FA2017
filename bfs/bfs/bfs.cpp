#include <iostream>
#include <stdio.h>
#include <stdlib.h>

enum { WHITE, GRAY, BLACK };

struct node {
	int key;
	node* next;
};

struct queue {
	int count;
	node* first;
	node* last;
};

struct adjList {
	node *head;
};

struct graph {
	int v;
	adjList* arr;
};

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
	p->next = NULL;
	return p;
}

void addEdge(graph* g, int src, int dest) {
	node* newNode = createNode(dest);
	newNode->next = g->arr[src].head;
	g->arr[src].head = newNode;
}

queue* createEmptyQueue() {
	queue* p = (queue*)malloc(sizeof(queue));
	p->first = NULL;
	p->last = NULL;
	p->count = 0;
	return p;
}

void enqueue(queue* q, int key) {
	node* p = createNode(key);
	if (q->count == 0) {
		q->first = q->last = p;
		q->count++;
	}
	else {
		p->next = q->last;
		q->last = p;
		q->count++;
	}
}

int dequeue(queue* q) {
	if (q->count >= 1) {
		if (q->count == 1) {
			node* p;
			p = q->first;
			q->first = q->last = NULL;
			q->count = 0;
			return p->key;
		}
		else {
			node* p;
			node* p1;
			p1 = NULL;
			p = q->last;
			while (p->next != NULL) {
				p1 = p;
				p = p->next;
			}
			q->first = p1;
			p1->next = NULL;
			q->count--;
			return p->key;
		}
	}
}

void BFS(int n, int srcNode, graph* g) {
	int mark[20];
	int w;
	queue* q = createEmptyQueue();
	for (int i = 0; i < n; i++) {
		mark[i] = WHITE;
	}
	node* p;
	mark[srcNode] = GRAY;
	printf("%d ", srcNode);
	enqueue(q, srcNode);
	while (q->count != 0) {
		int v = dequeue(q);
		for (p = g->arr[v].head; p != NULL; p = p->next) {
			w = p->key;
			if (mark[w] == WHITE) {
				mark[w] = GRAY;
				printf("%d ", w);
				enqueue(q, w);
			}
		}
		mark[v] = BLACK;
	}
}

int main() {
	int n = 9;
	int srcNode = 0;

	graph* g = createGraph(n);
	addEdge(g, 0, 1);                
	addEdge(g, 0, 3);
	addEdge(g, 0, 4);
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
	BFS(n, srcNode, g);
	

	getchar();
	return 0;
}
