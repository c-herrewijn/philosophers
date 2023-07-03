/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 11:55:02 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/03 16:54:55 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_settings		settings;
	pthread_mutex_t	**forks;
	t_philosopher	**philosophers;

	if (input_valid(argc, argv) == false)
		return (1);
	store_inputs(argc, argv, &settings);
	forks = create_cutlery(&settings);
	if (forks == NULL)
		return (1);
	philosophers = create_philosophers(&settings);
	if (philosophers == NULL)
		return (1);

	// debug:
	size_t i;
	i = 0;
	while (i < settings.nr_philo)
	{
		printf("nr: %zu\n", philosophers[i]->nr);
		i++;
	}

	// (create monitoring();)
	// create_thread_per_philopher();
	// wait_for_philosophers();
	// free_cutlery();
	// free_philosophers();

	printf("OK");  // debug
	return (0);
}
