/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 11:55:02 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/03 12:59:46 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_settings	settings;

	if (input_valid(argc, argv) == false)
		return (1);
	store_inputs(argc, argv, &settings);

	// create_cutlery();
	// create_philopher_objects();
	// (create monitoring();)
	// create_thread_per_philopher();
	// wait_for_philosophers();
	// delete_cutlery();

	printf("OK");  // debug
	return (0);
}
