#include <execinfo.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <signal.h>  
#include <sys/types.h>  
#include <sys/syscall.h>  
#include <pthread.h>  

/* Obtain a backtrace and print it to @code{stdout}. */  
void print_trace(void)  
{
	printf("in print_trace: tid=%ld\n", syscall(__NR_gettid));

	void *array[20];
	size_t size;
	char **strings;
	size_t i;

	size = backtrace(array, 20);
	strings = backtrace_symbols(array, size);
	if (NULL == strings) {
		perror("backtrace_synbols");
		exit(EXIT_FAILURE);
	}

	printf("Obtained %zd stack frames.\n", size);

	for (i = 0; i < size; i++)
		printf("%s\n", strings[i]);

	free(strings);
	strings = NULL;
}

/* A dummy function to make the backtrace more interesting. */  
void dummy_function(void)  
{
	print_trace();
}

void dump_signal(int sig)
{
	print_trace();
	//system("./1.sh &");
	sleep(1);
	sleep(2);
	//exit(EXIT_FAILURE);
	//signal(sig, SIG_DFL);
	//raise(sig);
}

extern void crash();
void func_c()
{
	//*((volatile char *)0x0) = 0x9999;
	crash();
}

void func_b()
{
	func_c();
}

void func_a()
{
	func_b();
}

void* thread_func(void* arg)
{
	pthread_detach(pthread_self());
	printf("in thead_func: tid=%ld\n", syscall(__NR_gettid));
	/*while (1) {
		sleep(1);
		printf("thread waiting...\n");
	}*/
	func_a();
}

int main(int argc, char *argv[])
{
	printf("in main: tid=%ld\n", syscall(__NR_gettid));

	//dummy_function();

	/*if (signal(SIGSEGV, dump_signal) == SIG_ERR) {
		perror("catch SIGSEGV failed\n");
	}
	signal(SIGINT, dump_signal);*/
	/* So that we can raise the signal again from the signal handler */
	static const struct sigaction sa = {
        .sa_handler = dump_signal,
        .sa_flags = SA_RESETHAND, 
    };

    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGILL, &sa, NULL);
    sigaction(SIGFPE, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);

	pthread_t t;
	pthread_create(&t, NULL, thread_func, NULL);
	//func_a();
	
	while (1) {
		sleep(1);
		printf("main waiting...\n");
	}

	printf("End...\n");
	return 0;
}
