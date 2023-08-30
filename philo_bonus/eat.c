/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 16:28:42 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/29 16:13:54 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_first_fork(t_data *data, t_settings *settings,
	t_philosopher *philo, t_locks *locks)
{
	struct timeval	now;

	sem_wait(data->sem_forks);
	sem_wait(locks->print_lock);
	gettimeofday(&now, NULL);
	print_timestamp(&(settings->start_time), &now, philo->nr);
	printf(" %zu has taken a fork\n", philo->nr);
	sem_post(locks->print_lock);
}

static void	take_second_fork(t_data *data, t_settings *settings,
	t_philosopher *philo, t_locks *locks)
{
	struct timeval	now;

	sem_wait(data->sem_forks);
	sem_wait(locks->print_lock);
	gettimeofday(&now, NULL);
	philo->times_eaten += 1;
	philo->last_eaten = now;
	print_timestamp(&(settings->start_time), &now, philo->nr);
	printf(" %zu has taken a fork\n", philo->nr);
	print_timestamp(&(settings->start_time), &now, philo->nr);
	printf(" %zu is eating\n", philo->nr);
	sem_post(locks->print_lock);
	ms_sleep(settings->time_to_eat, &now);
}

// if single philosopher: wait till simul ends (i.e. philo starves)
static void	single_philo(t_data *data, t_settings *settings,
	t_philosopher *philo, t_locks *locks)
{
	take_first_fork(data, settings, philo, locks);
	while (true)
		usleep(500);
}

void	philo_eat(t_data *data, t_settings *settings, t_philosopher *philo,
	t_locks *locks)
{
	size_t	times_eaten;

	times_eaten = philo->times_eaten;
	if (settings->nr_philo == 1)
		single_philo(data, settings, philo, locks);
	give_priority(philo, settings);
	take_first_fork(data, settings, philo, locks);
	take_second_fork(data, settings, philo, locks);
}
