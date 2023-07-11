/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 11:55:02 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/11 20:44:43 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutex_locks(t_locks *locks)
{
	pthread_mutex_destroy(&(locks->print_lock));
	pthread_mutex_destroy(&(locks->settings_lock));
}

void	free_all(t_data *data, t_locks *locks)
{
	destroy_and_free_cutlery(data->forks);
	free_philosophers(data->philosophers);
	free_thread_arr(data->threads);
	destroy_mutex_locks(locks);
}

// NOTE: overall start_time need to be set before the philosophers are created.
static int	init_data(t_data *data, t_settings *settings,
	t_locks *locks)
{
	gettimeofday(&(settings->start_time), NULL);
	data->philosophers = NULL;
	data->threads = NULL;
	data->forks = create_cutlery(settings);
	if (data->forks == NULL)
		return (-1);
	data->philosophers = create_philosophers(data, settings, locks);
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
	settings->simul_running = true;
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

static int	init_locks(t_locks *locks)
{
	if (pthread_mutex_init(&(locks->print_lock), NULL) < 0)
	{
		printf("problems creating mutex lock\n");
		return (-1);
	}
	if (pthread_mutex_init(&(locks->settings_lock), NULL) < 0)
	{
		pthread_mutex_destroy(&(locks->print_lock));
		printf("problems creating mutex lock\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_settings		settings;
	t_data			data;
	t_locks			locks;

	if (input_valid(argc, argv) == false)
		return (1);
	store_inputs(argc, argv, &settings);
	if (init_locks(&locks) < 0)
		return (1);
	if (init_data(&data, &settings, &locks) < 0)
	{
		destroy_mutex_locks(&locks);
		return (1);
	}
	if (launch_threads(&settings, data.philosophers, data.threads) < 0)
	{
		free_all(&data, &locks);
		return (1);
	}
	monitoring(&data, &settings, &locks);
	if (join_threads(data.threads) < 0)
	{
		free_all(&data, &locks);
		return (1);
	}
	free_all(&data, &locks);
	return (0);
}
