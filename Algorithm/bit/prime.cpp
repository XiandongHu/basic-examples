#include <stdio.h>

#define MAX	100

int result[MAX / 3];
int num;

static void findPrime1()
{
	int i, j;
	bool flags[MAX] = {false};
	
	num = 0;
	for (i = 2; i < MAX; i++) {
		if (!flags[i]) {
			result[num++] = i;
			for (j = i; j < MAX; j += i) {
				flags[j] = true;
			}
		}
	}
}

static void findPrime2()
{
	int i, j;
	int flags[MAX / 32] = {0};

	num = 0;
	for (i = 2; i < MAX; i++) {
		if (!((flags[i / 32] >> (i % 32)) & 1)) {
			result[num++] = i;
			for (j = i; j < MAX; j += i) {
				flags[j / 32] |= (1 << (j % 32));
			}
		}
	}
}

static void printResult()
{
	for (int i = 0; i < num; i++) {
		printf("%d", result[i]);
		if (i < num - 1) {
			printf(" ");
		}
	}
	printf("\n");
}

void primeTest()
{
	printf("100以内的素数：	");
	//findPrime();
	findPrime2();
	printResult();
}
