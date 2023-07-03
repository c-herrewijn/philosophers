/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:09:58 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/30 15:00:02 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include "libft.h"
# include <stdio.h>
# include <stdbool.h>

typedef struct s_settings
{
	size_t	nr_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	nr_to_eat;
}	t_settings;

bool	input_valid(int argc, char *argv[]);
void	store_inputs(int argc, char *argv[], t_settings *settings);

#endif
