#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

//static char line[64];

static const char* get_ident()
{
    FILE* self;
    //static char line[64];
    char line[64];
    char* p = NULL;

    if ((self = fopen("/proc/self/status", "r")) != NULL) {
        while (fgets(line, sizeof(line), self)) {
            if (!strncmp(line, "Name:", 5)) {
                printf("line=(%p) %s\n", (void*)line, line);
                p = strtok(line, "\t\n");
                printf("111111\n");
                printf("p=%s\n", p);
                p = strtok(NULL, "\t\n");
                printf("222222\n");
                if (p != NULL) {
                    printf("3333333333\n");
					printf("p=%p\n", p);
                } else {
                    printf("p is null\n");
                }
                break;
            }
        }
        fclose(self);
    }

    return p;
}

int main(int argc, char** argv)
{
	/*unsigned char value = 0xF7;
	printf("0x%X\n", value);
	char str[5] = { 0 };
	sprintf(str, "0x%X", value);
	printf("str: %s\n", str);
	int i = atoi(str);
	unsigned char j = (unsigned char)strtoi(str, NULL, 16);
	printf("i=%d\n", i);
	printf("j=%d\n", j);*/

	const char* ident = get_ident();
	printf("ident=%s\n", ident);

	//printf("foo: %d\n", foo(2));
	return 0;
}

int foo(int a, int b)
{
	return (a + b);
}
