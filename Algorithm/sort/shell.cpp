#include <stdio.h>
#include "util.h"

static void shellSort1(int a[], int n)
{
	int i, j, k;
	int gap;

	for (gap = n / 2; gap > 0; gap /= 2 ) {
		for (i = 0; i < gap; i++) {
			// 直接插入排序
			for (j = i + gap; j < n; j += gap) {
				if (a[j] < a[j - gap]) {
					int tmp = a[j];
					for (k = j - gap; k >= 0 && a[k] > tmp; k -= gap) {
						a[k + gap] = a[k];
					}
					a[k + gap] = tmp;
				}
			}
		}
	}
}

static void shellSort2(int a[], int n)
{
	int i, j;
	int gap;

	for (gap = n / 2; gap > 0; gap /= 2) {
		for (i = gap; i < n; i++) {
			if (a[i] < a[i - gap]) {
				int tmp = a[i];
				for (j = i - gap; j >= 0 && a[j] > tmp; j -= gap) {
					a[j + gap] = a[j];
				}
				a[j + gap] = tmp;
			}
		}
	}
}

static void shellSort3(int a[], int n)
{
	int i, j;
	int gap;

	for (gap = n / 2; gap > 0; gap /= 2) {
		for (i = gap; i < n; i++) {
			for (j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap) {
				swap(a[j], a[j + gap]);
			}
		}
	}
}

void shellTest(int a[], int n)
{
	int* b = new int[n];
	copyArray(a, n, b);

	/*shellSort1(b, n);
	printf("希尔排序1：	");
	printArray(b, n);*/

	/*shellSort2(b, n);
	printf("希尔排序2：	");
	printArray(b, n);*/

	shellSort3(b, n);
	printf("希尔排序3：	");
	printArray(b, n);

	delete[] b;
}
