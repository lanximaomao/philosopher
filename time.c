#include "philo.h"

// one second = 1,000,000 microseconds

//int main()
//{
//	struct timeval before;
//	struct timeval after;
//	gettimeofday(&before, NULL);
//	//printf("seconds: %ld\nmicrosecond: %d\n", before.tv_sec, before.tv_usec);
//	usleep(100000); // 100 miliseconds
//	gettimeofday(&after, NULL);
//	//printf("seconds: %ld\nmicrosecond: %d\n", after.tv_sec, after.tv_usec);
//	printf("time difference: %ld\n", (after.tv_usec-before.tv_usec) / 1000 + (after.tv_sec - before.tv_sec) * 1000);
//}

int timestamp(struct  timeval before, struct timeval after)
{
	int timestamp;

	timestamp = (after.tv_sec - before.tv_sec) * 1000 + (after.tv_usec - before.tv_usec)/1000;
}

