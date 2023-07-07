/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:09:58 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/07 16:47:54 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_settings
{
	size_t			nr_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nr_to_eat;
	struct timeval	start_time;
}	t_settings;

typedef struct s_philosopher
{
	size_t			nr;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_settings		*settings;
	pthread_mutex_t	*settings_lock;
	int				times_eaten;
}	t_philosopher;

typedef struct s_data
{
	pthread_mutex_t	**forks;
	t_philosopher	**philosophers;
	pthread_t		**threads;
}	t_data;

bool			input_valid(int argc, char *argv[]);
void			store_inputs(int argc, char *argv[], t_settings *settings);
pthread_mutex_t	**create_cutlery(t_data *data, t_settings *settings);
t_philosopher	**create_philosophers(t_data *data, t_settings *settings,
					pthread_mutex_t *settings_lock);
pthread_t		**create_thread_arr(t_data *data, t_settings *settings);
void			destroy_and_free_cutlery(pthread_mutex_t **forks);
void			free_philosophers(t_philosopher **philosophers);
void			free_thread_arr(pthread_t **threads);
void			free_all(t_data *data);
int				launch_threads(t_settings *settings,
					t_philosopher **philosophers, pthread_t **threads);
void			ms_sleep(size_t ms, struct timeval *start);
struct timeval	print_timestamp(t_settings *settings,
					pthread_mutex_t *settings_lock);
size_t			calc_ms_passed(struct timeval *start, struct timeval *end);
void			philo_eat(t_philosopher *philosopher);
void			philo_sleep(t_philosopher *philosopher);
void			philo_think(t_philosopher *philosopher);

#endif
