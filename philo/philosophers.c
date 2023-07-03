/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:26:50 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/03 17:18:14 by cherrewi      ########   odam.nl         */
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

t_philosopher	**create_philosophers(t_settings *settings)
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
		i++;
	}
	philosophers[i] = NULL;
	return (philosophers);
}
