#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_LINE 1024

int main(int argc, char** argv)
{
	char result[MAX_LINE];
	char command[MAX_LINE];

	/*snprintf(command, sizeof(command), "ls | wc -l");*/
	/*snprintf(command, sizeof(command), "ls ./abc");*/
	snprintf(command, sizeof(command), "ls ./abc 2>&1");

	FILE* fp = popen(command, "r");
	if (fp == NULL) {
		perror("popen failed");
		exit(1);
	}

	while (fgets(result, sizeof(result), fp) != NULL) {
		if ('\n' == result[strlen(result) - 1]) {
			result[strlen(result) - 1] = '\0';
		}
		printf("command [%s] output [%s]\n", command, result);
	}

	int rc = pclose(fp);
	if (rc == -1) {
		perror("pclose failed");
		exit(1);
	} else {
		printf("command [%s] child process status [%d] return value [%d]\n", command, rc, WEXITSTATUS(rc));
	}
	
	return 0;
}
