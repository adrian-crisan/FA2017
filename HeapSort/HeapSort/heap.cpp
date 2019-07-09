#include <iostream>
#include <stdio.h>
#include "Profiler.h"

using namespace std;
Profiler profiler("demo");

void heapIncreaseKey(int arr[], int i, int key, int arraySize) {
	int aux;
	if (key >= arr[i]) {
		arr[i] = key;
		while (i > 1 && arr[i / 2] < arr[i]) {
			aux = arr[i];
			arr[i] = arr[i / 2];
			arr[i / 2] = aux;
			i = i / 2;
		}
	}
}

void maxHeapInsert(int arr[], int key, int h, int arraySize) {
	arr[h] = -INT_MAX;
	heapIncreaseKey(arr, h, key, arraySize);
}

void buildMaxHeap(int arr[], int n, int arraySize) {
	int h = 1;
	for (int i = 2; i <= n; i++) {
		maxHeapInsert(arr, arr[i], ++h, arraySize);
	}
}

void heapify(int arr[], int arraySize, int heapSize, int i) {
	
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int aux;
	//profiler.countOperation("HSBUAC", heapSize, 5);
	if (l < arraySize && arr[l] > arr[i]) {
		largest = l;
	}
	if (r < arraySize && arr[r] > arr[largest]) {
		largest = r;
	}
	if (largest != i) {
		aux = arr[i];
		arr[i] = arr[largest];
		arr[largest] = aux;
		//profiler.countOperation("HSBUAA", heapSize, 3);
		heapify(arr, arraySize, heapSize, largest);
	}
}

void heapifyTD(int arr[], int arraySize, int heapSize, int i) {

	int largest = i;
	int l = 2 * i;
	int r = 2 * i + 1;
	int aux;
	profiler.countOperation("HSTDAC", arraySize, 5);
	if (l <= heapSize && arr[l] > arr[i]) {
		largest = l;
	}
	if (r <= heapSize && arr[r] > arr[largest]) {
		largest = r;
	}
	if (largest != i) {
		aux = arr[i];
		arr[i] = arr[largest];
		arr[largest] = aux;
		profiler.countOperation("HSTDAA", arraySize, 3);
		heapifyTD(arr, arraySize, heapSize, largest);
	}
}

void heapifyW(int arr[], int arraySize, int heapSize, int i) {

	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int aux;
	profiler.countOperation("HSBUWC", heapSize, 5);
	if (l < arraySize && arr[l] > arr[i]) {
		largest = l;
	}
	if (r < arraySize && arr[r] > arr[largest]) {
		largest = r;
	}
	if (largest != i) {
		aux = arr[i];
		arr[i] = arr[largest];
		arr[largest] = aux;
		profiler.countOperation("HSBUWA", heapSize, 3);
		heapifyW(arr, arraySize, heapSize, largest);
	}
}

void heapifyTDW(int arr[], int arraySize, int heapSize, int i) {

	int largest = i;
	int l = 2 * i;
	int r = 2 * i + 1;
	int aux;
	profiler.countOperation("HSTDWC", arraySize, 5);
	if (l <= heapSize && arr[l] > arr[i]) {
		largest = l;
	}
	if (r <= heapSize && arr[r] > arr[largest]) {
		largest = r;
	}
	if (largest != i) {
		aux = arr[i];
		arr[i] = arr[largest];
		arr[largest] = aux;
		profiler.countOperation("HSTDWA", arraySize, 3);
		heapifyTDW(arr, arraySize, heapSize, largest);
	}
}

void heapsortBU(int arr[], int n) {
	int aux;
	int arraySize = n;
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(arr, n, n, i);
	}
	for (int i = n - 1; i >= 0; i--) {
		aux = arr[0];
		arr[0] = arr[i];
		arr[i] = aux;
		heapify(arr, i, arraySize, 0);
	}
}

void heapsortTD(int arr[], int n) {
	int aux;
	buildMaxHeap(arr, n, n);
	int heapSize = n;
	for (int i = n; i > 0; i--) {
		aux = arr[1];
		arr[1] = arr[i];
		arr[i] = aux;
		heapSize--;
		heapifyTD(arr, n, heapSize, 1);
	}
}

void heapsortBUW(int arr[], int n) {
	int aux;
	int arraySize = n;
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapifyW(arr, n, n, i);
	}
	for (int i = n - 1; i >= 0; i--) {
		aux = arr[0];
		arr[0] = arr[i];
		arr[i] = aux;
		heapifyW(arr, i, arraySize, 0);
	}
}

void heapsortTDW(int arr[], int n) {
	int aux;
	buildMaxHeap(arr, n, n);
	int heapSize = n;
	for (int i = n; i > 0; i--) {
		aux = arr[1];
		arr[1] = arr[i];
		arr[i] = aux;
		heapSize--;
		heapifyTDW(arr, n, heapSize, 1);
	}
}


int main() {
	int n;
	/*int arr[10000];
	for (int n = 100; n < 10000; n += 100) {
		for (int c = 1; c <= 5; c++) {
			FillRandomArray(arr, n);
			heapsortBU(arr, n);
		}
	}
	for (int n = 100; n < 10000; n += 100) {
		for (int c = 1; c <= 5; c++) {
			FillRandomArray(arr, n);
			heapsortTD(arr, n);
		}
	}
	for (int n = 100; n < 10000; n += 100) {
		FillRandomArray(arr, n, 10, 50000, false, 1);
		heapsortBUW(arr, n);
	}
	for (int n = 100; n < 10000; n += 100) {
		FillRandomArray(arr, n, 10, 50000, false, 1);
		heapsortTDW(arr, n);
	}
	profiler.createGroup("HSBUA", "HSBUAC", "HSBUAA");
	profiler.createGroup("HSTDA", "HSTDAC", "HSTDAA");
	profiler.createGroup("HSBUW", "HSBUWC", "HSBUWA");
	profiler.createGroup("HSTDW", "HSTDWC", "HSTDWA");
	profiler.createGroup("HS comp", "HSBUAC", "HSTDAC");
	profiler.showReport();*/
	int a[6] = { 0,4,-2,7,3,9 };
	int b[7] = { 0,0,4,-2,7,3,9 };
	heapsortBU(a, 6);
	heapsortTD(b, 6);
	for (int i = 0; i < 6; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	for (int i = 1; i < 7; i++) {
		printf("%d ", b[i]);
	}
	getchar();
}