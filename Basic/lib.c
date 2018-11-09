#include <stdio.h>

static void call()
{
	*((volatile char*) 0x0) = 0x88;
}

void crash()
{
	printf("enter crash...\n");
	//*((volatile char*) 0x0) = 0x88;
	call();
}
