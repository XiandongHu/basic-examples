#include <stdio.h>
#include "util.h"

/**
 * 一个大小为n的数组，里面的数都属于范围[0, n-1]，有不确定的重复元素，找到至少一个重复元素，
 * 要求O(1)空间和O(n)时间。
 */

/**
 * 基于基数排序的思想
 */
static int findRepeatNumber1(int a[], int n)
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

/**
 * 符号位标记法
 * 这种通过取负来判断元素是否重复访问的方法对于数组第0个元素为0并且数据中只有0重复时无法找出正解
 */
static int findRepeatNumber2(int a[], int n)
{
	for (int i = 0; i < n; i++) {
		if (a[i] > 0) {
			if (a[a[i]] < 0) { // 已经被标上负值了，有重复
				return a[i];
			} else {
				a[a[i]] = -a[a[i]]; // 记为负
			}
		} else {
			if (a[-a[i]] < 0) { // 已经被标上负值了，有重复
				return -a[i];
			} else {
				a[-a[i]] = -a[-a[i]]; // 记为负
			}
		}
	}

	return -1;
}

/**
 * 因为对0取负导致上面的算法有缺陷，沿着上面的标记法的思路，
 * 采用加n的方法，通过判断元素是否大于或等于n就能决定该元素是否被访问过了
 */
static int findRepeatNumber3(int a[], int n)
{
	for (int i = 0; i < n; i++) {
		int realIndex = a[i] >= n ? a[i] - n : a[i];
		if (a[realIndex] >= n) {
			return realIndex;
		} else {
			a[realIndex] += n;
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

	//int number = findRepeatNumber1(a, MAX);
	//int number = findRepeatNumber2(a, MAX);
	int number = findRepeatNumber3(a, MAX);
	if (number != -1) {
		printf("找到重复元素：%d\n", number);
	} else {
		printf("没有找到重复元素\n");
	}
}
