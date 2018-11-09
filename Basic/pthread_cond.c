#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread_func(void* arg)
{
	pthread_detach(pthread_self());

	sleep(1);

	printf("### thread: 111\n");
	pthread_mutex_lock(&mutex);
	printf("### thread: 222\n");
	pthread_cond_wait(&cond, &mutex);
	printf("### thread: 333\n");
	pthread_mutex_unlock(&mutex);
	printf("### thread: 444\n");

	sleep(5);

	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t t;
	pthread_create(&t, NULL, thread_func, NULL);

	while (1) {
		printf("### main: 111\n");
		pthread_mutex_lock(&mutex);
		printf("### main: 222\n");
		pthread_cond_signal(&cond);
		printf("### main: 333\n");
		pthread_mutex_unlock(&mutex);
		printf("### main: 444\n");

		sleep(2);
	}

	return 0;
}
