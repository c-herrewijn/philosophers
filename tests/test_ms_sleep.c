# include <stdio.h>
# include <sys/time.h>
# include "philo.h"

// gcc -I./libft -I./philo tests/test_ms_sleep.c philo/utils.c -g -o test.out

static void print_time_raw(struct timeval *time)
{
	printf("\nsec: %ld\n", time->tv_sec);
	printf("usec: %d\n", time->tv_usec);
}

int main(void)
{
	t_settings		settings;
	struct timeval	t;
	pthread_mutex_t	settings_lock;

	gettimeofday(&(settings.start_time), NULL);
	pthread_mutex_init(&settings_lock, NULL);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &settings_lock);
	print_time_raw(&t);

	puts("\nsleeping 1 ms:\n");
	ms_sleep(1, &t);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &settings_lock);
	print_time_raw(&t);

	puts("\nsleeping 10 ms:\n");
	ms_sleep(10, &t);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &settings_lock);
	print_time_raw(&t);

	puts("\nsleeping 100 ms:\n");
	ms_sleep(100, &t);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &settings_lock);
	print_time_raw(&t);

	puts("\nsleeping 1000 ms:\n");
	ms_sleep(1000, &t);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &settings_lock);
	print_time_raw(&t);

	puts("\nsleeping 4321 ms:\n");
	ms_sleep(4321, &t);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &settings_lock);
	print_time_raw(&t);
	
	puts("\nsleeping 42 ms:\n");
	ms_sleep(42, &t);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &settings_lock);
	print_time_raw(&t);
}
