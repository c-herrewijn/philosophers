/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 15:54:44 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/03 18:41:24 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	launch_philo_processes(t_data *data, t_settings *settings)
{
	size_t	i;
	pid_t	new_pid;

	i = 0;
	while (i < settings->nr_philo)
	{
		new_pid = fork();
		if (new_pid == 0)
		{
			printf("philo nr: %zu is alive!\n", data->philosophers[i]->nr);
			exit(0);
		}
		data->philosophers[i]->pid = new_pid;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, t_settings *settings)
{
	data->philosophers = NULL;
	data->philosophers = create_philosophers(settings);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_settings	settings;
	t_data		data;

	if (parse_input(argc, argv, &settings) < 0)
		return (1);
	init_data(&data, &settings);
	launch_philo_processes(&data, &settings);
	return (0);
}
