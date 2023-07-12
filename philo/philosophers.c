/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:26:50 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/11 16:11:38 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philosophers(t_philosopher **philosophers)
{
	size_t	i;

	if (philosophers == NULL)
		return ;
	i = 0;
	while (philosophers[i] != NULL)
	{
		free(philosophers[i]);
		i++;
	}
	free(philosophers);
}

static t_philosopher	**malloc_philosopher_arr(t_settings *settings)
{
	t_philosopher	**philosophers;

	philosophers = malloc((settings->nr_philo + 1) * sizeof(t_philosopher *));
	if (philosophers == NULL)
	{
		printf("malloc error\n");
		return (NULL);
	}
	return (philosophers);
}

static t_philosopher	*malloc_philosopher(t_philosopher **philosophers)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (philosopher == NULL)
	{
		printf("malloc error\n");
		free_philosophers(philosophers);
		return (NULL);
	}
	return (philosopher);
}

t_philosopher	**create_philosophers(t_data *data, t_settings *settings,
	t_locks *locks)
{
	t_philosopher	**philosophers;
	size_t			i;

	philosophers = malloc_philosopher_arr(settings);
	if (philosophers == NULL)
		return (NULL);
	i = 0;
	while (i < settings->nr_philo)
	{
		philosophers[i] = malloc_philosopher(philosophers);
		if (philosophers[i] == NULL)
			return (NULL);
		philosophers[i]->nr = i + 1;
		philosophers[i]->fork_left = data->forks[i];
		philosophers[i]->fork_right = data->forks[(i + 1) % settings->nr_philo];
		philosophers[i]->settings = settings;
		philosophers[i]->locks = locks;
		philosophers[i]->times_eaten = 0;
		philosophers[i]->last_eaten = settings->start_time;
		i++;
	}
	philosophers[i] = NULL;
	return (philosophers);
}
