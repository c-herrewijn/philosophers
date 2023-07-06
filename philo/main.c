/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 11:55:02 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/06 21:50:41 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(pthread_t **threads)
{
	size_t	i;

	i = 0;
	while (threads[i] != NULL)
	{
		if (pthread_join(*(threads[i]), NULL) < 0)
		{
			printf("error joining threads");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_settings		settings;
	pthread_mutex_t	settings_lock;
	pthread_mutex_t	**forks;
	t_philosopher	**philosophers;
	pthread_t		**threads;

	if (input_valid(argc, argv) == false)
		return (1);
	store_inputs(argc, argv, &settings);
	forks = create_cutlery(&settings);
	if (forks == NULL)
		return (1);
	philosophers = create_philosophers(&settings, forks, &settings_lock);
	if (philosophers == NULL)
		return (1);
	pthread_mutex_init(&settings_lock, NULL);
	threads = create_thread_arr(&settings);
	if (threads == NULL)
		return (1);
	if (launch_threads(&settings, philosophers, threads) < 0)
		return (1);
	join_threads(threads);
	return (0);
}
