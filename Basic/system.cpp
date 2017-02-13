#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	char cmd[50] = {'\0'};
	sprintf(cmd, "/usr/bin/touch %s;/bin/mkdir %s", "file", "folder");
	std::cout << "system command: " << cmd << std::endl;
	system(cmd);

	return 0;
}
