/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads_launch.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 18:43:34 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/06 21:43:16 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_function(void *input)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)input;
	eat(philosopher);
	return (NULL);
}

int	launch_threads(t_settings *settings, t_philosopher **philosophers,
	pthread_t **threads)
{
	size_t		i;

	i = 0;
	if (gettimeofday(&(settings->start_time), NULL) < 0)
	{
		printf("gettimeofday error");
		return (-1);
	}
	while (i < settings->nr_philo)
	{
		if (pthread_create(threads[i], NULL, thread_function,
				(void *)(philosophers[i])) < 0)
		{
			printf("pthread_create error");
			return (-1);
		}
		i++;
	}
	return (0);
}
