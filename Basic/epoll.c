#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

#define MAX_EVENTS 64

static int create_socket(int server)
{
	int sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sfd == -1) {
		printf("create socket failed\n");
		return -1;
	}

	struct sockaddr_in sa;
	bzero(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	if (server) {
		sa.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(sfd, (struct sockaddr*)&sa, sizeof(struct sockaddr)) == -1) {
			printf("bind socket failed\n");
			return -1;
		}
	} else {
		sa.sin_addr.s_addr = inet_addr("127.0.0.1");
		if (connect(sfd, (struct sockaddr*)&sa, sizeof(struct sockaddr)) == -1) {
			printf("connect socket failed\n");
			return -1;
		}
	}
	return sfd;
}

static int make_socket_non_block(int sfd)
{
	int flags = fcntl(sfd, F_GETFL, 0);
	if (flags == -1) {
		printf("get fd flag failed\n");
		return -1;
	}
	if (fcntl(sfd, F_SETFL, flags | O_NONBLOCK) == -1) {
		printf("set fd flag failed\n");
		return -1;
	}
	return 0;
}

static int run_server()
{
	int sfd = create_socket(1);
	if (sfd == -1) {
		abort();
	}
	if (make_socket_non_block(sfd) == -1) {
		abort();
	}

	if (listen(sfd, SOMAXCONN) == -1) {
		printf("listen socket failed\n");
		abort();
	}

	int efd = epoll_create1(0);
	if (efd == -1) {
		printf("create epoll failed\n");
		abort();
	}

	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = sfd;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event) == -1) {
		printf("ctl epoll failed\n");
		abort();
	}

	printf("Server Running...\n");

	struct epoll_event* events = calloc(MAX_EVENTS, sizeof(struct epoll_event));
	while (1) {
			printf("waiting event...\n");
		int n = epoll_wait(efd, events, MAX_EVENTS, -1);
		for (int i = 0; i < n; i++) {
			if (events[i].events & (EPOLLERR | EPOLLHUP)) {
				printf("fd epoll error\n");
				close(events[i].data.fd);
				continue;
			}
			if (events[i].data.fd == sfd) {
				if (events[i].events & EPOLLIN) {
					// new connection
					while (1) {
						struct sockaddr_in sa;
						socklen_t len = sizeof(sa);
						int infd = accept(sfd, (struct sockaddr*)&sa, &len);
						if (infd == -1) {
							if (errno == EAGAIN || errno == EWOULDBLOCK) {
								// all connections accepted
								break;
							} else {
								printf("accept failed\n");
								break;
							}
						}

						char hbuf[INET_ADDRSTRLEN] = {0};
						inet_ntop(AF_INET, &sa.sin_addr, hbuf, sizeof(hbuf));
						printf("connection accepted: fd=%d, host=%s, port=%d\n", infd, hbuf, sa.sin_port);
						
						if (make_socket_non_block(infd) == -1) {
							abort();
						}

						event.events = EPOLLIN | EPOLLRDHUP;
						event.data.fd = infd;
						if (epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event) == -1) {
							printf("ctl epoll failed\n");
							abort();
						}
					}
				}
			} else {
				if (events[i].events & EPOLLRDHUP) {
					printf("receive EPOLLRDHUP event\n");
				}
				if (events[i].events & EPOLLIN) {
					while (1) {
						char buf[512];
						ssize_t count = read(events[i].data.fd, buf, sizeof(buf));
						if (count == -1) {
							if (errno != EAGAIN) {
								printf("read error\n");
								close(events[i].data.fd);
							}
							break;
						} else if (count == 0) {
							printf("connection closed: fd=%d\n", events[i].data.fd);
							close(events[i].data.fd);
							break;
						}

						if (write(1, buf, count) == -1) {
							printf("write error\n");
							abort();
						}

						event.events = EPOLLOUT;
						epoll_ctl(efd, EPOLL_CTL_MOD, events[i].data.fd, &event);
					}
				} else if (events[i].events & EPOLLOUT) {
					if (write(events[i].data.fd, "it's echo man\n", 14) == -1) {
						if (errno == EPIPE) {
							printf("connection closed: fd=%d\n", events[i].data.fd);
							close(events[i].data.fd);
							continue;
						}
					}

					event.events = EPOLLIN | EPOLLRDHUP;
					epoll_ctl(efd, EPOLL_CTL_MOD, events[i].data.fd, &event);
				}
			}
		}
	}

	free(events);
	close(sfd);

	return 0;
}

static int run_client()
{
	int sfd = create_socket(0);
	if (sfd == -1) {
		abort();
	}

	while (1) {
			printf("writing...\n");
		if (write(sfd, "hello\n", 6) == -1) {
			printf("write error: %m\n");
			goto error;
		}

			printf("reading...\n");
		char buf[512];
		ssize_t count = read(sfd, buf, sizeof(buf));
		if (count == -1) {
			printf("read error\n");
			goto error;
		} else if (count == 0) {
			printf("connection closed: fd=%d\n", sfd);
			goto error;
		}
		printf("%s", buf);

		sleep(2);
	}

	close(sfd);
	return 0;

error:
	close(sfd);
	return 1;
}

static void help(const char* prog)
{
	printf("Usage: %s [-s][-c]\n", prog);
}

int main(int argc, char** argv)
{
	if (argc != 2 || (strcmp("-s", argv[1]) && strcmp("-c", argv[1]))) {
		help(argv[0]);
		exit(EXIT_FAILURE);
	}

	if (!strcmp("-s", argv[1])) {
		return run_server();
	} else {
		return run_client();
	}
}
