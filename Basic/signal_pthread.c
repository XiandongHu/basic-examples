#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>

static void* sig_handler_thd(void* data)
{
	sigset_t* mask = data;
	int ret, sig;

	do {
		printf("sig wait...\n");
		ret = sigwait(mask, &sig);
		printf("signal %d gotten\n", sig);
	} while (ret == EINTR);

	printf("sig handler thread exit...\n");
}

static void* test_thd(void* data)
{
	printf("test thread start...\n");
	int* value = data;
	while (1) {
		printf("value: %d\n", *value);
		sleep(2);
	}
}

static void test()
{
	pthread_t thd;
	int value = 2;
	pthread_create(&thd, NULL, test_thd, &value);
}

static void setup_sig_handler()
{
	sigset_t mask, oldmask;
	pthread_t thd;
	int ret;

	sigemptyset(&mask);
	sigaddset(&mask, SIGHUP);
	sigaddset(&mask, SIGPIPE);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGTERM);
	sigaddset(&mask, SIGSEGV);

	printf("SIGHUP=%d, SIGPIPE=%d, SIGINT=%d, SIGTERM=%d, SIGSEGV=%d\n",
					SIGHUP, SIGPIPE, SIGINT, SIGTERM, SIGSEGV);

	pthread_sigmask(SIG_BLOCK, &mask, &oldmask);

	ret = pthread_create(&thd, NULL, sig_handler_thd, &mask);
	if (ret) {
		fprintf(stderr, "Failed to create signal handler thread: %d\n", ret);
		pthread_sigmask(SIG_SETMASK, &oldmask, NULL);
	}
}

int main(int argc, char** argv)
{
	/*sigset_t mask, oldmask;
	pthread_t thd;
	int ret;

	sigemptyset(&mask);
	sigaddset(&mask, SIGHUP);
	sigaddset(&mask, SIGPIPE);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGTERM);
	sigaddset(&mask, SIGSEGV);

	printf("SIGHUP=%d, SIGPIPE=%d, SIGINT=%d, SIGTERM=%d, SIGSEGV=%d\n",
					SIGHUP, SIGPIPE, SIGINT, SIGTERM, SIGSEGV);

	pthread_sigmask(SIG_BLOCK, &mask, &oldmask);

	ret = pthread_create(&thd, NULL, sig_handler_thd, &mask);
	if (ret) {
		fprintf(stderr, "Failed to create signal handler thread: %d\n", ret);
		pthread_sigmask(SIG_SETMASK, &oldmask, NULL);
	}*/
	/*setup_sig_handler();*/

	/*test();*/
	setup_sig_handler();

	/*while (1) {
		sleep(3);
	}*/

	pause();
	return 0;
}
