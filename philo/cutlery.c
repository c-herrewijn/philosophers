/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cutlery.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 13:02:52 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/03 13:50:13 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// the forks philosophers use to eat are implemented as mutex locks 
int	create_cutlery(t_settings *settings, pthread_mutex_t **forks)
{
	size_t	i;
	size_t	j;

	*forks = malloc(settings->nr_philo * sizeof(pthread_mutex_t));
	if (*forks == NULL)
		return (-1);
	i = 0;
	while (i < settings->nr_philo)
	{
		if (pthread_mutex_init(&(*forks)[i], NULL) < 0)
		{
			j = 0;
			while (j < i)
			{
				if (pthread_mutex_destroy(forks[i]) < 0)
					printf("problems destroying mutex lock nr: %zu\n", j);
				j++;
			}
			free(*forks);
			return (-1);
		}
		i++;
	}
	return (0);
}
