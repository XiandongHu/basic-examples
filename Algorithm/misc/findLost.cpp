#include <stdio.h>
#include "util.h"

/**
 * 给定一个无序的整数数组，怎么找到第一个大于0，并且不在此数组的整数。
 * 比如[1,2,0]返回3，[3,4,-1,1]返回2，[1, 5, 3, 4, 2]返回6，[100, 3, 2, 1, 6, 8, 5]返回4。
 * 要求使用O(1)空间和O(n)时间。
 */

static int findLostNumber(int a[], int n)
{
	int i;
	for (i = 0; i < n; i++) {
		while (a[i] > 0 && a[i] <= n && a[i] != i + 1 && a[i] != a[a[i] - 1]) {
			swap(a[i], a[a[i] - 1]);
		}
	}
	for (i = 0; i < n; i++) {
		if (a[i] != i + 1) {
			break;
		}
	}
	
	return i + 1;
}

void findLostTest()
{
	const int MAX = 6;
	int a[MAX] = {0, 1, -100, 3, 2, 5};
	printf("输入数据位：	");
	printArray(a, MAX);

	int number = findLostNumber(a, MAX);
	printf("缺失的第一个数为：%d\n", number);
}
