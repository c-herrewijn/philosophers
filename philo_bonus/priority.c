/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   priority.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 14:30:27 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/29 16:30:39 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
In case of odd nr of philos:
	First half GIVE priority after even nr of eatings (except zero)
	Second half GIVE priority after odd nr of eatings
	Last filo GIVE priority after even nr of eatings
*/
static void	priority_first_round(t_philosopher *philo, t_settings *settings,
	struct timeval *now)
{
	if (settings->nr_philo % 2 == 1 && philo->nr == settings->nr_philo)
		ms_sleep(1 + settings->time_to_eat + settings->time_to_sleep / 2, now);
	else
	{
		if (philo->nr % 2 == 1)
			ms_sleep(1 + settings->time_to_eat / 2, now);
	}
}

// Odd philosophers GIVE priority in the first round
static void	priority_odd_philos(t_philosopher *philo, t_settings *settings,
	struct timeval *now)
{
	if (philo->nr == settings->nr_philo)
	{
		if (philo->times_eaten % 2 == 0)
			ms_sleep(2 + settings->time_to_eat / 2, now);
	}
	else if (philo->nr <= settings->nr_philo / 2)
	{
		if (philo->times_eaten > 0 && (philo->times_eaten % 2) == 0)
			ms_sleep(2 + settings->time_to_eat / 2, now);
	}
	else
	{
		if (philo->times_eaten % 2 == 1)
			ms_sleep(2 + settings->time_to_eat / 2, now);
	}
}

void	give_priority(t_philosopher *philo, t_settings *settings)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (calc_ms_passed(&(settings->start_time), &now) < settings->time_to_eat)
		priority_first_round(philo, settings, &now);
	else if (settings->nr_philo % 2 == 1)
		priority_odd_philos(philo, settings, &now);
}
