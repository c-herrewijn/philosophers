/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep_think.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 17:17:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/13 22:06:43 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philosopher *philosopher)
{
	size_t			time_to_sleep;
	struct timeval	now;
	size_t			timestamp;

	if (check_simul_running(philosopher->settings, philosopher->locks)
		== false)
	{
		return (-1);
	}
	pthread_mutex_lock(&(philosopher->locks->print_lock));
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	timestamp = calc_ms_passed(&(philosopher->settings->start_time), &now);
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	printf("%5zu %zu is sleeping\n", timestamp, philosopher->nr);
	pthread_mutex_unlock(&(philosopher->locks->print_lock));
	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	time_to_sleep = philosopher->settings->time_to_sleep;
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	ms_sleep(time_to_sleep, &now, philosopher->settings, philosopher->locks);
	return (0);
}

int	philo_think(t_philosopher *philosopher)
{
	struct timeval	now;
	size_t			timestamp;

	if (check_simul_running(philosopher->settings, philosopher->locks)
		== false)
	{
		return (-1);
	}
	pthread_mutex_lock(&(philosopher->locks->print_lock));
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	timestamp = calc_ms_passed(&(philosopher->settings->start_time), &now);
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	printf("%5zu %zu is thinking\n", timestamp, philosopher->nr); 
	pthread_mutex_unlock(&(philosopher->locks->print_lock));
	return (0);
}
