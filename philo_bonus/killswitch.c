/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   killswitch.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 16:02:50 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/23 15:38:34 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sig_term_all_philos(t_philosopher **philosophers, size_t nr_philo)
{
	size_t	i;

	i = 0;
	while (i < nr_philo)
	{
		kill(philosophers[i]->pid, SIGTERM);
		i++;
	}
}

static void	*f_watch_killswitch(void *input)
{
	t_killswitch_data	*kill_switch_data;

	kill_switch_data = (t_killswitch_data *)input;
	sem_wait(kill_switch_data->kill_switch);
	// puts("killswitch triggered");
	sig_term_all_philos(kill_switch_data->philosophers,
		kill_switch_data->nr_philo);
	return (NULL);
}

static void	*f_mon_eaten_enough(void *input)
{
	t_mon_eaten_enough_data	*mon_eaten_enough_data;
	size_t					i;

	mon_eaten_enough_data = (t_mon_eaten_enough_data *)input;
	i = 0;
	// puts("starting monitor eaten enough..."); // debug
	while (i < mon_eaten_enough_data->nr_philo)
	{
		sem_wait(mon_eaten_enough_data->all_eaten);
		// puts("one philo is done eating"); // debug
		i++;
	}
	// puts("all eaten, stopping all processes");  // optionally, adjust print_lock, to prevent additional prints
	sig_term_all_philos(mon_eaten_enough_data->philosophers,
		mon_eaten_enough_data->nr_philo);
	return (NULL);
}

int	watch_killswitch(t_data *data, t_settings *settings,
	t_locks *locks, t_killswitch_data *kill_switch_data)
{
	// puts("watching killswitch...");

	pthread_t	kill_thread; // memory of kill_thread is stored on the stack, check if this is a problem

	kill_switch_data->kill_switch  = locks->kill_switch;
	kill_switch_data->philosophers = data->philosophers;
	kill_switch_data->nr_philo     = settings->nr_philo;
	if (pthread_create(&kill_thread, NULL, f_watch_killswitch,
		(void *)kill_switch_data) < 0)
	{
		printf("pthread_create error\n");
		return (-1);
	}
	return (0);
}

int	global_monitor_eaten_enough(t_data *data, t_settings *settings,
	t_locks *locks, t_mon_eaten_enough_data *mon_eaten_enough_data)
{
	pthread_t	mon_eaten_enough_thread; // memory of mon_eaten_enough_thread is stored on the stack, check if this is a problem	
	
	mon_eaten_enough_data->philosophers = data->philosophers;
	mon_eaten_enough_data->all_eaten    = locks->all_eaten;
	mon_eaten_enough_data->nr_philo     = settings->nr_philo;
	if (pthread_create(&mon_eaten_enough_thread, NULL, f_mon_eaten_enough,
		(void *)mon_eaten_enough_data) < 0)
	{
		printf("pthread_create error\n");
		return (-1);
	}
	return (0);
}
