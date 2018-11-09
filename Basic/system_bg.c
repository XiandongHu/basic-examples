#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_int(int signo)
{
	char s[] = "received";
	psignal(signo, s);
	exit(1);
}

void sig_chld(int signo)
{
	char s[] = "received";
	psignal(signo, s);

	int status;
	waitpid(-1, &status, WNOHANG);
	if (WIFEXITED(status)) {
		printf("child exist by code: %d\n", WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status)) {
		printf("child exist for signal: %d\n", WTERMSIG(status));
	}
}

int main(int argc, char** argv)
{
	struct sigaction sigact_int;
	sigact_int.sa_handler = sig_int;
	sigact_int.sa_flags = 0;
	sigaction(SIGINT, &sigact_int, NULL);

	struct sigaction sigact_chld;
	sigact_chld.sa_handler = sig_chld;
	sigact_chld.sa_flags = 0;
	sigaction(SIGCHLD, &sigact_chld, NULL);

	printf("### Start...\n");
	system("./forever");
	while (1) {
		printf("main loop\n");
		sleep(5);
	}
	printf("### End...\n");
	return 0;
}
