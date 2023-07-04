/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:09:58 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/04 13:55:10 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_settings
{
	size_t	nr_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	nr_to_eat;
}	t_settings;

typedef struct s_philosopher
{
	size_t			nr;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_settings		*settings;
	pthread_mutex_t	*settings_lock;
}	t_philosopher;

bool			input_valid(int argc, char *argv[]);
void			store_inputs(int argc, char *argv[], t_settings *settings);
pthread_mutex_t	**create_cutlery(t_settings *settings);
t_philosopher	**create_philosophers(t_settings *settings,
					pthread_mutex_t	**forks, pthread_mutex_t *settings_lock);
pthread_t		**create_thread_arr(t_settings *settings);
int				launch_threads(t_settings *settings,
					t_philosopher **philosophers, pthread_t **threads);

#endif
