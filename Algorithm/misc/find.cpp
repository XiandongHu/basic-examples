#include <stdio.h>
#include <stdlib.h>

/*
 * 有这样一个数组A，大小为n，相邻元素差的绝对值都是1。
 * 如：A={4,5,6,5,6,7,8,9,10,9}。现在，给定A和目标整数t，请找到t在A中的位置。
 * 除了依次遍历，还有更好的方法么？
 */

static void printArray(int a[], int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d", a[i]);
		if (i != n - 1) {
			putchar(' ');
		} else {
			putchar('\n');
		}
	}
}

static int findNumber(int a[], int n, int number)
{
	int nextIndex = abs(number - a[0]);
	while (nextIndex < n) {
		if (a[nextIndex] == number) {
			return nextIndex;
		}
		nextIndex += abs(number - a[nextIndex]);
	}

	return -1;
}

void findTest()
{
	const int MAX = 10;
	int a[MAX] = {4, 5, 6, 5, 6, 7, 8, 9, 10, 9};
	printf("输入数组：	");
	printArray(a, MAX);
	
	for (int i = 0; i < MAX; i++) {
		printf("查找%d	下标为%d\n", a[i], findNumber(a, MAX, a[i]));
	}
	printf("查找%d	下标为%d\n", 100, findNumber(a, MAX, 100));
}
