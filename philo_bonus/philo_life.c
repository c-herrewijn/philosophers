/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_life.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 19:03:16 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/27 20:50:28 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	eaten_enough(t_settings *settings, t_philosopher *philosopher)
{
	if (philosopher->times_eaten == settings->nr_to_eat)
		return (true);
	return (false);
}

int	philo_life(t_data *data, t_settings *settings, t_philosopher *philosopher,
	t_locks *locks)
{
	if (eaten_enough(settings, philosopher) == true)
		return (-1);
	philo_think(settings, philosopher, locks);
	while (true)
	{
		philo_eat(data, settings, philosopher, locks);
		if (eaten_enough(settings, philosopher) == true)
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
		usleep(500);
	return (0);
}
