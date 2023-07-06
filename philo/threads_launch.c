/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads_launch.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 18:43:34 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/06 17:54:46 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *thread_function(void *input)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)input;
	eat(philosopher);
	// todo: sleep (+ think)
	return (NULL);
}

int	launch_threads(t_settings *settings, t_philosopher **philosophers, pthread_t **threads)
{
	int			result;
	size_t		i;

	i = 0;
	while (i < settings->nr_philo)
	{
		result = pthread_create(threads[i], NULL, thread_function, (void *)(philosophers[i]));
		if (result < 0)
		{
			printf("thread creation error");
			return (-1);
			// todo: error handling
		}
		i++;
	}
	return (0);
}
