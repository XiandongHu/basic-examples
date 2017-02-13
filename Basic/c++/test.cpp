#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char** argv)
{
	char* a = (char*) malloc(100);
	memset(a, 0, 100);
	strcpy(a, "hello world");
	string s = a;
	cout << "before free: " << s << ", length=" << s.length() << endl;
	free(a);
	cout << "after free: " << s << ", length=" << s.length() << endl;
	return 0;
}
