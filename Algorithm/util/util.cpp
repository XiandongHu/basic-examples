#include <stdio.h>
#include "util.h"

void copyArray(int a[], int n, int* b)
{
	for (int i = 0; i < n; i++) {
		b[i] = a[i];
	}
}

void printArray(int a[], int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d", a[i]);
		if (i != n - 1) {
			printf(" ");
		} else {
			printf("\n");
		}
	}
}

void swap(int& a, int& b)
{
	if (a != b) {
		a ^= b;
		b ^= a;
		a ^= b;
	}
}
