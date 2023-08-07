/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 19:36:47 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/04 14:26:31 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	input_valid(int argc, char *argv[])
{
	if ((argc == 5 || argc == 6)
		&& ft_is_pos_integer(argv[1]) && ft_is_pos_integer(argv[2])
		&& ft_is_pos_integer(argv[3]) && ft_is_pos_integer(argv[4])
		&& (argc == 5 || ft_is_pos_integer(argv[5])))
	{
		if (ft_atoi(argv[1]) > SEM_VALUE_MAX)
		{
			printf("invalid input: too many philosophers\n");
			return (false);
		}
		return (true);
	}
	else
	{
		printf("invalid input\n");
		return (false);
	}
}

static void	store_inputs(int argc, char *argv[], t_settings *settings)
{
	settings->nr_philo = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		settings->nr_to_eat = ft_atoi(argv[5]);
	else
		settings->nr_to_eat = -1;
}

static int	init_locks(t_locks *locks)
{
	if (create_semaphore(NAME_SEM_PRINT_LOCK, 1, &(locks->print_lock)) < 0)
	{
		printf("problems creating semaphore lock\n");
		return (-1);
	}
	if (create_semaphore(NAME_SEM_SETTING_LOCK, 1, &(locks->settings_lock)) < 0)
	{
		sem_unlink(NAME_SEM_PRINT_LOCK);
		printf("problems creating semaphore lock\n");
		return (-1);
	}
	return (0);
}

int	parse_input(int argc, char *argv[], t_settings *settings, t_locks *locks)
{
	if (input_valid(argc, argv) == false)
		return (-1);
	store_inputs(argc, argv, settings);
	if (init_locks(locks) < 0)
		return (-1);
	return (0);
}
