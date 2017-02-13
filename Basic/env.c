#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	extern char** environ;
	printf("environ=%p\n", environ);

	char** env = environ;
	while (*env != NULL) {
		printf("%s\n", *env++);
	}

	char* value = NULL;
	env = environ;
	while (*env != NULL) {
		char* str = *env++;
		if (strncmp(str, "LANG", strlen("LANG")) == 0) {
			value = str + strlen("LANG") + 1;
			printf("LANG=%s\n", value);
			break;
		}
	}

	printf("==================================\n");
	char* path = getenv("PATH");
	printf("PATH=%s\n", path != NULL ? path : "");
	char* android_sdk_home = getenv("ANDROID_SDK_HOME");
	printf("ANDROID_SDK_HOME=%s\n", android_sdk_home != NULL ? android_sdk_home : "");
	char* android_home = getenv("ANDROID_HOME");
	printf("ANDROID_HOME=%s\n", android_home != NULL ? android_home : "");
	char* android_ndk_home = getenv("ANDROID_NDK_HOME");
	printf("ANDROID_NDK_HOME=%s\n", android_ndk_home != NULL ? android_ndk_home : "");
	char* android_ndk = getenv("ANDROID_NDK");
	printf("ANDROID_NDK=%s\n", android_ndk != NULL ? android_ndk : "");
	printf("==================================\n");

	return 0;
}
