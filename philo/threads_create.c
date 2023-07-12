/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads_create.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 18:22:27 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/11 11:06:02 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_thread_arr(pthread_t **threads)
{
	size_t	i;

	if (threads == NULL)
		return ;
	i = 0;
	while (threads[i] != NULL)
	{
		free(threads[i]);
		i++;
	}
	free(threads);
}

pthread_t	**create_thread_arr(t_settings *settings)
{
	pthread_t	**threads;
	size_t		i;

	threads = malloc((settings->nr_philo + 1) * sizeof(pthread_t *));
	if (threads == NULL)
	{
		printf("malloc error\n");
		return (NULL);
	}
	i = 0;
	while (i < settings->nr_philo)
	{
		threads[i] = malloc(sizeof(pthread_t));
		if (threads[i] == NULL)
		{
			printf("malloc error\n");
			free_thread_arr(threads);
			return (NULL);
		}
		i++;
	}
	threads[i] = NULL;
	return (threads);
}
