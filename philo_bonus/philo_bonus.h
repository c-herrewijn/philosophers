/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 16:03:41 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/03 19:24:40 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define NAME_SEM_FORKS "fork_stack"

# include <errno.h>
# include <limits.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
	size_t			nr;
	pid_t			pid;
	int				times_eaten;
	struct timeval	last_eaten;
}	t_philosopher;

typedef struct s_data
{
	t_philosopher	**philosophers;
	sem_t			*sem_forks;
}	t_data;

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

int				parse_input(int argc, char *argv[], t_settings *settings);
t_philosopher	**create_philosophers(t_settings *settings);
int				philo_life(t_data *data, t_settings *settings,
					t_philosopher *philosopher);

// utils
bool			ft_is_pos_integer(char *int_str);
int				ft_atoi(const char *str);
#endif
