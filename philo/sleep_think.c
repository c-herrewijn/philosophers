/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep_think.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 17:17:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/31 21:14:05 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philosopher *philo)
{
	size_t			time_to_sleep;
	struct timeval	now;

	pthread_mutex_lock(&(philo->locks->print_lock));
	if (check_simul_running(philo->settings, philo->locks)
		== false)
	{
		pthread_mutex_unlock(&(philo->locks->print_lock));
		return (-1);
	}
	gettimeofday(&now, NULL);
	print_timestamp(&(philo->settings->start_time), &now, philo->nr);
	printf(" %zu is sleeping\n", philo->nr);
	pthread_mutex_unlock(&(philo->locks->print_lock));
	time_to_sleep = philo->settings->time_to_sleep;
	ms_sleep(time_to_sleep, &now, philo->settings, philo->locks);
	return (0);
}

int	philo_think(t_philosopher *philo)
{
	struct timeval	now;

	pthread_mutex_lock(&(philo->locks->print_lock));
	if (check_simul_running(philo->settings, philo->locks)
		== false)
	{
		pthread_mutex_unlock(&(philo->locks->print_lock));
		return (-1);
	}
	gettimeofday(&now, NULL);
	print_timestamp(&(philo->settings->start_time), &now, philo->nr);
	printf(" %zu is thinking\n", philo->nr);
	pthread_mutex_unlock(&(philo->locks->print_lock));
	return (0);
}
