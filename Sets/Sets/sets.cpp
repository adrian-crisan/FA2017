#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

using namespace std;

Profiler profiler("Sets");

struct object {
	char key;
	int rank;
	int rankK;
	int parentK;
	object *parent;
};

struct Edge {
	int src;
	int dest;
	int weight;
};

struct Graph {
	int V;
	int E;
	Edge* edge;
};

Graph* createGraph(int V, int E) {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	graph->E = E;
	graph->edge = (Edge*)malloc(graph->E*sizeof(Edge));
	return graph;
}

int find(object array[], int i) {
	if (array[i].parentK != i) {
		array[i].parentK = find(array, array[i].parentK);
	}
	return array[i].parentK;
}

void unionSetK(object array[], int x, int y) {
	int xRoot = find(array, x);
	int yRoot = find(array, y);
	if (array[xRoot].rankK < array[yRoot].rankK) {
		array[xRoot].parentK = yRoot;
	}
	else if (array[xRoot].rankK > array[yRoot].rankK) {
			array[yRoot].parentK = xRoot;
		}
	else {
		array[yRoot].parentK = xRoot;
		array[xRoot].rankK++;
	}
}

int myComp(const void* a, const void* b)
{
	struct Edge* a1 = (struct Edge*)a;
	struct Edge* b1 = (struct Edge*)b;
	return a1->weight > b1->weight;
}

void Kruskal(Graph* graph) {
	int V = graph->V;
	Edge res[20];
	int e = 0;
	int i = 0;
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
	object *array = (object*)malloc(V * sizeof(object));
	for (int v = 0; v < V; ++v) {
		array[v].parentK = v;
		array[v].rank = 0;
	}
	while (e < V - 1) {
		Edge nextEdge = graph->edge[i++];
		int x = find(array, nextEdge.src);
		int y = find(array, nextEdge.dest);
		if (x != y) {
			res[e++] = nextEdge;
			unionSetK(array, x, y);
		}
	}
	printf("The edges of the MST are: \n");
	for (i = 0; i < e; ++i) {
		printf("%d -- %d = %d\n", res[i].src, res[i].dest, res[i].weight);
	}
	return;
}

/*void KruskalTest(Graph* graph) {
	int V = graph->V;
	Edge res[20];
	int e = 0;
	int i = 0;
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
	object *array = (object*)malloc(V * sizeof(object));
	for (int v = 0; v < V; ++v) {
		array[v].parentK = v;
		array[v].rank = 0;
	}
	while (e < V - 1) {
		Edge nextEdge = graph->edge[i++];
		int x = find(array, nextEdge.src);
		int y = find(array, nextEdge.dest);
		if (x != y) {
			res[e++] = nextEdge;
			unionSetK(array, x, y);
		}
	}
	printf("The edges of the MST are: \n");
	for (i = 0; i < e; ++i) {
		printf("%d -- %d = %d\n", res[i].src, res[i].dest, res[i].weight);
	}
	return;
}*/

object* makeSet(object* x, char key) {
	x = (object*)malloc(sizeof(object));
	x->parent = x;
	x->rank = 0;
	x->key = key;
	return x;
}

void link(object *x, object *y) {
	if (x->rank > y->rank) {
		y->parent = x;
	}
	else {
		x->parent = y;
		if (x->rank == y->rank) {
			y->rank = y->rank + 1;
		}
	}
}

object* findSet(object *x) {
	if (x != x->parent) {
		x->parent = findSet(x->parent);
	}
	return x->parent;
}

void unionSet(object *x, object *y) {
	link(findSet(x), findSet(y));
}

int main() {
	int n = 10;
	object *a[10];
	char key[10] = { 'a','b','c','d','e','f','g','h','i','j' };
	for (int i = 0; i < n; i++) {
		a[i] = makeSet(a[i], key[i]);
		printf("%c ", a[i]->parent->key);
	}
	printf("\n\n");

	object *x = findSet(a[4]);
	printf("The fifth key is: %c", x->key);
	printf("\n");

	unionSet(a[0], a[1]);
	unionSet(a[1], a[3]);
	unionSet(a[1], a[4]);
	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("%c ", a[i]->parent->key);
	}
	printf("\n\n");

	int V = 4;
	int E = 5;
	Graph* graph = createGraph(V, E);		//  0--- 5 --- 3
	graph->edge[0].src = 0;					//  | \      / |
	graph->edge[0].dest = 1;				//  10  6  15  4
	graph->edge[0].weight = 10;				//  |  /   \   |
											//  1          2
	graph->edge[1].src = 0;
	graph->edge[1].dest = 2;
	graph->edge[1].weight = 6;

	graph->edge[2].src = 0;
	graph->edge[2].dest = 3;
	graph->edge[2].weight = 5;


	graph->edge[3].src = 1;
	graph->edge[3].dest = 3;
	graph->edge[3].weight = 15;

	graph->edge[4].src = 2;
	graph->edge[4].dest = 3;
	graph->edge[4].weight = 4;

	Kruskal(graph);

	/*int weights[10000];
	for (int i = 100; i <= 10000; i += 100) {
		FillRandomArray(weights, i, 10, 5000);
		int nodes = i;
		int edges = i * 4;
		Graph* graphTest = createGraph(nodes, edges);
		for (int j = 0; j < edges; j++) {
			int rSrc = rand() % i;
			int rDest = rand() % i;
			if (rDest != rSrc) {
				graphTest->edge[j].src = rSrc;
				graphTest->edge[j].dest = rDest;
				graphTest->edge[j].weight = weights[j];
			}
		}
		KruskalTest(graphTest);
	}*/
	getchar();
	return 0;
}

