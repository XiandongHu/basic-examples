#include <stdio.h>

template <class T>
static void printBinary(T a)
{
	for (int i = sizeof(a) * 8 - 1; i >= 0; i--) {
		if ((a >> i) & 1) {
			putchar('1');
		} else {
			putchar('0');
		}
		if ((i % 8) == 0 && i != 0) {
			putchar(' ');
		}
	}
	putchar('\n');
}

// 交换一个16位无符号整数的高8位和低8位
static void exchangeHighAndLow(unsigned short a)
{
	printf("原数 %d 的二进制为：	", a);
	printBinary(a);
	a = (a << 8) + (a >> 8);
	printf("交换高低位之后为：	");
	printBinary(a);
}

// 二进制逆序
static void reverseBits(unsigned short a)
{
	/**
	 * 类似归并排序的分组处理：
	 * 1.每2位为一组，组内高低位交换
	 * 2.每4位为一组，组内高低位交换
	 * 3.每8位为一组，组内高低位交换
	 * 4.每16位为一组，组内高低位交换
	 *
	 * 以第1步为例，每2位为一组，再分别组内高低位交换，比较麻烦，
	 * 可以考虑一种非常有技巧的方法：
	 * 分别取10000110 11011000的奇数位和偶数位，空位以下划线表示：
	 * 原数		10000110 11011000
	 * 奇数位	1_0_0_1_ 1_0_1_0_
	 * 偶数位	_0_0_1_0 _1_1_0_0
	 * 先将下划线用0填充：
	 * 奇数位	10000010 10001000
	 * 偶数位	00000100 01010000
	 * 再将奇数位右移1位，偶数位左移1位，两个数相或即可达到奇偶位上数据交换的效果
	 */
	printf("原数 %d 的二进制为：	", a);
	printBinary(a);
	a = ((a & 0xAAAA) >> 1) | ((a & 0x5555) << 1);
	a = ((a & 0xCCCC) >> 2) | ((a & 0x3333) << 2);
	a = ((a & 0xF0F0) >> 4) | ((a & 0x0F0F) << 4);
	a = ((a & 0xFF00) >> 8) | ((a & 0x00FF) << 8);
	printf("逆序之后为：		");
	printBinary(a);
}

// 二进制中1的个数
static void numbersOf1InBits(unsigned short a)
{
	/**
	 * 可以用循环移位计数来解决，还有一种高效的方法：
	 * 类似上面的二进制逆序：
	 * 1.每2位为一组，组内高低位相加
	 * 2.每4位为一组，组内高低位相加
	 * 3.每8位为一组，组内高低位相加
	 * 4.每16位为一组，组内高低位相加
	 * 最后得到的结果即为二进制中1的个数
	 */
	printf("原数 %d 的二进制为：	", a);
	printBinary(a);
	a = ((a & 0xAAAA) >> 1) + (a & 0x5555);
	a = ((a & 0xCCCC) >> 2) + (a & 0x3333);
	a = ((a & 0xF0F0) >> 4) + (a & 0x0F0F);
	a = ((a & 0xFF00) >> 8) + (a & 0x00FF);
	printf("计算结果为：		");
	printBinary(a);
	printf("二进制中1的个数位为：%d\n", a);
}

void exchangeTest()
{
	unsigned short a = 34520;
	exchangeHighAndLow(a);
	reverseBits(a);
	numbersOf1InBits(a);
}
