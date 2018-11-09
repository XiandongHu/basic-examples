#include <stdio.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv)
{
	int pipe_fd[2];
	pipe(pipe_fd);

	char buf[1024] = {'\0'};

	fcntl(pipe_fd[0], F_SETFL, fcntl(pipe_fd[0], F_GETFL) | O_NONBLOCK);
	size_t ret = write(pipe_fd[1], "start", 5);
	printf("ret=%ld\n", ret);
	ret = write(pipe_fd[1], "oo", 2);
	printf("ret=%ld\n", ret);
	ret = read(pipe_fd[0], buf, 5);
	printf("buf=%s, ret=%ld\n", buf, ret);
	ret = read(pipe_fd[0], buf, 1);
	printf("buf=%s, ret=%ld\n", buf, ret);
	ret = read(pipe_fd[0], buf, 2);
	printf("buf=%s, ret=%ld\n", buf, ret);
	ret = read(pipe_fd[0], buf, 2);
	printf("buf=%s, ret=%ld\n", buf, ret);

	struct iovec iov[2];

	char cmd = 1;
	char* data = "12345";
	iov[0].iov_base = &cmd;
	iov[0].iov_len = sizeof(char);
	iov[1].iov_base = data;
	iov[1].iov_len = 99;
	writev(pipe_fd[1], iov, 2);

	cmd = 2;
	data = "67890";
	iov[0].iov_base = &cmd;
	iov[0].iov_len = sizeof(char);
	iov[1].iov_base = data;
	iov[1].iov_len = 99;
	writev(pipe_fd[1], iov, 2);

	char cmd1;
	char data1[100] = { 0 };
	struct iovec iov1[2];
	iov1[0].iov_base = &cmd1;
	iov1[0].iov_len = sizeof(char);
	iov1[1].iov_base = data1;
	iov1[1].iov_len = 100 - 1;
	ssize_t count = readv(pipe_fd[0], iov1, 2);
	printf("count=%ld, data1=%s\n", count, data1);

	memset(data1, 0, 100);
	iov1[0].iov_base = &cmd1;
	iov1[0].iov_len = sizeof(char);
	iov1[1].iov_base = data1;
	iov1[1].iov_len = 100 - 1;
	count = readv(pipe_fd[0], iov1, 2);
	printf("count=%ld, data1=%s\n", count, data1);

	memset(data1, 0, 100);
	iov1[0].iov_base = &cmd1;
	iov1[0].iov_len = sizeof(char);
	iov1[1].iov_base = data1;
	iov1[1].iov_len = 100 - 1;
	count = readv(pipe_fd[0], iov1, 2);
	printf("count=%ld, data1=%s\n", count, data1);

	close(pipe_fd[0]);
	close(pipe_fd[1]);

	return 0;
}
