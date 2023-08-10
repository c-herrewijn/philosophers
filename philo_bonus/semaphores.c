/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphores.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 15:55:10 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/10 16:08:23 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	create_semaphore(char *sem_name, size_t value, sem_t **sem)
{
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, value);
	if (*sem == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			if (sem_unlink(sem_name) < 0)
				return (-1);
			*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, value);
			if (*sem == SEM_FAILED)
				return (-1);
			else
				return (0);
		}
	}
	return (0);
}

int	create_semaphores(t_data *data, t_settings *settings,
	t_locks *locks)
{
	if (create_semaphore(NAME_SEM_FORKS, settings->nr_philo,
			&(data->sem_forks)) < 0
		|| create_semaphore(NAME_SEM_PRINT_LOCK, 1, &(locks->print_lock)) < 0
		|| create_semaphore(NAME_SEM_SETTING_LOCK, 1,
			&(locks->settings_lock)) < 0
		|| create_semaphore(NAME_SEM_KILL_SWITCH, 0, &(locks->kill_switch)) < 0
		|| create_semaphore(NAME_SEM_ALL_EATEN, 0, &(locks->all_eaten)) < 0)
	{
		printf("problems creating semaphores\n");
		unlink_semaphores();
		return (-1);
	}
	return (0);
}

void	unlink_semaphores(void)
{
	sem_unlink(NAME_SEM_FORKS);
	sem_unlink(NAME_SEM_PRINT_LOCK);
	sem_unlink(NAME_SEM_SETTING_LOCK);
	sem_unlink(NAME_SEM_KILL_SWITCH);
	sem_unlink(NAME_SEM_ALL_EATEN);
}
