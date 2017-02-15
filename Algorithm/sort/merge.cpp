#include <stdio.h>
#include "util.h"

static void mergeArray(int a[], int first, int mid, int last, int tmp[])
{
	int i = first, j = mid + 1;
	int m = mid, n = last;
	int k = 0;

	while (i <= m && j <= n) {
		if (a[i] < a[j]) {
			tmp[k++] = a[i++];
		} else {
			tmp[k++] = a[j++];
		}
	}
	while (i <= m) {
		tmp[k++] = a[i++];
	}
	while (j <= n) {
		tmp[k++] = a[j++];
	}

	for (i = 0; i < k; i++) {
		a[first + i] = tmp[i];
	}
}

static void mergeSort(int a[], int first, int last, int tmp[])
{
	if (first < last) {
		int mid = (first + last) / 2;
		mergeSort(a, first, mid, tmp); // 左边有序
		mergeSort(a, mid + 1, last, tmp); // 右边有序
		mergeArray(a, first, mid, last, tmp); // 再将两个有序数组合并
	}
}

void mergeTest(int a[], int n)
{
	int* b = new int[n];
	copyArray(a, n, b);

	int* tmp = new int[n];
	mergeSort(b, 0, n - 1, tmp);
	delete[] tmp;
	printf("归并排序：	");
	printArray(b, n);

	delete[] b;
}
