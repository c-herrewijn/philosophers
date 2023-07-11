/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 15:34:58 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/11 21:38:49 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	all_done_eating(t_data *data, t_settings *settings, t_locks *locks)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&(locks->settings_lock));
	while (data->philosophers[i] != NULL)
	{
		if (data->philosophers[i]->times_eaten < settings->nr_to_eat)
		{
			pthread_mutex_unlock(&(locks->settings_lock));
			return (false);
		}
		i++;
	}
	pthread_mutex_unlock(&(locks->settings_lock));
	return (true);
}

static bool philo_starved(t_data *data, t_settings *settings, t_locks *locks)
{
	size_t			i;
	size_t			time_to_die;
	size_t			time_of_death;
	struct timeval	now;
	
	time_to_die = settings->time_to_die;
	i = 0;
	gettimeofday(&now, NULL);
	while (data->philosophers[i] != NULL)
	{
		if (calc_ms_passed(&(data->philosophers[i]->last_eaten), &now)
			>= settings->time_to_die)
		{
			time_of_death = calc_ms_passed(&(settings->start_time),
								&(data->philosophers[i]->last_eaten))
							+ settings->time_to_die;
			pthread_mutex_lock(&(locks->settings_lock));
			settings->simul_running = false;
			pthread_mutex_unlock(&(locks->settings_lock));
			pthread_mutex_lock(&(locks->print_lock));
			printf("%5zu %zu died\n", time_of_death, data->philosophers[i]->nr); 
			pthread_mutex_unlock(&(locks->print_lock));
			return (true);
		}
		i++;
	}
	return (false);
}

// stop if all philosophers have eaten enough, or one philo died
void	monitoring(t_data *data, t_settings *settings, t_locks *locks)
{
	struct timeval	now;
	struct timeval	start_time;

	pthread_mutex_lock(&(locks->settings_lock));
	start_time = settings->start_time;
	pthread_mutex_unlock(&(locks->settings_lock));
	while (true)
	{
		if (all_done_eating(data, settings, locks))
		{
			break;
		}
		if (philo_starved(data, settings, locks))
		{
			break;
		}
		gettimeofday(&now, NULL);
		ms_sleep(2, &now, settings, locks);
	}
}
