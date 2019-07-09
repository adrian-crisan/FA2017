// Sortings.cpp : Defines the entry point for the console application.
//

// We can observe that only for Insertion and Bubble Sort Best cases the graphic is linear, corresponding to O(n), 
//for the rest of the cases being O(n*n).

#include "stdafx.h"
#include "Profiler.h"
#include <iostream>
#include <stdio.h>

using namespace std;
Profiler profiler("demo");

void bubbleSort(int arr[], int n) {
	int aux;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			//profiler.countOperation("BSAC", n);
			if (arr[i] > arr[j]) {
				aux = arr[i];
				arr[i] = arr[j];
				arr[j] = aux;
				//profiler.countOperation("BSAA", n);
			}
		}
	}
}

void bubbleSortBest(int arr[], int n) {
	int aux;
	for (int i = 0; i < n; i++) {
		profiler.countOperation("BSBC", n);
		for (int j = i; j < n; j++) {
			if (arr[i] > arr[j]) {
				aux = arr[i];
				arr[i] = arr[j];
				arr[j] = aux;
				profiler.countOperation("BSBA", n);
			}
		}
	}
}

void bubbleSortWorst(int arr[], int n) {
	int aux;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			profiler.countOperation("BSWC", n);
			if (arr[i] > arr[j]) {
				aux = arr[i];
				arr[i] = arr[j];
				arr[j] = aux;
				profiler.countOperation("BSWA", n);
			}
		}
	}
}

void insertionSort(int arr[], int n) {
	int aux, k;
	for (int i = 2; i < n; i++) {
		aux = arr[i];
		k = i - 1;
		while (k >= 0 && aux < arr[k]) {
			//profiler.countOperation("ISAC", n, 2);
			arr[k + 1] = arr[k];
			k--;
			//profiler.countOperation("ISAA", n, 3);
		}
		arr[k + 1] = aux;
	}
}

void insertionSortBest(int arr[], int n) {
	int aux, k;
	for (int i = 2; i < n; i++) {
		aux = arr[i];
		k = i - 1;
		profiler.countOperation("ISBC", n, 2);
		while (k >= 0 && aux < arr[k]) {
			arr[k + 1] = arr[k];
			k--;
		}
		arr[k + 1] = aux;
		profiler.countOperation("ISBA", n, 3);
	}
}

void insertionSortWorst(int arr[], int n) {
	int aux, k;
	for (int i = 2; i < n; i++) {
		aux = arr[i];
		k = i - 1;
		while (k >= 0 && aux < arr[k]) {
			profiler.countOperation("ISWC", n, 2);
			arr[k + 1] = arr[k];
			k--;
			profiler.countOperation("ISWA", n, 3);
		}
		arr[k + 1] = aux;
	}
}

void selectionSort(int arr[], int n) {
	int aux, min;
	for (int i = 1; i < n; i++) {
		min = i;
		for (int j = i + 1; j <= n; j++) {
			//profiler.countOperation("SSAC", n);
			if (arr[j] < arr[min]) {
				min = j;
			}
			//profiler.countOperation("SSAA", n, 3);
		}
		if (i != min) {
			aux = arr[i];
			arr[i] = arr[min];
			arr[min] = aux;
		}
	}
}

void selectionSortBest(int arr[], int n) {
	int aux, min;
	for (int i = 1; i < n; i++) {
		min = i;
		for (int j = i + 1; j <= n; j++) {
			profiler.countOperation("SSBC", n);
			if (arr[j] < arr[min]) {
				min = j;
			}
			profiler.countOperation("SSBA", n, 3);
		}
		if (i != min) {
			aux = arr[i];
			arr[i] = arr[min];
			arr[min] = aux;
		}
	}
}

void selectionSortWorst(int arr[], int n) {
	int aux, min;
	for (int i = 1; i < n; i++) {
		min = i;
		for (int j = i + 1; j <= n; j++) {
			profiler.countOperation("SSWC", n);
			if (arr[j] < arr[min]) {
				min = j;
				profiler.countOperation("SSWA", n, 3);
			}
		}
		if (i != min) {
			aux = arr[i];
			arr[i] = arr[min];
			arr[min] = aux;
		}
	}
}

