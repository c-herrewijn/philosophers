/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 17:54:48 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/25 18:03:44 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
returns end - start in milli seconds
returns 0 if start > end 
*/
size_t	calc_ms_passed(struct timeval *start, struct timeval *end)
{
	size_t			ms_passed;
	long int		seconds_passed;
	int				us_passed;

	if (start->tv_sec > end->tv_sec
		|| (start->tv_sec == end->tv_sec && start->tv_usec > end->tv_usec))
		return (0);
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
void	ms_sleep_pure(size_t ms, struct timeval *start)
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

// sleeps relative to start time
void	ms_sleep(size_t ms, struct timeval *start, t_settings *settings,
	t_locks *locks)
{
	struct timeval	end;
	size_t			ms_passed;
	size_t			ms_passed_previous;
	bool			simul_running;

	gettimeofday(&end, NULL);
	ms_passed = calc_ms_passed(start, &end);
	ms_passed_previous = ms_passed;
	while (ms_passed < ms)
	{
		usleep(400);
		gettimeofday(&end, NULL);
		ms_passed = calc_ms_passed(start, &end);
		if (ms_passed != ms_passed_previous)
		{
			pthread_mutex_lock(&(locks->settings_lock));
			simul_running = settings->simul_running;
			pthread_mutex_unlock(&(locks->settings_lock));
			if (simul_running == false)
				break ;
		}
		ms_passed_previous = ms_passed;
	}
}
