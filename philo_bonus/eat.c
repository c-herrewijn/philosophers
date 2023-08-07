/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 16:28:42 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/07 21:25:15 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int take_first_fork(t_data *data, t_settings *settings,
	t_philosopher *philo, t_locks *locks)
{
	struct timeval	now;

	sem_wait(data->sem_forks);
	sem_wait(locks->print_lock);
	if (check_simul_running(settings, locks) == false)
	{
		sem_post(locks->print_lock);
		sem_post(data->sem_forks);
		return (-1);
	}
	gettimeofday(&now, NULL);
	print_timestamp(&(settings->start_time), &now, philo->nr);
	printf(" %zu has taken a fork\n", philo->nr);
	sem_post(locks->print_lock);
	return (0);
}

static int take_second_fork(t_data *data, t_settings *settings,
	t_philosopher *philo, t_locks *locks)
{
	struct timeval	now;

	sem_wait(data->sem_forks);
	sem_wait(locks->print_lock);
	if (check_simul_running(settings, locks)
		== false)
	{
		sem_post(locks->print_lock);
		sem_post(data->sem_forks);
		sem_post(data->sem_forks);
		return (-1);
	}
	sem_wait(locks->settings_lock);
	gettimeofday(&now, NULL);
	philo->times_eaten += 1;
	philo->last_eaten = now;
	sem_post(locks->settings_lock);
	print_timestamp(&(settings->start_time), &now, philo->nr);
	printf(" %zu has taken a fork\n", philo->nr);
	print_timestamp(&(settings->start_time), &now, philo->nr);
	printf(" %zu is eating\n", philo->nr);
	sem_post(locks->print_lock);
	ms_sleep(settings->time_to_eat, &now, settings, locks);
	return (0);
}

// if single philosopher: wait till simul ends (i.e. philo starves)
static void	single_philo(t_data *data, t_settings *settings,
	t_philosopher *philo, t_locks *locks)
{
	if (take_first_fork(data, settings, philo, locks) < 0)
		return ;
	while (true)
	{
		if (!check_simul_running(settings, locks))
		{
			usleep(500);
			break ;
		}
	}
	sem_post(data->sem_forks);
}

int philo_eat(t_data *data, t_settings *settings, t_philosopher *philo,
	t_locks *locks)
{
	if (settings->nr_philo == 1)
	{
		single_philo(data, settings, philo, locks); // todo!
		return (-1);
	}
	else
	{
		if (take_first_fork(data, settings, philo, locks) < 0)
		{
			puts("debug 01?");
			return (-1);
		}
		if (take_second_fork(data, settings, philo, locks) < 0)
		{
			puts("debug 02?");
			return (-1);
		}
	}
	return (0);
}
