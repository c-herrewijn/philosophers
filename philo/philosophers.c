/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:26:50 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/03 17:32:26 by cherrewi      ########   odam.nl         */
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

t_philosopher	**create_philosophers(t_settings *settings,
	pthread_mutex_t	**forks)
{
	t_philosopher	**philosophers;
	size_t			i;

	philosophers = malloc((settings->nr_philo + 1) * sizeof(t_philosopher *));
	if (philosophers == NULL)
	{
		printf("malloc error\n");
		return (NULL);
	}
	i = 0;
	while (i < settings->nr_philo)
	{
		philosophers[i] = malloc(sizeof(t_philosopher));
		if (philosophers[i] == NULL)
		{
			printf("malloc error\n");
			free_philosophers(philosophers);
			return (NULL);
		}
		philosophers[i]->nr = i + 1;
		philosophers[i]->fork_left = forks[i];
		philosophers[i]->fork_right = forks[(i + 1) % settings->nr_philo];
		i++;
	}
	philosophers[i] = NULL;
	return (philosophers);
}
