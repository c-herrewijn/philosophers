/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cutlery.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 13:02:52 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/11 11:05:44 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_and_free_cutlery(pthread_mutex_t **forks)
{
	size_t	i;

	if (forks == NULL)
		return ;
	i = 0;
	while (forks[i] != NULL)
	{
		if (pthread_mutex_destroy(forks[i]) < 0)
			printf("problems destroying mutex lock for fork nr: %zu\n", i);
		free(forks[i]);
		i++;
	}
	free(forks);
}

static void	free_cutlery(pthread_mutex_t **forks)
{
	size_t	i;

	if (forks == NULL)
		return ;
	i = 0;
	while (forks[i] != NULL)
	{
		free(forks[i]);
		i++;
	}
	free(forks);
}

static int	initiate_mutex(pthread_mutex_t **forks, size_t i)
{
	if (pthread_mutex_init(forks[i], NULL) < 0)
	{
		printf("problems creating mutex lock\n");
		free(forks[i]);
		forks[i] = NULL;
		destroy_and_free_cutlery(forks);
		return (-1);
	}
	return (0);
}

// the forks philosophers use to eat are implemented as mutex locks 
pthread_mutex_t	**create_cutlery(t_settings *settings)
{
	pthread_mutex_t	**forks;
	size_t			i;

	forks = malloc((settings->nr_philo + 1) * sizeof(pthread_mutex_t *));
	if (forks == NULL)
	{
		printf("malloc error\n");
		return (NULL);
	}
	i = 0;
	while (i < settings->nr_philo)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (forks[i] == NULL)
		{
			printf("malloc error\n");
			free_cutlery(forks);
			return (NULL);
		}
		if (initiate_mutex(forks, i) < 0)
			return (NULL);
		i++;
	}
	forks[i] = NULL;
	return (forks);
}
