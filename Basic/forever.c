#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sig_int(int signo)
{
	char s[] = "received2";
	psignal(signo, s);
	exit(1);
}

int main(int argc, char** argv)
{
	struct sigaction sigact_int;
	sigact_int.sa_handler = sig_int;
	sigact_int.sa_flags = 0;
	sigaction(SIGINT, &sigact_int, NULL);

	while (1) {
		printf("*** forever\n");
		sleep(2);
	}
	return 0;
}
