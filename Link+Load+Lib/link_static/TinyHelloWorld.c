char* str = "Hello World!\n";

void print()
{
	// %0 --- m32
	/*asm("movl $13,%%edx \n\t"
		"movl %0,%%ecx \n\t"
		"movl $1,%%ebx \n\t"
		"movl $4,%%eax \n\t"
		"int $0x80 \n\t"
		::"r"(str):"edx","ecx","ebx");*/
	asm("movl $1,%edx \n\t"
		"movl $22,%ecx \n\t"
		"movl $1,%ebx \n\t"
		"movl $4,%eax \n\t"
		"int $0x80 \n\t");
}

void exit()
{
	asm("movl $42,%ebx \n\t"
		"movl $1,%eax \n\t"
		"int $0x80 \n\t");
}

void nomain()
{
	print();
	exit();
}
