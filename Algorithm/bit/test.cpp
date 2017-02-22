#include <stdio.h>

extern void primeTest();
extern void exchangeTest();
extern void lostTest();

int main(int argc, char** argv)
{
	primeTest();
	printf("\n");

	exchangeTest();
	printf("\n");

	lostTest();

	return 0;
}
