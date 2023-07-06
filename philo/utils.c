/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 17:54:48 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/06 16:39:20 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	calc_ms_passed(struct timeval *start, struct timeval *end)
{
	size_t			ms_passed;
	long int		seconds_passed;
	int				us_passed;

	seconds_passed = (end->tv_sec - start->tv_sec);
	if (end->tv_usec > start->tv_usec)
		us_passed = (end->tv_usec - start->tv_usec);
	else
	{
		us_passed = -1 * (start->tv_usec - end->tv_usec);
	}
	ms_passed = (size_t)(((seconds_passed * 1000000) + us_passed) / 1000);
	return (ms_passed);
}

// sleeps relative to start time
void	ms_sleep(size_t ms, struct timeval *start)
{
	struct timeval	end;
	size_t			ms_passed;

	gettimeofday(&end, NULL);
	ms_passed = calc_ms_passed(start, &end);
	while (ms_passed < ms)
	{
		usleep(100);
		gettimeofday(&end, NULL);
		ms_passed = calc_ms_passed(start, &end);
	}
}

void	print_timestamp(t_settings *settings, pthread_mutex_t *settings_lock)
{
	struct timeval	start;
	struct timeval	end;

	pthread_mutex_lock(settings_lock);
	start = settings->start_time;
	pthread_mutex_unlock(settings_lock);
	gettimeofday(&end, NULL);
	printf("%zu ", calc_ms_passed(&start, &end));
}
