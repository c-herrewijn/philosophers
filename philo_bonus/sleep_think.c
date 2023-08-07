/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep_think.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 16:28:46 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/07 21:29:17 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_sleep(t_data *data, t_settings *settings,
	t_philosopher *philo, t_locks *locks)
{
	size_t			time_to_sleep;
	struct timeval	now;

	sem_wait(locks->print_lock);
	if (check_simul_running(settings, locks)
		== false)
	{
		sem_post(data->sem_forks);
		sem_post(data->sem_forks);
		sem_post(locks->print_lock);
		return (-1);
	}
	gettimeofday(&now, NULL);
	print_timestamp(&(settings->start_time), &now, philo->nr);
	printf(" %zu is sleeping\n", philo->nr);
	sem_post(data->sem_forks);
	sem_post(data->sem_forks);
	sem_post(locks->print_lock);
	time_to_sleep = settings->time_to_sleep;
	ms_sleep(time_to_sleep, &now, settings, locks);
	return (0);
}

int	philo_think(t_settings *settings, t_philosopher *philo, t_locks *locks)
{
	struct timeval	now;

	sem_wait(locks->print_lock);
	if (check_simul_running(settings, locks)
		== false)
	{
		sem_post(locks->print_lock);
		return (-1);
	}
	gettimeofday(&now, NULL);
	print_timestamp(&(settings->start_time), &now, philo->nr);
	printf(" %zu is thinking\n", philo->nr);
	sem_post(locks->print_lock);
	return (0);
}
