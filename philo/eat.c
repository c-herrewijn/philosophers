/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 17:29:51 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/31 20:13:00 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// odd philosophers have priority in the first round
static void	give_priority(t_philosopher *philo)
{
	int				times_eaten;
	size_t			philo_nr;
	size_t			time_to_eat;
	struct timeval	now;

	times_eaten = philo->times_eaten;
	philo_nr = philo->nr;
	time_to_eat = philo->settings->time_to_eat;
	if (times_eaten == 0 && philo_nr % 2 == 0)
	{
		gettimeofday(&now, NULL);
		ms_sleep(1 + time_to_eat / 2, &now, philo->settings,
			philo->locks);
	}
}

static int	take_fork_left(t_philosopher *philo)
{
	struct timeval	now;

	pthread_mutex_lock(philo->fork_left);
	if (check_simul_running(philo->settings, philo->locks)
		== false)
	{
		pthread_mutex_unlock(philo->fork_left);
		return (-1);
	}
	pthread_mutex_lock(&(philo->locks->print_lock));
	gettimeofday(&now, NULL);
	print_timestamp(&(philo->settings->start_time), &now, philo->nr);
	printf(" %zu has taken a fork\n", philo->nr);
	pthread_mutex_unlock(&(philo->locks->print_lock));
	return (0);
}

static int	take_fork_right(t_philosopher *philo, size_t time_to_eat)
{
	struct timeval	now;

	pthread_mutex_lock(philo->fork_right);
	if (check_simul_running(philo->settings, philo->locks)
		== false)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (-1);
	}
	pthread_mutex_lock(&(philo->locks->print_lock));
	pthread_mutex_lock(&(philo->locks->settings_lock));
	gettimeofday(&now, NULL);
	philo->times_eaten += 1;
	philo->last_eaten = now;
	pthread_mutex_unlock(&(philo->locks->settings_lock));
	print_timestamp(&(philo->settings->start_time), &now, philo->nr);
	printf(" %zu has taken a fork\n", philo->nr);
	print_timestamp(&(philo->settings->start_time), &now, philo->nr);
	printf(" %zu is eating\n", philo->nr);
	pthread_mutex_unlock(&(philo->locks->print_lock));
	ms_sleep(time_to_eat, &now, philo->settings, philo->locks);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

// if single philosopher: wait till simul ends (i.e. philo starves)
static void	single_philo(t_philosopher *philo)
{
	if (take_fork_left(philo) < 0)
		return ;
	while (true)
	{
		if (!check_simul_running(philo->settings, philo->locks))
		{
			usleep(500);
			break ;
		}
	}
	pthread_mutex_unlock(philo->fork_left);
}

int	philo_eat(t_philosopher *philo)
{
	bool	is_single_philo;
	size_t	time_to_eat;
	size_t	times_eaten;

	pthread_mutex_lock(&(philo->locks->settings_lock));
	is_single_philo = (philo->fork_left == philo->fork_right);
	time_to_eat = philo->settings->time_to_eat;
	times_eaten = philo->times_eaten;
	pthread_mutex_unlock(&(philo->locks->settings_lock));
	if (times_eaten == 0)
		give_priority(philo);
	if (is_single_philo)
	{
		single_philo(philo);
		return (-1);
	}
	else
	{
		if (take_fork_left(philo) < 0)
			return (-1);
		if (take_fork_right(philo, time_to_eat) < 0)
			return (-1);
	}
	return (0);
}
