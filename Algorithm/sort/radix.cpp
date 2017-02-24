#include <stdio.h>
#include <math.h>
#include <string.h>
#include "util.h"

static void radixSort(int a[], int n, int digits)
{
	int i, j, bit;
	// 必须从低位数开始，如果从高位数开始，次高位的排序会影响已经排好的大小关系
	for (i = 1; i <= digits; i++) {
		int* tmpArray = new int[n];
		memset(tmpArray, 0, n * sizeof(int));
		int countingArray[10] = {0};

		for (j = 0; j < n; j++) {
			bit = a[j] / (int)pow(10, i - 1)  - (a[j] / (int)pow(10, i) * 10);
			countingArray[bit] += 1;
		}
		for (j = 1; j < 10; j++) {
			countingArray[j] += countingArray[j - 1];
		}
		// 从后往前，保持稳定
		for (j = n - 1; j >= 0; j--) {
			bit = a[j] / (int)pow(10, i - 1)  - (a[j] / (int)pow(10, i) * 10);
			tmpArray[countingArray[bit] - 1] = a[j];
			countingArray[bit] -= 1;
		}
		for (j = 0; j < n; j++) {
			a[j] = tmpArray[j];
		}
		printf("第%d位排序结果：	", i);
		printArray(a, n);
	}
}

void radixTest()
{
	const int NUM = 6;
	int a[NUM] = {68, 342, 1, 169, 29, 1040};
	printf("基数排序输入数据：	");
	printArray(a, NUM);
	
	radixSort(a, NUM, 4);
}
