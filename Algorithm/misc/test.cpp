#include <stdio.h>

extern void findIndexTest();
extern void findRepeatTest();
extern void findLostTest();
extern void reverseSequenceTest();
extern void buildArrayTest();

int main(int argc, char** argv)
{
	findIndexTest();
	printf("\n");

	findRepeatTest();
	printf("\n");

	findLostTest();
	printf("\n");

	reverseSequenceTest();
	printf("\n");

	buildArrayTest();

	return 0;
}
