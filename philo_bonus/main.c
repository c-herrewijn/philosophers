/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 15:54:44 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/10 16:06:51 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	wait_philo_processes(t_settings *settings, t_philosopher **philos)
{
	size_t	i;
	pid_t	return_pid;
	int		stat_loc;

	i = 0;
	while (i < settings->nr_philo)
	{
		return_pid = waitpid(philos[i]->pid, &stat_loc, 0);
		if (return_pid == -1)
		{
			perror(NULL);
			return (-1);
		}
		if (WEXITSTATUS(stat_loc) != 0)
		{
			printf("philosopher process exited with status: %d\n",
				WEXITSTATUS(stat_loc));
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	init_data(t_data *data, t_settings *settings, t_locks *locks)
{
	data->philosophers = NULL;
	data->philosophers = create_philosophers(settings);
	if (data->philosophers == NULL)
		return (-1);
	if (create_semaphores(data, settings, locks) < 0)
	{
		free_philosophers(data->philosophers);
		data->philosophers = NULL;
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_settings	settings;
	t_data		data;
	t_locks		locks;

	setbuf(stdout, NULL); // debug only, to write to file in order
	if (parse_input(argc, argv, &settings) < 0)
		return (1);
	if (init_data(&data, &settings, &locks) < 0)
		return (1);
	launch_philo_processes(&data, &settings, &locks);
	wait_philo_processes(&settings, data.philosophers);
	return (0);
}
