#include <stdio.h>

#include "hello.h"

#define MACRO_STRING "I am a MACRO"

void print()
{
	printf("Hello World, " MACRO_STRING "\n");
}

int main(int argc, char** argv)
{
	print();

	return 0;
}
