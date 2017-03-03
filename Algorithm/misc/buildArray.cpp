#include <stdio.h>
#include "util.h"

/**
 * 给定一数组a[N]，我们希望构造数组b [N]，其中b[j]=a[0]*a[1]…a[N-1] / a[j]，
 * 在构造过程中，不允许使用除法，要求O（1）空间复杂度和O（n）的时间复杂度；
 * 除遍历计数器与a[N] b[N]外，不可使用新的变量（包括栈临时变量、堆空间和全局静态变量等）
 */

static void buildArray(int a[], int n, int b[])
{
	int i;
	for (i = 1, b[0] = 1; i < n; i++) {
		b[i] = b[i - 1] * a[i - 1];
	}
	/*b[0] = 1;
	b[1] = a[0];
	b[2] = a[0] * a[1];
	b[3] = a[0] * a[1] * a[2];
	... ...
	b[n - 2] = a[0] * a[1] * ... * a[n - 3];
	b[n - 1] = a[0] * a[1] * a[2] * ... * a[n - 2];*/

	// 先直观的用一个临时变量tmp
	/*int tmp = a[n - 1];
	for (i = n - 2; i >= 0; i--) {
		b[i] *= tmp;
		tmp *= a[i];
	}*/
	/*b[n - 2] = b[n - 2] * a[n - 1];
	tmp = a[n - 1] * a[n - 2];
	b[n - 3] = b[n - 3] * a[n - 1] * a[n - 2];
	tmp = a[n - 1] * a[n - 2] * a[n - 3];
	... ...
	b[0] = b[0] * a[n - 1] * a[n - 2] * ... * a[1];
	tmp = a[n - 1] * ... * a[i];*/

	// 可以考虑用b[0]代替上面的临时变量tmp
	for (i = n - 1; i >= 1; i--) {
		b[i] *= b[0];
		b[0] *= a[i];
	}
	/*b[n - 1] = b[n - 1];
	b[0] = a[n - 1];
	b[n - 2] = b[n - 2] * a[n -  1];
	b[0] = a[n - 1] * a[n - 2];
	b[n - 3] = b[n - 3] * a[n - 1] * a[n - 2];
	b[0] = a[n - 1] * a[n - 2] * a[n - 3];
	... ...
	b[1] = b[1] * a[n - 1] * a[n - 2] * ... * a[2];
	b[0] = a[n - 1] * a[n - 2] * ... * a[1];*/
}

void buildArrayTest()
{
	const int MAX = 5;
	int a[MAX] = {2, 4, 6, 8, 10};
	printf("原数组为：	");
	printArray(a, MAX);

	int b[MAX] = {0};
	buildArray(a, MAX, b);
	printf("新数组为：	");
	printArray(b, MAX);
}
