#include <stdio.h>
#include "util.h"

static void selectSort(int a[], int n)
{
	int i, j;
	int minIndex;

	for (i = 0; i < n; i++) {
		minIndex = i;
		for (j = i + 1; j < n; j++) {
			if (a[j] < a[minIndex]) {
				minIndex = j;
			}
		}
		swap(a[i], a[minIndex]);
	}
}

void selectTest(int a[], int n)
{
	int* b = new int[n];
	copyArray(a, n, b);

	selectSort(b, n);
	printf("直接选择排序：	");
	printArray(b, n);

	delete[] b;
}
