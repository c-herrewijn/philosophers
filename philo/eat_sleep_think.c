/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 17:17:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/07/12 16:27:58 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(char fork_char, t_philosopher *philosopher)
{
	struct timeval	now;
	size_t			timestamp;
	size_t			time_to_eat;

	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	time_to_eat = philosopher->settings->time_to_eat;
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	if (fork_char == 'l')
		pthread_mutex_lock(philosopher->fork_left);
	else
		pthread_mutex_lock(philosopher->fork_right);
	pthread_mutex_lock(&(philosopher->locks->print_lock));
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	timestamp = calc_ms_passed(&(philosopher->settings->start_time), &now);
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	if (check_simul_running(philosopher->settings, philosopher->locks))
		printf("%5zu %zu has taken a fork\n", timestamp, philosopher->nr);
	if (fork_char == 'r')
	{
		if (check_simul_running(philosopher->settings, philosopher->locks))
		{
			printf("%5zu %zu is eating\n", timestamp, philosopher->nr); 
			pthread_mutex_lock(&(philosopher->locks->settings_lock));
			philosopher->times_eaten += 1;
			philosopher->last_eaten = now;
			pthread_mutex_unlock(&(philosopher->locks->settings_lock));
		}
		pthread_mutex_unlock(&(philosopher->locks->print_lock));
		ms_sleep(time_to_eat, &now, philosopher->settings, philosopher->locks);
	}
	else
		pthread_mutex_unlock(&(philosopher->locks->print_lock));
}

void	philo_eat(t_philosopher *philosopher)
{
	size_t			time_to_eat;
	int				nr_to_eat;
	struct timeval	now;

	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	time_to_eat = philosopher->settings->time_to_eat;
	nr_to_eat = philosopher->settings->nr_to_eat;
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	if (philosopher->times_eaten == 0 && philosopher->nr % 2 == 0)
	{
		gettimeofday(&now, NULL);
		ms_sleep(1 + time_to_eat / 2, &now, philosopher->settings, philosopher->locks);
	}
	take_fork('l', philosopher);
	if (philosopher->fork_left != philosopher->fork_right)
		take_fork('r', philosopher);
	pthread_mutex_unlock(philosopher->fork_left);
	if (philosopher->fork_left != philosopher->fork_right)
		pthread_mutex_unlock(philosopher->fork_right);
}

void	philo_sleep(t_philosopher *philosopher)
{
	size_t			time_to_sleep;
	struct timeval	now;
	size_t			timestamp;

	pthread_mutex_lock(&(philosopher->locks->print_lock));
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	timestamp = calc_ms_passed(&(philosopher->settings->start_time), &now);
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	printf("%5zu %zu is sleeping\n", timestamp, philosopher->nr);
	pthread_mutex_unlock(&(philosopher->locks->print_lock));
	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	time_to_sleep = philosopher->settings->time_to_sleep;
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	ms_sleep(time_to_sleep, &now, philosopher->settings, philosopher->locks);
}

void	philo_think(t_philosopher *philosopher)
{
	struct timeval	now;
	size_t			timestamp;

	pthread_mutex_lock(&(philosopher->locks->print_lock));
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&(philosopher->locks->settings_lock));
	timestamp = calc_ms_passed(&(philosopher->settings->start_time), &now);
	pthread_mutex_unlock(&(philosopher->locks->settings_lock));
	printf("%5zu %zu is thinking\n", timestamp, philosopher->nr); 
	pthread_mutex_unlock(&(philosopher->locks->print_lock));
}
