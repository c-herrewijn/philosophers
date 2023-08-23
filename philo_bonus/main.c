/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 15:54:44 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/23 15:51:40 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	wait_philo_processes(t_data *data, t_settings *settings)
{
	size_t	i;
	pid_t	return_pid;
	int		stat_loc;

	i = 0;
	while (i < settings->nr_philo)
	{
		return_pid = waitpid(data->philosophers[i]->pid, &stat_loc, 0);
		// printf("waitpid triggered for philo nr %zu\n", data->philosophers[i]->nr);
		if (return_pid == -1)
		{
			printf("waitpid error\n");
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
	t_settings				settings;
	t_data					data;
	t_locks					locks;
	t_killswitch_data		kill_switch_data;
	t_mon_eaten_enough_data	mon_eaten_enough_data;

	setbuf(stdout, NULL); // debug only, to write to file in order
	if (parse_input(argc, argv, &settings) < 0)
		return (1);
	if (init_data(&data, &settings, &locks) < 0)
		return (1);
	launch_philo_processes(&data, &settings, &locks);

	// should be detached thread // check return val!
	watch_killswitch(&data, &settings, &locks, &kill_switch_data);
	
	// should be detached thread // check return val!
	global_monitor_eaten_enough(&data, &settings, &locks, &mon_eaten_enough_data);  
	
	if (wait_philo_processes(&data, &settings) < 0)
		return (1);
	return (0);
}
