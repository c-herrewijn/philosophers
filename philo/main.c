/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 11:55:02 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/03 19:22:19 by cherrewi      ########   odam.nl         */
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
			return (-1);  // todo: check error handling
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_settings		settings;
	pthread_mutex_t	**forks;
	t_philosopher	**philosophers;
	pthread_t		**threads;

	if (input_valid(argc, argv) == false)
		return (1);
	store_inputs(argc, argv, &settings);
	forks = create_cutlery(&settings);
	if (forks == NULL)
		return (1);	// todo: free all data
	philosophers = create_philosophers(&settings, forks);
	if (philosophers == NULL)
		return (1); // todo: free all data
	threads = create_thread_arr(&settings);
	if (threads == NULL)
		return (1); // todo: free all data
	if (launch_threads(&settings, philosophers, threads) < 0)
		return (1); // todo: free all data

	join_threads(threads);
		

	// threads = create_threads(&settings, forks, philosophers);
		

	// debug:
	// size_t i;
	// i = 0;
	// while (i < settings.nr_philo)
	// {
	// 	printf("nr: %zu, left fork: %p, right fork: %p\n", 
	// 		philosophers[i]->nr,
	// 		philosophers[i]->fork_left,
	// 		philosophers[i]->fork_right);
	// 	i++;
	// }

	// (create monitoring();)
	// create_thread_per_philopher();
	// wait_for_philosophers();
	// free_cutlery();
	// free_philosophers();

	printf("OK");  // debug
	return (0);
}
