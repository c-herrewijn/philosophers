/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 15:34:58 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/30 15:16:44 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_oldest_last_eaten_time(t_data *data, long int *last_eaten_sec,
	int *last_eaten_usec)
{
	size_t		i;

	*last_eaten_sec = data->philosophers[0]->last_eaten.tv_sec;
	*last_eaten_usec = data->philosophers[0]->last_eaten.tv_usec;
	i = 0;
	while (data->philosophers[i] != NULL)
	{
		if (data->philosophers[i]->last_eaten.tv_sec < *last_eaten_sec)
		{
			*last_eaten_sec = data->philosophers[i]->last_eaten.tv_sec;
			*last_eaten_usec = data->philosophers[i]->last_eaten.tv_usec;
		}
		if (data->philosophers[i]->last_eaten.tv_usec < *last_eaten_usec
			&& data->philosophers[i]->last_eaten.tv_sec <= *last_eaten_sec)
			*last_eaten_usec = data->philosophers[i]->last_eaten.tv_usec;
		i++;
	}
}

static void	print_philo_died(t_data *data, t_settings *settings, t_locks *locks,
	struct timeval *now)
{
	size_t		i;
	long int	last_eaten_sec;
	int			last_eaten_usec;

	pthread_mutex_lock(&(locks->print_lock));
	pthread_mutex_lock(&(locks->settings_lock));
	settings->simul_running = false;
	set_oldest_last_eaten_time(data, &last_eaten_sec, &last_eaten_usec);
	i = 0;
	while (true)
	{
		if (data->philosophers[i]->last_eaten.tv_sec == last_eaten_sec
			&& data->philosophers[i]->last_eaten.tv_usec == last_eaten_usec)
		{
			gettimeofday(now, NULL);
			print_timestamp(&(settings->start_time), now,
				data->philosophers[i]->nr);
			printf(" %zu died\n", data->philosophers[i]->nr);
			pthread_mutex_unlock(&(locks->settings_lock));
			pthread_mutex_unlock(&(locks->print_lock));
			break ;
		}
		i++;
	}
}

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
	settings->simul_running = false;
	pthread_mutex_unlock(&(locks->settings_lock));
	return (true);
}

static bool	philo_starved(t_data *data, t_settings *settings, t_locks *locks)
{
	size_t			i;
	size_t			time_to_die;
	struct timeval	now;
	struct timeval	last_eaten;

	time_to_die = settings->time_to_die;
	i = 0;
	gettimeofday(&now, NULL);
	while (data->philosophers[i] != NULL)
	{
		pthread_mutex_lock(&(locks->settings_lock));
		last_eaten = data->philosophers[i]->last_eaten;
		pthread_mutex_unlock(&(locks->settings_lock));
		if (calc_ms_passed(&last_eaten, &now) >= time_to_die)
		{
			print_philo_died(data, settings, locks, &now);
			return (true);
		}
		i++;
	}
	return (false);
}

// stop if all philosophers have eaten enough, or one philo died
void	monitoring(t_data *data, t_settings *settings, t_locks *locks)
{
	struct timeval	start_time;
	int				nr_to_eat;

	start_time = settings->start_time;
	nr_to_eat = settings->nr_to_eat;
	while (true)
	{
		if (nr_to_eat != -1 && all_done_eating(data, settings, locks))
			break ;
		if (philo_starved(data, settings, locks))
			break ;
		usleep(200);
	}
}
