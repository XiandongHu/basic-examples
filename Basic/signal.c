#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <signal.h>

#define BUFFER_SIZE 80

void sig_int(int signo)
{
	char s[] = "received";
	psignal(signo, s);
}

void sig_alrm(int signo)
{
	char s[] = "received";
	psignal(signo, s);
}

void err_sys(const char* err)
{
	perror(err);
	exit(1);
}

int main(int argc, char** argv)
{
	fd_set readfds;
	sigset_t sigset;
	sigset_t zeromask;

	// zero mask
	if (sigemptyset(&zeromask) == -1) {
		err_sys("sigemptyset");
	}

	// set SIGINT signal handler
	struct sigaction sigact_int;
	sigact_int.sa_handler = sig_int;
	if (sigemptyset(&sigact_int.sa_mask) == -1) {
		err_sys("sigemptyset");
	}
	sigact_int.sa_flags = 0;
	if (sigaction(SIGINT, &sigact_int, NULL) == -1) {
		err_sys("sigaction");
	}

	// set SIGALRM signal handler
	struct sigaction sigact_alrm;
	sigact_alrm.sa_handler = sig_alrm;
	if (sigemptyset(&sigact_alrm.sa_mask) == -1) {
		err_sys("sigemptyset");
	}
	sigact_alrm.sa_flags = 0;
	if (sigaction(SIGALRM, &sigact_alrm, NULL) == -1) {
		err_sys("sigaction");
	}

	// initialize signal set and add SIGALRM into sigset
	if (sigemptyset(&sigset) == -1) {
		err_sys("sigemptyset");
	}
	if (sigaddset(&sigset, SIGALRM) == -1) {
		err_sys("sigaddset");
	}

	// block SIGALRM signal
	if (sigprocmask(SIG_BLOCK, &sigset, NULL) == -1) {
		err_sys("sigprocmask");
	}

	alarm(1);

	// select | pselect
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	if (select(STDIN_FILENO + 1, &readfds, NULL, NULL, NULL) <= 0) {
	//if (pselect(STDIN_FILENO + 1, &readfds, NULL, NULL, NULL, &sigset) <= 0) {
	//if (pselect(STDIN_FILENO + 1, &readfds, NULL, NULL, NULL, &zeromask) <= 0) {
		err_sys("pselect");
	}
	if (FD_ISSET(STDIN_FILENO, &readfds)) {
		char buf[BUFFER_SIZE];
		ssize_t nread = read(STDIN_FILENO, buf, BUFFER_SIZE);
		if (nread == -1) {
			err_sys("read");
		}
		if (write(STDOUT_FILENO, buf, nread) != nread) {
			err_sys("write");
		}
	}

	exit(0);
}
