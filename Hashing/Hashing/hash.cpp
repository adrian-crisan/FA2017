#include <iostream>
#include <stdio.h>
#include "Profiler.h"

//hash table


/*
quadratic hash function for probing
consider the auxiliary hash function to  be h'(k) =  k
returns the position on finding empty slot
returns -1 if slot is already taken
*/
int hashFunction(int k, int i, int tableSize) {
	return (int)(k % tableSize + i + 3 * pow(i, 2)) % tableSize;
}

//hash insertion
void hashInsert(int a[], int k, int tableSize) {
	int i = 0;
	while (i < tableSize) {
		int j = hashFunction(k, i, tableSize);
		if (a[j] == 0) {
			a[j] = k;
			break;
		}
		else
			i++;
	}
	if (i == tableSize)
		printf("I did not put: %d", k);
}

//hash searching
int hashSearch(int a[], int k, int tableSize) {
	static int z;
	int i = 0;
	int j = hashFunction(k, i, tableSize);
	while ((i < tableSize) && (a[j] != 0)) {
		if (a[j] == k) {
			i++;
			return i;
		}
		i++;
		j = hashFunction(k, i, tableSize);
	}

	return i + 1;//means not found
}

void displayArray(int a[], int size) {
	printf("\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", a[i]);
	}
}

int main()
{
	int a[10];
	memset(a, 0, 10*sizeof(int));
	int b[5] = { 1, 2, 5, 8, 1000 };
	displayArray(a, 10);
	for (int i = 0; i < 5; i++) {
		printf("insert\n");
		hashInsert(a, b[i],10);
	}
	displayArray(a, 10);
	for (int i = 0; i < 5; i++) {
		int f = hashSearch(a, b[i], 10);
		if (a[f-1]!=0 )
			printf("ok\n");
		else
			printf("not ok\n");
	}

	/*char s = 'a';
	printf("e to exit\n");
	while (s != 'e') {

		int a[10007];
		int elements[10007];
		int elementsIn[1500];//elements in the table
		int elementsNotIn[1500];//elements not in the table
		int f;
		int alfa[5] = { 8000,8500,9000,9500,9900 };
		double totalEffortFound = 0;
		double maxEffortFound = 0;
		double totalEffortNotFound = 0;
		double maxEffortNotFound = 0;
		int i;

		printf("| Filling | AVG. Effort | Max. Effort | AVG. Effort | Max. Effort |");
		printf("\n| factor  |    found    |    found    |  not-found  |  not-found  |");
		printf("\n-------------------------------------------------------------------\n");
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				//repeat five times the inseration
				memset(a, 0, 10007 * sizeof(int));//initialize all the elements with 0
				FillRandomArray(elements, alfa[i], 1, 100500, true, 0);
				for (int k = 0; k < alfa[i]; k++) { //inserted the elements
					hashInsert(a, elements[k], 10007);
				}

				//generate elements to search for and find
				FillRandomArray(elementsIn, 1500, 0, alfa[i] - 1, true, 0);
				for (int k = 0; k < 1500; k++) {
				    f = hashSearch(a, elements[elementsIn[k]], 10007);
					if (a[hashFunction(elements[elementsIn[k]], f - 1, 10007)] == 0)
						printf("not found\n");
					totalEffortFound += f;
					if (f > maxEffortFound)
						maxEffortFound = f;

				}
				//generate elements to search for and not find
				FillRandomArray(elementsNotIn, 1500, 100501, 200000, true, 0);
				for (int k = 0; k < 1500; k++) 
				    f = hashSearch(a, elementsNotIn[k], 10007);
					totalEffortNotFound += f;
					if (f > maxEffortNotFound)
						maxEffortNotFound = f;

				}
			}
			//display the info
			printf("| %7.2f | %11.2f | %11.2f | %11.2f | %11.2f |", alfa[i] / 10007.0, totalEffortFound / 7500.0, maxEffortFound, totalEffortNotFound / 7500.0, maxEffortNotFound);
			printf("\n-------------------------------------------------------------------\n");
			totalEffortFound = 0;
			totalEffortNotFound = 0;
			maxEffortFound = 0;
			maxEffortNotFound = 0;
		}
		scanf_s("%c", &s);
	}*/
	getchar();
	return 0;
}