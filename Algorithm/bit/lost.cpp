#include <stdio.h>

// 很多成对出现的数字，由于意外有一个数字消失了，找到这个数字
static void findNumber1()
{
	const int MAX = 15;
	int a[MAX] = {1, 22, 46, 349, 87, 46, 349, 13, 88, 13, 1, 88, 22, 9, 9};
	int number = 0;
	for (int i = 0; i < MAX; i++) {
		number ^= a[i];
	}
	printf("缺失的数字是：%d\n", number);
}

// 很多成对出现的数字，有两个数字只出现了一次，找到这两个数字
static void findNumber2()
{
	const int MAX = 16;
	int a[MAX] = {1, 22, 46, 349, 87, 46, 349, 13, 88, 13, 1, 88, 22, 9, 9, 69};
	int i, j;

	// 计算这两个数异或的结果
	int tmp = 0;
	for (i = 0; i < 16; i++) {
		tmp ^= a[i];
	}
	// 找到第一个为1的位
	for (j = 0; j < sizeof(int) * 8; j++) {
		if ((tmp >> j) & 1) {
			break;
		}
	}
	// 第j位为1,说明这两个数在第j位是不同的，由此分组即可
	int number1 = 0, number2 = 0;
	for (i = 0; i < 16; i++) {
		if ((a[i] >> j) & 1) {
			number1 ^= a[i];
		} else {
			number2 ^= a[i];
		}
	}
	printf("两个只出现一次的数字分别是：%d和%d\n", number1, number2);
}

// 一组数据中只有一个数只出现了一次，其他数都出现了3次，找到这个数字
static void findNumber3()
{
	const int MAX = 10;
	int a[MAX] = {1, 22, 1, 87, 87, 1, 87, 10, 22, 22};
	int i, j;
	int bits[32] = {0};

	for (i = 0; i < 32; i++) {
		for (j = 0; j < MAX; j++) {
			bits[i] += ((a[j] >> i) & 1);
		}
	}
	int number = 0;
	for (i = 0; i < 32; i++) {
		if (bits[i] % 3) {
			number += (1 << i);
		}
	}
	printf("只出现一次的数字是：%d\n", number);
}

void lostTest()
{
	findNumber1();
	findNumber2();
	findNumber3();
}
