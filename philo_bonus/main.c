/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 15:54:44 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/07 21:25:58 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	unlink_lock_semaphores(void)
{
	sem_unlink(NAME_SEM_PRINT_LOCK);
	sem_unlink(NAME_SEM_SETTING_LOCK);
}

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

static int	init_data(t_data *data, t_settings *settings)
{
	data->philosophers = NULL;
	data->philosophers = create_philosophers(settings);
	if (data->philosophers == NULL)
		return (-1);
	if (create_semaphore(NAME_SEM_FORKS, settings->nr_philo,
			&(data->sem_forks)) < 0)
	{
		free_philosophers(data->philosophers);
		data->philosophers = NULL;
		printf("error creating semaphore");
		return (-1);
	}
	settings->simul_running = true;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_settings	settings;
	t_data		data;
	t_locks		locks;

	setbuf(stdout, NULL); // debug only, to write to file in order
	if (parse_input(argc, argv, &settings, &locks) < 0)
		return (1);
	if (init_data(&data, &settings) < 0)
	{
		unlink_lock_semaphores();
		return (1);
	}
	launch_philo_processes(&data, &settings, &locks);
	wait_philo_processes(&settings, data.philosophers);
	return (0);
}
