/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   priority.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 14:30:27 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/29 18:45:50 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	priority_even_philos(t_philosopher *philo, t_settings *settings,
	struct timeval *now)
{
	if (calc_ms_passed(&(settings->start_time), now) < settings->time_to_eat)
	{
		if (philo->nr % 2 == 0)
			ms_sleep(settings->time_to_eat, now);
	}
}

/*
Odd philosophers GIVE priority in the first round
First half GIVE priority after even nr of eatings (except zero)
Second half GIVE priority after odd nr of eatings
Last filo GIVE priority after even nr of eatings
*/
static void	priority_odd_philos(t_philosopher *philo, t_settings *set,
	struct timeval *now)
{
	if (calc_ms_passed(&(set->start_time), now) < set->time_to_eat)
	{
		if (philo->nr == set->nr_philo)
			ms_sleep(1 + set->time_to_eat + set->time_to_sleep / 2, now);
		else if (philo->nr % 2 == 1)
			ms_sleep(1 + set->time_to_eat / 2, now);
	}
	else
	{
		if (philo->nr == set->nr_philo)
		{
			if (philo->times_eaten % 2 == 0)
				ms_sleep(2 + set->time_to_eat / 2, now);
		}
		else if (philo->nr <= set->nr_philo / 2)
		{
			if (philo->times_eaten > 0 && (philo->times_eaten % 2) == 0)
				ms_sleep(2 + set->time_to_eat / 2, now);
		}
		else
		{
			if (philo->times_eaten % 2 == 1)
				ms_sleep(2 + set->time_to_eat / 2, now);
		}
	}
}

void	give_priority(t_philosopher *philo, t_settings *settings)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (settings->nr_philo % 2 == 1)
		priority_odd_philos(philo, settings, &now);
	else
		priority_even_philos(philo, settings, &now);
}
