/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 17:54:48 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/09 15:24:42 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// prints timestamp in different colors
// void	print_timestamp(t_philosopher *philosopher, struct timeval *now)
void	print_timestamp(struct timeval *start_time, struct timeval *now,
	size_t philo_nr)
{
	size_t			timestamp;
	size_t			nr_colors;
	static char		*colors[] = {
		ANSI_RED,
		ANSI_GREEN,
		ANSI_YELLOW,
		ANSI_BLUE,
		ANSI_MAGENTA,
		ANSI_CYAN,
	};

	nr_colors = sizeof(colors) / sizeof(char *);
	timestamp = calc_ms_passed(start_time, now);
	printf("%s%5zu", colors[(philo_nr - 1) % nr_colors], timestamp);
}

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
void	ms_sleep(size_t ms, struct timeval *start)
{
	struct timeval	end;
	size_t			ms_passed;

	gettimeofday(&end, NULL);
	ms_passed = calc_ms_passed(start, &end);
	while (ms_passed < ms)
	{
		usleep(400);
		gettimeofday(&end, NULL);
		ms_passed = calc_ms_passed(start, &end);
	}
}
