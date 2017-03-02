#include <stdio.h>
#include "util.h"

/**
 * 在一个排列中，如果一对数的前后位置与大小顺序相反，即前面的数大于后面的数，那么它们就称为一个逆序数对。
 * 一个排列中逆序的总数就称为这个排列的逆序数。如{2，4，3，1}中，2和1，4和3，4和1，3和1是逆序数对，因此整个数组的逆序数对个数为4。
 * 现在给定一数组，要求统计出该数组的逆序数对个数。
 */

/**
 * 最简单的方法就是从前向后依次统计每个数字与它后面的数字是否能组成逆序数对
 */
static int reverseSequence1(int a[], int n)
{
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (a[i] > a[j]) {
				count++;
			}
		}
	}

	return count;
}

/**
 * 采用归并排序的思想
 */
static void mergeArray(int a[], int first, int mid, int last, int tmp[], int& count)
{
	int i = first, j = mid + 1;
	int m = mid, n = last;
	int k = 0;

	while (i <= m && j <= n) {
		if (a[i] < a[j]) {
			tmp[k++] = a[i++];
		} else {
			tmp[k++] = a[j++];
			// a[j]和a[i...m]之间的每一个数都能组成逆序数对
			count += m - i + 1;
		}
	}
	if (i <= m) {
		tmp[k++] = a[i++];
	}
	if (j <= n) {
		tmp[k++] = a[j++];
	}

	for (i = 0; i < k; i++) {
		a[first + i] = tmp[i];
	}
}

static void mergeSort(int a[], int first, int last, int tmp[], int& count)
{
	if (first < last) {
		int mid = (first + last) / 2;
		mergeSort(a, first, mid, tmp, count);
		mergeSort(a, mid + 1, last, tmp, count);
		mergeArray(a, first, mid, last, tmp, count);
	}
}

static int reverseSequence2(int a[], int n)
{
	int* tmp = new int[n];
	int count = 0;
	mergeSort(a, 0, n - 1, tmp, count);
	return count;
}

void reverseSequenceTest()
{
	const int MAX = 10;
	int a[MAX] = {1, 3, 2, 7, 5, 8, 4, 9, 100, 21};
	printf("输入数据为：	");
	printArray(a, MAX);

	//int count = reverseSequence1(a, MAX);
	int count = reverseSequence2(a, MAX);
	printf("逆序数对为：%d\n", count);
}
