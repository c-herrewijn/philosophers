/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 11:55:02 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/03 13:51:47 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_settings		settings;
	pthread_mutex_t	*forks;
	t_philosopher	**philosophers;

	if (input_valid(argc, argv) == false)
		return (1);
	store_inputs(argc, argv, &settings);
	if (create_cutlery(&settings, &forks) < 0)
		return (1);
	philosophers = create_philosophers(&settings);
	if (philosophers == NULL)
		return (1);
	// (create monitoring();)
	// create_thread_per_philopher();
	// wait_for_philosophers();
	// delete_cutlery();

	printf("OK");  // debug
	return (0);
}
