/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 16:03:41 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/23 15:39:06 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H
# define NAME_SEM_FORKS "fork_stack"
# define NAME_SEM_PRINT_LOCK "print_lock"
# define NAME_SEM_SETTING_LOCK "settings_lock"
# define NAME_SEM_KILL_SWITCH "kill_switch"
# define NAME_SEM_ALL_EATEN "all_eaten"

# define ANSI_RED		"\x1b[31m"
# define ANSI_GREEN		"\x1b[32m"
# define ANSI_YELLOW	"\x1b[33m"
# define ANSI_BLUE		"\x1b[34m"
# define ANSI_MAGENTA	"\x1b[35m"
# define ANSI_CYAN		"\x1b[36m"

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
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
	sem_t			*kill_switch;
	sem_t			*all_eaten;
}	t_locks;

typedef struct s_settings
{
	size_t			nr_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nr_to_eat;
	struct timeval	start_time;
}	t_settings;

typedef struct s_monitor_data
{
	t_philosopher	*philo;
	size_t			time_to_die;
	t_locks			*sem_locks;
	sem_t			*settings_lock;
	struct timeval	*start_time;
}	t_monitor_data;

typedef struct s_killswitch_data
{
	sem_t			*kill_switch;
	t_philosopher	**philosophers;
	size_t			nr_philo;
}	t_killswitch_data;

typedef struct s_mon_eaten_enough_data
{
	t_philosopher	**philosophers;
	sem_t			*all_eaten;
	size_t			nr_philo;
}	t_mon_eaten_enough_data;


int				parse_input(int argc, char *argv[], t_settings *settings);
t_philosopher	**create_philosophers(t_settings *settings);
int				create_semaphores(t_data *data, t_settings *settings,
					t_locks *locks);
void			unlink_semaphores(void);
int				launch_philo_processes(t_data *data, t_settings *settings,
					t_locks *locks);
int				philo_life(t_data *data, t_settings *settings,
					t_philosopher *philosopher, t_locks *locks);
void			free_philosophers(t_philosopher **philosophers);
void			philo_eat(t_data *data, t_settings *settings,
					t_philosopher *philo, t_locks *locks);
void			philo_sleep(t_data *data, t_settings *settings,
					t_philosopher *philo, t_locks *locks);
void			philo_think(t_settings *settings, t_philosopher *philo,
					t_locks *locks);
int				global_monitor_eaten_enough(t_data *data, t_settings *settings,
					t_locks *locks,
					t_mon_eaten_enough_data *mon_eaten_enough_data);
int				watch_killswitch(t_data *data, t_settings *settings,
					t_locks *locks, t_killswitch_data *kill_switch_data);

// time utils
void			ms_sleep(size_t ms, struct timeval *start);
size_t			calc_ms_passed(struct timeval *start, struct timeval *end);
void			print_timestamp(struct timeval *start_time,
					struct timeval *now, size_t philo_nr);

// utils
bool			ft_is_pos_integer(char *int_str);
int				ft_atoi(const char *str);
#endif
