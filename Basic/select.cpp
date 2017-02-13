#include <unistd.h>
#include <pthread.h>
#include <sys/select.h>

#include <iostream>

int fd[2];

void* threadFunc(void* arg)
{
	while (1) {
		sleep(2);
		char value[2] = { 'm', 'c' };
		write(fd[1], value, sizeof(value));
	}
}

int main(int argc, char** argv)
{
	fd_set readSet;
	int maxFd = 2;
	pipe(fd);
	std::cout << "fd[0]=" << fd[0] << ", fd[1]=" << fd[1] << std::endl;
	maxFd = fd[0] > fd[1] ? fd[0] : fd[1];

	pthread_t threadId;
	pthread_create(&threadId, NULL, threadFunc, NULL);

	while (1) {
		FD_ZERO(&readSet);
		FD_SET(fd[0], &readSet);
		std::cout << "select start ..." << std::endl;
		int ret = select(maxFd + 1, &readSet, NULL, NULL, NULL);
		if (ret < 0) {
			std::cout << "Error: select failed" << std::endl;
			break;
		} else if (ret == 0) {
			std::cout << "Error: select timeout" << std::endl;
		} else {
			if (FD_ISSET(fd[0], &readSet)) {
				std::cout << "read event coming" << std::endl;
				char buf[2];
				read(fd[0], buf, sizeof(buf));
				std::cout << "buf[0]=" << buf[0] << ", buf[1]=" << buf[1] << std::endl;
			} else {
				std::cout << "Other ???" << std::endl;
			}
		}
	}

	return 0;
}
