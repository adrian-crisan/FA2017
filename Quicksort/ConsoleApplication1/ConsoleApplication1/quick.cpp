#include <iostream>
#include <stdio.h>
#include "Profiler.h"

using namespace std;
Profiler profiler("demo");

int partition(int arr[], int p, int r, int n) {
	int x = arr[r];
	int i = (p - 1);
	int aux;
	int aux2;
	for (int j = p; j <= r - 1; j++) {
		profiler.countOperation("QSC", n, 1);
		if (arr[j] <= x) {
			i++;
			aux = arr[i];
			arr[i] = arr[j];
			arr[j] = aux;
		}
	}
	aux2 = arr[r];
	arr[r] = arr[i + 1];
	arr[i + 1] = aux2;
	profiler.countOperation("QSA", n, 6);
	return (i + 1);
}

void quickSort(int arr[], int p, int r, int n) {
	if (p < r) {
		int q = partition(arr, p, r, n);
		quickSort(arr, p, q - 1, n);
		quickSort(arr, q + 1, r, n);
	}
}

int partitionW(int arr[], int p, int r, int n) {
	int x = arr[r];
	int i = (p - 1);
	int aux;
	int aux2;
	for (int j = p; j <= r - 1; j++) {
		profiler.countOperation("QS Worst", n, 1);
		if (arr[j] <= x) {
			i++;
			aux = arr[i];
			arr[i] = arr[j];
			arr[j] = aux;
		}
	}
	aux2 = arr[r];
	arr[r] = arr[i + 1];
	arr[i + 1] = aux2;
	//profiler.countOperation("QSA", n, 6);
	return (i + 1);
}

void quickSortW(int arr[], int p, int r, int n) {
	if (p < r) {
		int q = partitionW(arr, p, r, n);
		quickSortW(arr, p, q - 1, n);
		quickSortW(arr, q + 1, r, n);
	}
}

int randomizedPartition(int arr[], int p, int r, int n) {
	int i = rand() % (r + -p) + p;
	int aux;
	aux = arr[r];
	arr[r] = arr[i];
	arr[i] = aux;
	return partition(arr, p, r, n);
}

int randomizedSelect(int arr[], int p, int r, int i, int n) {
	if (p == r) {
		return arr[p];
	}
	int q = randomizedPartition(arr, p, r, n);
	int k = q - p + 1;
	if (i == k) {
		return arr[q];
	}
	if (i < k) {
		return randomizedSelect(arr, p, q - 1, i, n);
	}
	else {
		return randomizedSelect(arr, q + 1, r, i - k, n);
	}
}

void heapify(int arr[], int arraySize, int heapSize, int i) {

	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int aux;
	profiler.countOperation("HSC", heapSize, 5);
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
		profiler.countOperation("HSA", heapSize, 3);
		heapify(arr, arraySize, heapSize, largest);
	}
}

void heapsort(int arr[], int n) {
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

int main() {
	int arr[] = { 0, 9, 8, 77, 99, 2, 1 };
	//quickSort(arr, 0, 6, 7);
	for (int i = 0; i < 7; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	for (int i = 1; i <= 7; i++) {
		int res = randomizedSelect(arr, 0, 6, i, 7);
		printf("%d ", res);
	}
	/*int b[10000];
	int n;
	for (int n = 100; n <= 10000; n += 100) {
		for (int j = 0; j < 5; j++) {
			FillRandomArray(b, n, 10, 50000, true);
			quickSort(b, 0, n - 1, n);
		}
	}
	for (int n = 100; n <= 10000; n += 100) {
		for (int j = 0; j < 5; j++) {
			FillRandomArray(b, n, 10, 50000, true);
			heapsort(b, n);
		}
	}
	for (int n = 100; n <= 10000; n += 100) {
		FillRandomArray(b, n, 10, 50000, true, 1);
		quickSortW(b, 0, n - 1, n);
	}
	profiler.createGroup("HS v QS C", "HSC", "QSC");
	profiler.createGroup("HS v QS A", "HSA", "QSA");
	profiler.showReport();*/
	getchar();
	return 0;
}