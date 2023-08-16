/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 16:28:42 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/16 20:20:50 by cherrewi      ########   odam.nl         */
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
	ms_sleep(settings->time_to_eat, &now);
}

// if single philosopher: wait till simul ends (i.e. philo starves)
static void	single_philo(t_data *data, t_settings *settings,
	t_philosopher *philo, t_locks *locks)
{
	// to test!
	take_first_fork(data, settings, philo, locks);
	while (true)
		;
}

// odd philosophers have priority in the first round
static void	give_priority(t_philosopher *philo, t_settings *settings)
{
	int				times_eaten;
	size_t			philo_nr;
	size_t			time_to_eat;
	struct timeval	now;

	times_eaten = philo->times_eaten;
	philo_nr = philo->nr;
	time_to_eat = settings->time_to_eat;
	if (times_eaten == 0 && philo_nr % 2 == 0)
	{
		gettimeofday(&now, NULL);
		ms_sleep(1 + time_to_eat / 2, &now);
	}
}

void	philo_eat(t_data *data, t_settings *settings, t_philosopher *philo,
	t_locks *locks)
{
	size_t	times_eaten;

	sem_wait(locks->settings_lock);
	times_eaten = philo->times_eaten;
	sem_post(locks->settings_lock);
	if (times_eaten == 0)
		give_priority(philo, settings);
	if (settings->nr_philo == 1)
		single_philo(data, settings, philo, locks);
	else
	{
		take_first_fork(data, settings, philo, locks);
		take_second_fork(data, settings, philo, locks);
	}
}
