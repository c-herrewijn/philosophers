/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 19:36:47 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/02 13:54:33 by cherrewi      ########   odam.nl         */
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

int	parse_input(int argc, char *argv[], t_settings *settings)
{
	if (input_valid(argc, argv) == false)
		return (-1);
	store_inputs(argc, argv, settings);
	return (0);
}
