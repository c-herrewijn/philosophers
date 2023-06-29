/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validations.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:11:55 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/29 18:44:37 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_and_store_inputs(int argc, char *argv[], t_settings *settings)
{
	if ((argc != 5 && argc != 6)
		|| !ft_is_pos_integer(argv[1]) || !ft_is_pos_integer(argv[2])
		|| !ft_is_pos_integer(argv[3]) || !ft_is_pos_integer(argv[4])
		|| (argc == 6 && ft_is_pos_integer(argv[5]) == false))
	{
		printf("invalid input\n");
		return (-1);
	}
	settings->nr_philo = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		settings->nr_to_eat = ft_atoi(argv[5]);
	else
		settings->nr_to_eat = -1;
	return (0);
}
