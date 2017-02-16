#include <stdio.h>
#include "util.h"

static int adjustArray(int a[], int l, int r)
{
	int i = l, j = r;
	int x = a[i]; // a[i]就是第一个坑

	while (i < j) {
		// 从右向左找小于x的数来填a[i]
		while (i < j && a[j] > x) {
			j--;
		}
		if (i < j) {
			// 将a[j]填到a[i]中，a[j]就形成了一个新的坑
			a[i] = a[j];
			i++;
		}

		// 从左向右找大于x的数来填a[j]
		while (i < j && a[i] < x) {
			i++;
		}
		if (i < j) {
			// 将a[i]填到a[j]中，a[i]就形成了一个新的坑
			a[j] = a[i];
			j--;
		}
	}
	// 退出时，i等于j。将x填到这个坑中
	a[i] = x;

	return i;
}

static void quickSort(int a[], int l, int r)
{
	if (l < r) {
		int p = adjustArray(a, l, r);
		quickSort(a, l, p - 1);
		quickSort(a, p + 1, r);
	}
}

void quickTest(int a[], int n)
{
	int* b = new int[n];
	copyArray(a, n, b);

	quickSort(b, 0, n - 1);
	printf("快速排序：	");
	printArray(b, n);

	delete[] b;
}
