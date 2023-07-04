# include <stdio.h>
# include <sys/time.h>

// gcc -I./libft tests/test_ms_sleep.c philo/utils.c

void	ms_sleep(size_t ms, struct timeval *start);

static void print_time_raw(struct timeval *time)
{
	printf("sec: %ld\n", time->tv_sec);
	printf("usec: %d\n", time->tv_usec);
}

int main(void)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	print_time_raw(&t);

	puts("\nsleeping 1 ms:\n");
	ms_sleep(1, &t);

	gettimeofday(&t, NULL);
	print_time_raw(&t);

	puts("\nsleeping 10 ms:\n");
	ms_sleep(10, &t);

	gettimeofday(&t, NULL);
	print_time_raw(&t);

	puts("\nsleeping 100 ms:\n");
	ms_sleep(100, &t);

	gettimeofday(&t, NULL);
	print_time_raw(&t);

	puts("\nsleeping 1000 ms:\n");
	ms_sleep(1000, &t);

	gettimeofday(&t, NULL);
	print_time_raw(&t);

	puts("\nsleeping 4321 ms:\n");
	ms_sleep(4321, &t);

	gettimeofday(&t, NULL);
	print_time_raw(&t);
	
	puts("\nsleeping 42 ms:\n");
	ms_sleep(42, &t);

	gettimeofday(&t, NULL);
	print_time_raw(&t);
}
