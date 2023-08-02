/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 16:03:41 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/02 13:57:03 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_settings
{
	size_t			nr_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nr_to_eat;
	struct timeval	start_time;
	bool			simul_running;	
}	t_settings;

int		parse_input(int argc, char *argv[], t_settings *settings);
bool	ft_is_pos_integer(char *int_str);
int		ft_atoi(const char *str);
#endif
