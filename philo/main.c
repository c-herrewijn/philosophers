/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 11:55:02 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/07 16:49:28 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	destroy_and_free_cutlery(data->forks);
	free_philosophers(data->philosophers);
	free_thread_arr(data->threads);
}

// put all pointer variables to NULL, for better error handling
static void	init_data(t_data *data)
{
	data->forks = NULL;
	data->philosophers = NULL;
	data->threads = NULL;
}

static int	join_threads(pthread_t **threads)
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
	t_data			data;

	if (input_valid(argc, argv) == false)
		return (1);
	store_inputs(argc, argv, &settings);
	init_data(&data);
	data.forks = create_cutlery(&data, &settings);
	if (data.forks == NULL)
		return (1);
	data.philosophers = create_philosophers(&data, &settings, &settings_lock);
	if (data.philosophers == NULL)
		return (1);
	data.threads = create_thread_arr(&data, &settings);
	if (data.threads == NULL)
		return (1);
	
	pthread_mutex_init(&settings_lock, NULL);
	if (launch_threads(&settings, data.philosophers, data.threads) < 0)
		return (1);
	join_threads(data.threads);
	free_all(&data);
	return (0);
}
