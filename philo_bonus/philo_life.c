/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_life.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 19:03:16 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/16 20:19:39 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	eaten_enough(t_settings *settings, t_philosopher *philosopher,
			t_locks *locks)
{
	sem_wait(locks->settings_lock);
	if (philosopher->times_eaten == settings->nr_to_eat)
	{
		sem_post(locks->settings_lock);
		return (true);
	}
	sem_post(locks->settings_lock);
	return (false);
}

int	philo_life(t_data *data, t_settings *settings, t_philosopher *philosopher,
	t_locks *locks)
{
	if (eaten_enough(settings, philosopher, locks) == true)
		return (-1);
	philo_think(settings, philosopher, locks);
	while (true)
	{
		philo_eat(data, settings, philosopher, locks);
		if (eaten_enough(settings, philosopher, locks) == true)
		{
			sem_post(locks->all_eaten);
			sem_post(data->sem_forks);
			sem_post(data->sem_forks);
			break ;
		}
		philo_sleep(data, settings, philosopher, locks);
		philo_think(settings, philosopher, locks);
	}
	while (true)
		;
	return (0);
}
