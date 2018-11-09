#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t wait_pid(int options)
{
	int status;
	pid_t pid = waitpid(-1, &status, options);
	if (pid <= 0) {
		return pid;
	}
	if (WIFEXITED(status)) {
		printf("child exist by code: %d\n", WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status)) {
		printf("child exist for signal: %d\n", WTERMSIG(status));
	}
	return pid;
}

void sig_int1(int signo)
{
	char s[] = "received";
	psignal(signo, s);
}

void sig_int2(int signo)
{
	char s[] = "received";
	psignal(signo, s);
	exit(1);
}

void sig_chld(int signo)
{
	char s[] = "received";
	psignal(signo, s);

	while (1) {
		pid_t pid = wait_pid(WNOHANG);
		if (pid > 0) {
			printf("child pid (%d) exit\n", pid);
		} else {
			if (pid == 0) {
				printf("no child exit\n");
			} else {
				printf("on error: %m\n");
			}
			break;
		}
	}
}

int main(int argc, char** argv)
{
	struct sigaction sigact_int;
	sigact_int.sa_handler = sig_int1;
	sigact_int.sa_flags = 0;
	sigaction(SIGINT, &sigact_int, NULL);

	struct sigaction sigact_chld;
	sigact_chld.sa_handler = sig_chld;
	sigact_chld.sa_flags = 0;
	sigaction(SIGCHLD, &sigact_chld, NULL);

	pid_t pid = fork();
	if (pid == 0) {
		/*struct sigaction sigact_int;
		sigact_int.sa_handler = sig_int2;
		sigact_int.sa_flags = 0;
		sigaction(SIGINT, &sigact_int, NULL);*/

		/*for (int i = 0; i < 5; i++) {
			printf("### child %d...\n", i);
			sleep(2);
		}*/
		//execlp("./forever", "./forever", NULL);
		execlp("sh", "sh", "-c", "/home/huxiandong/Documents/Study/Test/Basic/forever &", NULL);
		printf("DONOT arrive here\n");
	} else if (pid > 0) {
		/*struct sigaction sigact_int;
		sigact_int.sa_handler = sig_int1;
		sigact_int.sa_flags = 0;
		sigaction(SIGINT, &sigact_int, NULL);*/

		pid_t p = wait_pid(0);
		if (p == 0) {
			printf("no child exit\n");
		} else if (p < 0) {
			printf("on error: %m\n");
		} else {
			printf("in main, child pid (%d) exit\n", p);
			printf("child exist\n");
		}
		for (int i = 0; i < 20; i++) {
			printf("### will exit in %ds...\n", 2 * (20 - i));
			sleep(2);
		}
	} else {
		printf("fork failed!\n");
	}

	return 0;
}
