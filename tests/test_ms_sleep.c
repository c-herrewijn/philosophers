# include <stdio.h>
# include <sys/time.h>
# include "philo.h"

// gcc -I./libft -I./philo tests/test_ms_sleep.c philo/time_utils.c -g -o test.out

static void print_time_raw(struct timeval *time)
{
	printf("\nsec: %ld\n", time->tv_sec);
	printf("usec: %d\n", time->tv_usec);
}

void	test_ms_sleep(void)
{
	t_settings		settings;
	t_locks			locks;
	struct timeval	t;
	pthread_mutex_t	settings_lock;
	int res;

	puts("testing ms_sleep ...");

	settings.simul_running = true;
	gettimeofday(&(settings.start_time), NULL);
	res = pthread_mutex_init(&(locks.settings_lock), NULL);
	printf("res: %d\n", res);
	res = pthread_mutex_init(&(locks.print_lock), NULL);
	printf("res: %d\n", res);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &(locks.settings_lock));
	print_time_raw(&t);

	puts("\nsleeping 1 ms:\n");
	ms_sleep(1, &t, &settings, &locks);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &(locks.settings_lock));
	print_time_raw(&t);

	puts("\nsleeping 10 ms:\n");
	ms_sleep(10, &t, &settings, &locks);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &(locks.settings_lock));
	print_time_raw(&t);

	puts("\nsleeping 100 ms:\n");
	ms_sleep(100, &t, &settings, &locks);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &(locks.settings_lock));
	print_time_raw(&t);

	puts("\nsleeping 1000 ms:\n");
	ms_sleep(1000, &t, &settings, &locks);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &(locks.settings_lock));
	print_time_raw(&t);

	puts("\nsleeping 4321 ms:\n");
	ms_sleep(4321, &t, &settings, &locks);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &(locks.settings_lock));
	print_time_raw(&t);
	
	puts("\nsleeping 42 ms:\n");
	ms_sleep(42, &t, &settings, &locks);

	gettimeofday(&t, NULL);
	printf("time:");
	print_timestamp(&settings, &(locks.settings_lock));
	print_time_raw(&t);

	puts("\n-----------\n");
}

void	test_calc_ms_passed(void)
{
	size_t			ms_passed;
	struct timeval	start_time;
	struct timeval	end_time;

	puts("testing calc_ms_passed ...");
	start_time.tv_sec = 1689168989;
	start_time.tv_usec = 797375;
	end_time.tv_sec = 1689168989;
	end_time.tv_usec = 838630;

	ms_passed = calc_ms_passed(&start_time, &end_time);
	printf("ms passed: %zu\n", ms_passed);

	puts("\n-----------\n");
}

int main(void)
{
	test_ms_sleep();
	test_calc_ms_passed();
}
