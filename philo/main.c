/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 11:55:02 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/11 12:00:17 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	destroy_and_free_cutlery(data->forks);
	free_philosophers(data->philosophers);
	free_thread_arr(data->threads);
}

static int	init_data(t_data *data, t_settings *settings,
	pthread_mutex_t *settings_lock)
{
	data->philosophers = NULL;
	data->threads = NULL;
	data->forks = create_cutlery(settings);
	if (data->forks == NULL)
		return (-1);
	data->philosophers = create_philosophers(data, settings, settings_lock);
	if (data->philosophers == NULL)
	{
		destroy_and_free_cutlery(data->forks);
		data->forks = NULL;
		return (-1);
	}
	data->threads = create_thread_arr(settings);
	if (data->threads == NULL)
	{
		free_philosophers(data->philosophers);
		data->philosophers = NULL;
		destroy_and_free_cutlery(data->forks);
		data->forks = NULL;
		return (-1);
	}
	return (0);
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

static int	init_lock(pthread_mutex_t *lock)
{
	if (pthread_mutex_init(lock, NULL) < 0)
	{
		printf("problems creating mutex lock\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_settings		settings;
	t_data			data;
	pthread_mutex_t	settings_lock;

	if (input_valid(argc, argv) == false)
		return (1);
	store_inputs(argc, argv, &settings);
	if (init_data(&data, &settings, &settings_lock) < 0)
		return (1);
	if (init_lock(&settings_lock) < 0)
	{
		free_all(&data);
		return (1);
	}
	if (launch_threads(&settings, data.philosophers, data.threads) < 0)
	{
		free_all(&data);
		pthread_mutex_destroy(&settings_lock);
		return (1);
	}
	if (join_threads(data.threads) < 0)
	{
		free_all(&data);
		pthread_mutex_destroy(&settings_lock);
		return (1);
	}
	free_all(&data);
	return (0);
}
