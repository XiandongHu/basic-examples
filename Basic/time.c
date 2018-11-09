#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

uint64_t get_micro_seconds(clockid_t id)
{
	struct timespec ts;
	clock_gettime(id, &ts);
	return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}

int main(int argc, char** argv)
{
	time_t t = time(NULL);
	printf("time: %ld\n", t * 1000);

	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("gettimeofday: %ld\n", tv.tv_sec * 1000000 + tv.tv_usec);

	printf("clock_gettime(CLOCK_REALTIME): %ld\n", get_micro_seconds(CLOCK_REALTIME));
	printf("clock_gettime(CLOCK_MONOTONIC): %ld\n", get_micro_seconds(CLOCK_MONOTONIC));

	return 0;
}
