/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:09:58 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/30 15:44:28 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ANSI_RED		"\x1b[31m"
# define ANSI_GREEN		"\x1b[32m"
# define ANSI_YELLOW	"\x1b[33m"
# define ANSI_BLUE		"\x1b[34m"
# define ANSI_MAGENTA	"\x1b[35m"
# define ANSI_CYAN		"\x1b[36m"

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

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

typedef struct s_locks
{
	pthread_mutex_t	print_lock;
	pthread_mutex_t	settings_lock;
}	t_locks;

typedef struct s_philosopher
{
	size_t			nr;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_settings		*settings;
	t_locks			*locks;
	int				times_eaten;
	struct timeval	last_eaten;
}	t_philosopher;

typedef struct s_data
{
	pthread_mutex_t	**forks;
	t_philosopher	**philosophers;
	pthread_t		**threads;
}	t_data;

int				parse_input(int argc, char *argv[], t_settings *settings,
					t_locks *locks);
pthread_mutex_t	**create_cutlery(t_settings *settings);
t_philosopher	**create_philosophers(t_data *data, t_settings *settings,
					t_locks *locks);
pthread_t		**create_thread_arr(t_settings *settings);
void			destroy_and_free_cutlery(pthread_mutex_t **forks);
void			free_philosophers(t_philosopher **philosophers);
void			free_thread_arr(pthread_t **threads);
int				launch_threads(t_settings *settings,
					t_philosopher **philosophers, pthread_t **threads,
					t_locks *locks);
void			ms_sleep(size_t ms, struct timeval *start, t_settings *settings,
					t_locks *locks);
void			ms_sleep_pure(size_t ms, struct timeval *start);
size_t			calc_ms_passed(struct timeval *start, struct timeval *end);
int				philo_eat(t_philosopher *philo);
int				philo_sleep(t_philosopher *philo);
int				philo_think(t_philosopher *philo);
void			monitoring(t_data *data, t_settings *settings, t_locks *locks);
bool			check_simul_running(t_settings *settings, t_locks *locks);
void			print_timestamp(struct timeval *start_time, struct timeval *now,
					size_t philo_nr);
bool			ft_is_pos_integer(char *int_str);
int				ft_atoi(const char *str);

#endif
