/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_launch.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 14:45:22 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/07 21:29:09 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	set_start_time(t_settings *settings, t_philosopher **philosophers)
{
	size_t		i;

	if (gettimeofday(&(settings->start_time), NULL) < 0)
	{
		printf("gettimeofday error");
		return (-1);
	}
	i = 0;
	while (i < settings->nr_philo)
	{
		philosophers[i]->last_eaten = settings->start_time;
		i++;
	}
	return (0);
}

int	launch_philo_processes(t_data *data, t_settings *settings, t_locks *locks)
{
	size_t	i;
	pid_t	new_pid;

	if (set_start_time(settings, data->philosophers) < 0)
		return (-1);
	i = 0;
	while (i < settings->nr_philo)
	{
		new_pid = fork();
		if (new_pid < 0)
		{
			sem_wait(locks->settings_lock);
			settings->simul_running = false;
			sem_post(locks->settings_lock);
			printf("fork error\n");
			return (-1);
		}
		if (new_pid == 0)
		{
			if (philo_life(data, settings, data->philosophers[i], locks) < 0)
				exit(1);
			else
				exit(0);
		}
		data->philosophers[i]->pid = new_pid;
		i++;
	}
	return (0);
}
