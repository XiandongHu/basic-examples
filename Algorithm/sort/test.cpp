#include <stdio.h>
#include "util.h"

extern void bubbleTest(int a[], int n);

int main(int argc, char** argv)
{
	const int NUM = 10;
	int a[NUM] = {5, 19, 2, 5, 7, 20, 16, 1, 9, 11};
	printf("输入数据：	");
	printArray(a, NUM);

	bubbleTest(a, NUM);
}