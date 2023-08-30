/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_launch.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 14:45:22 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/27 22:01:03 by cherrewi      ########   odam.nl         */
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

static void	*f_mon_thread(void *input)
{
	t_monitor_data	*mon_data;
	struct timeval	last_eaten;
	struct timeval	now;

	mon_data = (t_monitor_data *)input;
	while (true)
	{
		gettimeofday(&now, NULL);
		last_eaten = mon_data->philo->last_eaten;
		if (calc_ms_passed(&last_eaten, &now) >= mon_data->time_to_die)
		{
			sem_wait(mon_data->sem_locks->print_lock);
			gettimeofday(&now, NULL);
			print_timestamp(mon_data->start_time, &now, mon_data->philo->nr);
			printf(" %zu died\n", mon_data->philo->nr);
			sem_post(mon_data->sem_locks->kill_switch);
			break ;
		}
		usleep(200);
	}
	return (NULL);
}

static int	launch_starvation_monitor(t_monitor_data *mon_data)
{
	pthread_t		mon_thread;

	if (pthread_create(&mon_thread, NULL, f_mon_thread, (void *)mon_data) < 0)
	{
		printf("pthread_create error\n");
		return (-1);
	}
	return (0);
}

static int	philo_main(t_data *data, t_settings *settings,
	t_philosopher *philosopher,	t_locks *locks)
{
	t_monitor_data	mon_data;

	mon_data.philo = philosopher;
	mon_data.time_to_die = settings->time_to_die;
	mon_data.sem_locks = locks;
	mon_data.start_time = &(settings->start_time);
	if (launch_starvation_monitor(&mon_data) < 0)
		exit(1);
	if (philo_life(data, settings, philosopher, locks) < 0)
		exit(1);
	else
		exit(0);
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
			printf("fork error\n");
			return (-1);
		}
		if (new_pid == 0)
		{
			if (philo_main(data, settings, data->philosophers[i], locks) < 0)
				exit(1);
			else
				exit(0);
		}
		data->philosophers[i]->pid = new_pid;
		i++;
	}
	return (0);
}
