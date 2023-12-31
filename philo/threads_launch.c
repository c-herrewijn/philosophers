/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads_launch.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 18:43:34 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/01 11:45:42 by cherrewi      ########   odam.nl         */
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

static bool	eaten_enough(t_philosopher	*philosopher)
{
	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	if (philosopher->times_eaten == philosopher->settings->nr_to_eat)
	{
		pthread_mutex_unlock(&(philosopher->locks->settings_lock));
		return (true);
	}
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	return (false);
}

static int	set_start_time(t_settings *settings, t_philosopher **philosophers)
{
	size_t		i;

	if (gettimeofday(&(settings->start_time), NULL) < 0)
	{
		printf("gettimeofday error");
		return (-1);
	}
	i = 0;
	while (i < settings->nr_philo)
	{
		philosophers[i]->last_eaten = settings->start_time;
		i++;
	}
	return (0);
}

void	*thread_function(void *input)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)input;
	if (eaten_enough(philosopher) == true || philo_think(philosopher) < 0)
		return (NULL);
	while (true)
	{
		if (eaten_enough(philosopher) == false)
		{
			if (philo_eat(philosopher) < 0)
				break ;
			if (philo_sleep(philosopher) < 0)
				break ;
			if (philo_think(philosopher) < 0)
				break ;
		}
		else
			break ;
	}
	return (NULL);
}

// set 'start_time' and init 'last_eaten' before launching threads
int	launch_threads(t_settings *settings, t_philosopher **philosophers,
	pthread_t **threads, t_locks *locks)
{
	size_t		i;

	if (set_start_time(settings, philosophers) < 0)
		return (-1);
	i = 0;
	while (i < settings->nr_philo)
	{
		if (pthread_create(threads[i], NULL, thread_function,
				(void *)(philosophers[i])) < 0)
		{
			pthread_mutex_lock(&(locks->settings_lock));
			settings->simul_running = false;
			pthread_mutex_unlock(&(locks->settings_lock));
			printf("pthread_create error");
			return (-1);
		}
		i++;
	}
	return (0);
}
