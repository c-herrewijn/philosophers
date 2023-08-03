/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_life.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 19:03:16 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/03 19:20:49 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int philo_eat(t_data *data, t_settings *settings, t_philosopher *philo)
{
	int res;

	(void) settings; // debug 

	// take fork 1
	res = sem_wait(data->sem_forks);
	if (res < 0 && res != EINTR)
	{
		printf("error with sem_wait");
		return (-1);
	}
	printf(" %zu has taken a fork\n", philo->nr);		

	// take fork 1
	res = sem_wait(data->sem_forks);
	if (res < 0 && res != EINTR)
	{
		printf("error with sem_wait");
		return (-1);
	}
	printf(" %zu has taken a fork\n", philo->nr);
	printf(" %zu is eating\n", philo->nr);

	usleep(1000); // dummy

	// puts back forks
	res = sem_post(data->sem_forks);
	res = sem_post(data->sem_forks);
	return (0);
}

int	philo_life(t_data *data, t_settings *settings, t_philosopher *philosopher)
{
	// if (eaten_enough(philosopher) == true || philo_think(philosopher) < 0)
	// 	return ;
	// while (true)
	// {
		// if (eaten_enough(philosopher) == false)
		// {
			if (philo_eat(data, settings, philosopher) < 0)
				return (-1) ;
			// if (philo_sleep(philosopher) < 0)
			// 	break ;
			// if (philo_think(philosopher) < 0)
			// 	break ;
		// }
	// 	else
	// 		break ;
	// }
	return (0);
}
