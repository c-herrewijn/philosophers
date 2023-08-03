/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 15:54:44 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/03 19:23:59 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_semaphore(char *sem_name, size_t value, sem_t **sem)
{
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, value);
	if (*sem == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			if (sem_unlink(sem_name) < 0)
				return (-1);
			*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, value);
			if (*sem == SEM_FAILED)
				return (-1);
			else
				return (0);
		}
	}
	return (0);
}

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
			if (philo_life(data, settings, data->philosophers[i]) < 0)
				exit(1);
			else
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
	if (data->philosophers == NULL)
		return (-1);
	if (create_semaphore(NAME_SEM_FORKS, settings->nr_philo,
			&(data->sem_forks)) < 0)
	{
		printf("error creating semaphore");
		return (-1);
	}
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
