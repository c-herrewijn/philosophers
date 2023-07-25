/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 17:29:51 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/25 18:09:08 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// odd philosophers have priority in the first round
static void	give_priority(t_philosopher *philosopher)
{
	int				times_eaten;
	size_t			philo_nr;
	size_t			time_to_eat;
	struct timeval	now;

	times_eaten = philosopher->times_eaten;
	philo_nr = philosopher->nr;
	time_to_eat = philosopher->settings->time_to_eat;
	if (times_eaten == 0 && philo_nr % 2 == 0)
	{
		gettimeofday(&now, NULL);
		ms_sleep(1 + time_to_eat / 2, &now, philosopher->settings,
			philosopher->locks);
	}
}

static int	take_fork_left(t_philosopher *philosopher)
{
	struct timeval	now;
	size_t			timestamp;

	pthread_mutex_lock(philosopher->fork_left);
	if (check_simul_running(philosopher->settings, philosopher->locks)
		== false)
	{
		pthread_mutex_unlock(philosopher->fork_left);
		return (-1);
	}
	pthread_mutex_lock(&(philosopher->locks->print_lock));
	gettimeofday(&now, NULL);
	timestamp = calc_ms_passed(&(philosopher->settings->start_time), &now);
	printf("%5zu %zu has taken a fork\n", timestamp, philosopher->nr);
	pthread_mutex_unlock(&(philosopher->locks->print_lock));
	return (0);
}

static int	take_fork_right(t_philosopher *philosopher, size_t time_to_eat)
{
	struct timeval	now;
	size_t			timestamp;

	pthread_mutex_lock(philosopher->fork_right);
	if (check_simul_running(philosopher->settings, philosopher->locks)
		== false)
	{
		pthread_mutex_unlock(philosopher->fork_left);
		pthread_mutex_unlock(philosopher->fork_right);
		return (-1);
	}
	pthread_mutex_lock(&(philosopher->locks->print_lock));
	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	gettimeofday(&now, NULL);
	timestamp = calc_ms_passed(&(philosopher->settings->start_time), &now);
	philosopher->times_eaten += 1;
	philosopher->last_eaten = now;
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	printf("%5zu %zu has taken a fork\n", timestamp, philosopher->nr);
	printf("%5zu %zu is eating\n", timestamp, philosopher->nr); 
	pthread_mutex_unlock(&(philosopher->locks->print_lock));
	ms_sleep(time_to_eat, &now, philosopher->settings, philosopher->locks);
	pthread_mutex_unlock(philosopher->fork_left);
	pthread_mutex_unlock(philosopher->fork_right);
	return (0);
}

// if single philosopher: wait till simul ends (i.e. philo starves)
static void	single_philo(t_philosopher *philosopher)
{
	if (take_fork_left(philosopher) < 0)
		return ;
	while (true)
	{
		if (!check_simul_running(philosopher->settings, philosopher->locks))
		{
			usleep(500);
			break ;
		}
	}
	pthread_mutex_unlock(philosopher->fork_left);
}

int	philo_eat(t_philosopher *philosopher)
{
	bool	is_single_philo;
	size_t	time_to_eat;
	size_t	times_eaten;

	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	is_single_philo = (philosopher->fork_left == philosopher->fork_right);
	time_to_eat = philosopher->settings->time_to_eat;
	times_eaten = philosopher->times_eaten;
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	if (times_eaten == 0)
		give_priority(philosopher);
	if (is_single_philo)
	{
		single_philo(philosopher);
		return (-1);
	}
	else
	{
		if (take_fork_left(philosopher) < 0)
			return (-1);
		if (take_fork_right(philosopher, time_to_eat) < 0)
			return (-1);
	}
	return (0);
}
