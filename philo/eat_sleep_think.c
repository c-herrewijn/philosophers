/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 17:17:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/06 17:53:13 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosopher *philosopher)
{
	size_t			time_to_eat;
	struct timeval	eat_start_time;

	pthread_mutex_lock(philosopher->settings_lock);
	time_to_eat = philosopher->settings->time_to_eat;
	pthread_mutex_unlock(philosopher->settings_lock);
	pthread_mutex_lock(philosopher->fork_left);
	print_timestamp(philosopher->settings, philosopher->settings_lock);
	printf("%zu has taken a fork\n", philosopher->nr);
	pthread_mutex_lock(philosopher->fork_right);
	eat_start_time = print_timestamp(philosopher->settings,
		philosopher->settings_lock);
	printf("%zu has taken a fork\n", philosopher->nr);
	print_timestamp(philosopher->settings, philosopher->settings_lock);
	printf("%zu is eating\n", philosopher->nr); // todo: make sure the same time is printed as the 2nd fork!
	ms_sleep(time_to_eat, &eat_start_time);
	pthread_mutex_unlock(philosopher->fork_left);
	pthread_mutex_unlock(philosopher->fork_right);

	// todo: store 'timestamp of last-eaten' on philosopher
}
