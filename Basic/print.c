#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_func(void* arg)
{
	while (1) {
		sleep(2);
		printf("*** thread func\n");
	}
}

int main(int argc, char** argv)
{
	pthread_t t;
	pthread_create(&t, NULL, thread_func, NULL);

	while (1) {
		printf("### main");
		//fflush(stdout);
		sleep(1);
	}

	return 0;
}
