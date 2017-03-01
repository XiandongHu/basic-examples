#include <stdio.h>

extern void findIndexTest();
extern void findRepeatTest();
extern void findLostTest();

int main(int argc, char** argv)
{
	findIndexTest();
	printf("\n");

	findRepeatTest();
	printf("\n");

	findLostTest();

	return 0;
}
