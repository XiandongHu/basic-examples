#include <stdio.h>
#include "util.h"

/**
 * i节点的父节点为 (i - 1) / 2
 */
static void maxHeapFixup(int a[], int i)
{
	int j, tmp;

	tmp = a[i];
	j = (i - 1) / 2; // 父节点
	while (j >= 0 && i != 0) {
		if (a[j] >= tmp) {
			break;
		}

		// 把较小的父节点往下移动，替换它的子节点
		a[i] = a[j];
		i = j;
		j = (i - 1) / 2;
	}
	a[i] = tmp;
}

/**
 * i节点的子节点为 2 * i + 1和2 * i + 2
 */
static void maxHeapFixdown(int a[], int i, int n)
{
	int j, tmp;

	tmp = a[i];
	j = 2 * i + 1; // 子节点1
	while (j < n) {
		// 在左右孩子中找最大的
		if (j + 1 < n && a[j + 1] > a[j]) {
			j++;
		}

		if (a[j] <= tmp) {
			break;
		}

		// 把较大的子节点往上移动，替换它的父节点
		a[i] = a[j];
		i = j;
		j = 2 * i + 1;
	}
	a[i] = tmp;
}

static void heapSort1(int a[], int n)
{
	int i;

	// 逐个从数组中取出数据建立堆
	for (i = 0; i < n; i++) {
		maxHeapFixup(a, i);
	}
	for (i = n - 1; i > 0; i--) {
		swap(a[i], a[0]);
		maxHeapFixdown(a, 0, i);
	}
}

static void heapSort2(int a[], int n)
{
	int i;

	// 只需将a[(n-1)/2 ... 0]分别做一次向下调整操作即可
	for (i = (n - 1) / 2; i >= 0; i--) {
		maxHeapFixdown(a, i, n);
	}
	for (i = n - 1; i > 0; i--) {
		swap(a[i], a[0]);
		maxHeapFixdown(a, 0, i);
	}
}

void heapTest(int a[], int n)
{
	int* b = new int[n];
	copyArray(a, n, b);

	/*heapSort1(b, n);
	printf("堆排序1：	");
	printArray(b, n);*/

	heapSort2(b, n);
	printf("堆排序2：	");
	printArray(b, n);

	delete[] b;
}
