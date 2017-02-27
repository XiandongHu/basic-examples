#include <stdio.h>
#include "util.h"

/**
 * 一个大小为n的数组，里面的数都属于范围[0, n-1]，有不确定的重复元素，找到至少一个重复元素，
 * 要求O(1)空间和O(n)时间。
 */

static int findRepeatNumber(int a[], int n)
{
	/**
	 * 虽然有二重循环，但每个元素只会被访问一次
	 */
	for (int i = 0; i < n; i++) {
		while (i != a[i]) {
			if (a[i] == a[a[i]]) {
				return a[i];
			}
			swap(a[i], a[a[i]]);
		}
	}

	return -1;
}

void findRepeatTest()
{
	const int MAX = 10;
	int a[MAX] = {0, 4, 2, 5, 5, 6, 4, 0, 9, 2};
	printf("输入数组为：	");
	printArray(a, MAX);

	int number = findRepeatNumber(a, MAX);
	if (number != -1) {
		printf("找到重复元素：%d\n", number);
	} else {
		printf("没有找到重复元素\n");
	}
}
