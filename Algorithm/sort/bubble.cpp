#include <stdio.h>
#include "util.h"

static void bubbleSort1(int a[], int n)
{
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 1; j < n - i; j++) {
			if (a[j -1] > a[j]) {
				swap(a[j - 1], a[j]);
			}
		}
	}
}

static void bubbleSort2(int a[], int n)
{
	int i, j;
	bool flag;

	j = n;
	flag = true;
	while (flag) {
		flag = false;
		for (i = 1; i < j; i++) {
			if (a[i -1] > a[i]) {
				swap(a[i - 1], a[i]);
				flag = true;
			}
		}
		j--;
	}
}

static void bubbleSort3(int a[], int n)
{
	int i, j;
	int flag;

	flag = n;
	while (flag > 0) {
		j = flag;
		flag = 0;
		for (i = 1; i < j; i++){
			if (a[i - 1] > a[i]) {
				swap(a[i - 1], a[i]);
				flag = i;
			}
		}
	}
}

void bubbleTest(int a[], int n)
{
	int *b = new int[n];
	copyArray(a, n, b);

	/*bubbleSort1(b, n);
	printf("冒泡排序：	");
	printArray(b, n);*/

	/*bubbleSort2(b, n);
	printf("冒泡排序改进1：	");
	printArray(b, n);*/

	bubbleSort3(b, n);
	printf("冒泡排序改进2：	");
	printArray(b, n);

	delete[] b;
}
