/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads_launch.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 18:43:34 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/12 20:01:15 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_simul_running(t_settings *settings, t_locks *locks)
{
	bool	simul_running;

	pthread_mutex_lock(&(locks->settings_lock));
	simul_running = settings->simul_running;
	pthread_mutex_unlock(&(locks->settings_lock));
	return (simul_running);
}

void	*thread_function(void *input)
{
	t_philosopher	*philosopher;
	int				nr_to_eat;

	philosopher = (t_philosopher *)input;
	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	nr_to_eat = philosopher->settings->nr_to_eat;
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	while (true)
	{
		pthread_mutex_lock(&(philosopher->locks->settings_lock));
		if (philosopher->times_eaten == nr_to_eat)
		{
			pthread_mutex_unlock(&(philosopher->locks->settings_lock));
			break ;
		}
		pthread_mutex_unlock(&(philosopher->locks->settings_lock));
		if (check_simul_running(philosopher->settings, philosopher->locks))
			philo_eat(philosopher);
		else
			break ;
		if (philosopher->fork_left == philosopher->fork_right)
		{
			while (true)
			{
				if (!check_simul_running(philosopher->settings, philosopher->locks))
					return (NULL);
			}
		}
		if (check_simul_running(philosopher->settings, philosopher->locks))
			philo_sleep(philosopher);
		else
			break ;
		if (check_simul_running(philosopher->settings, philosopher->locks))
			philo_think(philosopher);
		else
			break ;
	}
	return (NULL);
}

int	launch_threads(t_settings *settings, t_philosopher **philosophers,
	pthread_t **threads)
{
	size_t		i;

	i = 0;
	if (gettimeofday(&(settings->start_time), NULL) < 0)
	{
		printf("gettimeofday error");
		return (-1);
	}
	while (i < settings->nr_philo)
	{
		if (pthread_create(threads[i], NULL, thread_function,
				(void *)(philosophers[i])) < 0)
		{
			printf("pthread_create error");
			return (-1);
		}
		i++;
	}
	return (0);
}
