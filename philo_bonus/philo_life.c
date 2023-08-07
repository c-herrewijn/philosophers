/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_life.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 19:03:16 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/07 21:27:50 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	check_simul_running(t_settings *settings, t_locks *locks)
{
	bool	simul_running;

	sem_wait(locks->settings_lock);
	simul_running = settings->simul_running;
	sem_post(locks->settings_lock);
	return (simul_running);
}

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

int	philo_life(t_data *data, t_settings *settings, t_philosopher *philosopher, t_locks *locks)
{
	// if (eaten_enough(philosopher) == true || philo_think(philosopher) < 0)
	// 	return ;
	while (true)
	{
		if (eaten_enough(settings, philosopher, locks) == false)
		{
			if (philo_eat(data, settings, philosopher, locks) < 0)
				return (-1);
			if (philo_sleep(data, settings, philosopher, locks) < 0)
				break ;
			if (philo_think(settings, philosopher, locks) < 0)
				break ;
		}
		else
			break ;
	}
	return (0);
}
