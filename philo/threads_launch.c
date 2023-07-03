/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads_launch.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 18:43:34 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/03 19:41:17 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *thread_function(void *input)
{
	t_payload	*payload;

	payload = (t_payload *)input;
	
	// print payload;
	if (payload->philosopher->nr == 2)
		sleep(1);
	printf("total nr. philo: %zu, my nr %zu\n", payload->settings->nr_philo, payload->philosopher->nr);

	return (NULL);
}


int	launch_threads(t_settings *settings, t_philosopher **philosophers, pthread_t **threads)
{
	int			result;
	size_t		i;
	t_payload	payload;

	i = 0;
	payload.settings = settings;
	while (i < settings->nr_philo)
	{
		payload.philosopher = philosophers[i];
		result = pthread_create(threads[i], NULL, thread_function, (void *)(&payload));
		if (result < 0)
		{
			printf("thread creation error");
			return (-1);
			; // todo: error handling
		}
		i++;
	}
	return (0);
}
