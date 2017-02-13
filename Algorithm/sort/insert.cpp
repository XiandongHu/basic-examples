#include <stdio.h>
#include "util.h"

static void insertSort1(int a[], int n)
{
	int i, j, k;

	for (i = 1; i < n; i++) {
		// 为a[i]在前面的a[0...i-1]有序区间内找一个合适的位置
		for (j = i - 1; j >= 0; j--) {
			if (a[j] < a[i]) {
				break;
			}
		}

		// 如果找到了一个合适的位置
		if (j != i - 1) {
			// 将比a[i]大的数向后移
			int tmp = a[i];
			for (k = i - 1; k >= j + 1; k--) {
				a[k + 1] = a[k];
			}
			// 将a[i]放到正确的位置
			a[k + 1] = tmp;
		}
	}
}

static void insertSort2(int a[], int n)
{
	int i, j;

	for (i = 1; i < n; i++) {
		if (a[i] < a[i - 1]) {
			int tmp = a[i];
			for (j = i - 1; j >= 0 && a[j] > tmp; j--) {
				a[j + 1] = a[j];
			}
			a[j + 1] = tmp;
		}
	}
}

static void insertSort3(int a[], int n)
{
	int i, j;

	for (i = 1; i < n; i++) {
		for (j = i - 1; j >= 0 && a[j] > a[j + 1]; j--) {
			swap(a[j], a[j + 1]);
		}
	}
}

void insertTest(int a[], int n)
{
	int* b = new int[n];
	copyArray(a, n, b);

	/*insertSort1(b, n);
	printf("直接插入排序1：	");
	printArray(b, n);*/

	/*insertSort2(b, n);
	printf("直接插入排序2：	");
	printArray(b, n);*/

	insertSort3(b, n);
	printf("直接插入排序3：	");
	printArray(b, n);

	delete[] b;
}
