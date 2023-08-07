/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 16:03:41 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/07 21:33:30 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H
# define NAME_SEM_FORKS "fork_stack"
# define NAME_SEM_PRINT_LOCK "print_lock"
# define NAME_SEM_SETTING_LOCK "settings_lock"
# define ANSI_RED		"\x1b[31m"
# define ANSI_GREEN		"\x1b[32m"
# define ANSI_YELLOW	"\x1b[33m"
# define ANSI_BLUE		"\x1b[34m"
# define ANSI_MAGENTA	"\x1b[35m"
# define ANSI_CYAN		"\x1b[36m"

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

typedef struct s_locks
{
	sem_t			*print_lock;
	sem_t			*settings_lock;
}	t_locks;

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

int				parse_input(int argc, char *argv[], t_settings *settings,
					t_locks *locks);
t_philosopher	**create_philosophers(t_settings *settings);
int				create_semaphore(char *sem_name, size_t value, sem_t **sem);
int				launch_philo_processes(t_data *data, t_settings *settings,
					t_locks *locks);
int				philo_life(t_data *data, t_settings *settings,
					t_philosopher *philosopher, t_locks *locks);
void			free_philosophers(t_philosopher **philosophers);
int				philo_eat(t_data *data, t_settings *settings,
					t_philosopher *philo, t_locks *locks);
int				philo_sleep(t_data *data, t_settings *settings,
					t_philosopher *philo, t_locks *locks);
int				philo_think(t_settings *settings, t_philosopher *philo,
					t_locks *locks);
bool			check_simul_running(t_settings *settings, t_locks *locks);

// time utils
void			ms_sleep(size_t ms, struct timeval *start, t_settings *settings,
					t_locks *locks);
void			ms_sleep_pure(size_t ms, struct timeval *start);
size_t			calc_ms_passed(struct timeval *start, struct timeval *end);
void			print_timestamp(struct timeval *start_time, struct timeval *now,
					size_t philo_nr);

// utils
bool			ft_is_pos_integer(char *int_str);
int				ft_atoi(const char *str);
#endif