int main()
{
	int n;
	/*int arr[10000];
	for (int n = 100; n < 10000; n += 100) {
		for (int c = 1; c <= 5; c++) {
			FillRandomArray(arr, n);
			bubbleSort(arr, n);
		}
	}
	for (int n = 100; n < 10000; n += 100) {
		FillRandomArray(arr, n, 1, 500000, false, 1);
		int aux = arr[0];
		arr[0] = arr[1];
		arr[1] = aux;
		bubbleSortBest(arr, n);
	}
	for (int n = 100; n < 10000; n += 100) {
		FillRandomArray(arr, n , 1, 500000, false, 2);
		bubbleSortWorst(arr, n);
	}
	for (int n = 100; n < 10000;  n += 100) {
		for (int c = 1; c <= 5; c++) {
			FillRandomArray(arr, n);
			insertionSort(arr, n);
		}
	}
	for (int n = 100; n < 10000; n += 100) {
		FillRandomArray(arr, n, 1, 500000, false, 1);
		int aux = arr[0];
		arr[0] = arr[1];
		arr[1] = aux;
		insertionSortBest(arr, n);
	}
	for (int n = 100; n < 10000; n += 100) {
		FillRandomArray(arr, n, 1, 500000, false, 2);
		insertionSortWorst(arr, n);
	}
	for (int n = 100; n < 10000; n += 100) {
		for (int c = 1; c <= 5; c++) {
			FillRandomArray(arr, n);
			selectionSort(arr, n);
		}
	}
	for (int n = 100; n < 10000; n += 100) {
		FillRandomArray(arr, n, 1, 500000, false, 1);
		int aux = arr[0];
		arr[0] = arr[1];
		arr[1] = aux;
		selectionSortBest(arr, n);
	}
	for (int n = 100; n < 10000; n += 100) {
		FillRandomArray(arr, n, 1, 500000, false, 2);
		selectionSortWorst(arr, n);
	}
	profiler.createGroup("Average Case C", "BSAC", "ISAC", "SSAC");
	profiler.createGroup("Average Case A", "BSAA", "ISAA", "SSAA");
	profiler.addSeries("Avg Case BS A+C", "BSAC", "BSAA");
	profiler.addSeries("Best Case BS A+C", "BSBC", "BSBA");
	profiler.addSeries("Worst Case BS A+C", "BSWC", "BSWC");

	profiler.createGroup("Best Case C", "SSBC");
	profiler.createGroup("Best Case A", "SSBA");
	profiler.addSeries("Avg Case IS A+C", "ISAC", "ISAA");
	profiler.addSeries("Best Case IS A+C", "ISBC", "ISBA");
	profiler.addSeries("Worst Case IS A+C", "ISWC", "ISWC");

	profiler.createGroup("Worst Case C", "BSWC", "ISWC", "SSWC");
	profiler.createGroup("Worst Case A", "BSWA", "ISWA", "SSWA");
	profiler.addSeries("Avg Case SS A+C", "SSAC", "SSAA");
	profiler.addSeries("Best Case SS A+C", "SSBC", "SSBA");
	profiler.addSeries("Worst Case SS A+C", "SSWC", "SSWC");

	profiler.createGroup("A/B/W IS A+C", "Avg Case IS A+C", "Best Case IS A+C", "Worst Case IS A+C");
	profiler.createGroup("A/B/W BS A+C", "Avg Case BS A+C", "Best Case BS A+C", "Worst Case BS A+C");
	profiler.createGroup("A/B/W SS A+C", "Avg Case SS A+C", "Best Case SS A+C", "Worst Case SS A+C");


	profiler.showReport();*/

	int a[6] = { 2,1,7,4,-7,0 };
	int b[7] = { 0 ,2,1,7,4,-7,0 };
	int c[7] = { 0,2,1,7,4,-7,0 };
	bubbleSort(a, 6);
	insertionSort(b, 6);
	selectionSort(c, 6);
	for (int i = 0; i < 6; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	for (int i = 0; i < 6; i++) {
		printf("%d ", b[i]);
	}
	printf("\n"); 
	for (int i = 1; i < 7; i++) {
		printf("%d ", c[i]);
	}
	printf("\n");
	getchar();
	
    return 0;
}

